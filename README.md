# ESP-IDF Code Conversion
 Conversion from C to C++ to Arduino .ino to support re-use of snippets

## Purpose

I have been using the Arduino IDE for creation of firmware for ESP32/ESP8266 boards quite a while now. Recently I acquired a board with very interesting **hardware** (TTGO TAudio 9 V1.6 by Lilygo). Work on the mining of this board's capabilities will be described in other repos. Many times, the capabilities of such boards are documented very poorly. You can be lucky when the inputs/outputs and product codes of onboard additional hardware components are given. And last but not least: when it is clear which version of a board you have in hands such that you know that the hardware info belongs to your board.

Similar things are true for the **software**. You are lucky when the manufacturer offers a Github repo with exmples. However, it happens that you have to find snippets of code on the web for the onboard hardware components. Together with the information on usage of controller ports for these hardware components it is then possible to re-write those snippets to fit them to the available hardware.

There are all kinds of code snippets on the web. Some of them are specific for the Arduino IDE (C++-like), but most of them are written in either C or C++. This implies that I have to abandon the Arduino IDE and go for a programming environment that can handle C / C++ only code. In fact the best way would be to go the system supported by the manufacturer of the heart of the boards: Espressif.

Espressif offers a extensively documented ((https://github.com/espressif/esp-idf) with setup instructions for the ESP-IDF environment). This can be used from the command line (with calls to idf.py) or via IDEs such as Eclipse or Visual Studio with the ESP-idf extension. None of these environments is very easy to use. Currently I have the best experience with **ESP-IDF from the command line**.  The package also contains a large number of examples, well sorted per application area. This gives development of own code based on them a headstart . They are very well documented in the README files. There are several hurdles to take in using these examples and developing own code based on them: 
- most of them (if not all) are written in C and my knowledge of C is poor. 
- the Espressif-IDF documentation does not describe how to start a project from scratch (not for C++ projects, but even not for C projects !). 

The solution is nearby!

Recently I found this article ( https://www.deeptronic.com/software-design/developing-esp32-application-with-esp-idf-and-c-in-windows). It is on "conversion" of a C example code into C++ code or, better, on creation of a C++ wrapper around the original code such that it can be built and flashed from the ESP-IDF environment as C++ code. A subsequent described step is to extract relevant portions of the C code and convert that into C++ modules or libraries. This may open up a way to use existing C++ libraries in the code, which is of course a huge advantage.

In this repo I do the walktrough example described in the article. This starts with the Espressif hello_world example written in C (see folder: hello_world_c) and goes via functionally identical code that wraps the C code but that can be complied in C++ (see folder: hello_world_cpp) and ends with code where parts of the C code have been replaced by C++ code (see: folder: hello_world_cpp_libs). 

I **do NOT** describe the details of the walktrough as the article does that perfectly. I may note down some learnings or summarizing remarks.

One step further (not described in the article) would be to wrap the original C code in an Arduino sketch (hello_world_Arduino).

Each folder contains the original README that describes how to compile the example in the ESP-IDF.

## References
1. https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/
2. https://blog.espressif.com/esp-idf-development-tools-guide-part-i-89af441585b
also see the hello_world readme.md and links therein, such as 
3. https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html how to start a new project (and folder structure)

## Learnings / summary

- The ESP-IDF environment can compile projects that use CMake.
- The wrapping solution involves a.o. editing of the CMake files.
- It would be interesting learn on how to convert non-CMake C projects (such as....) to CMake. This would open up a large amount of C codes for doing the conversion to C++ or Arduino IDE. 

Here is the structure of the original project in folder hello_world_C (taken from the README supplied with the example):


```
hello_world_c
├── CMakeLists.txt
├── example_test.py            Python script used for automated example testing
├── main
│   ├── CMakeLists.txt
│   ├── component.mk           Component make file
│   └── hello_world_main.c
├── Makefile                   Makefile used by legacy GNU Make
└── README.md                  
```

Note: the CMakeLists.txt files contain "hello_world", being the original project name. There is NO relation with the name of the project folder (hello_world_c). THe project compiles and flashes well.


The contents of the folder is copied into a new folder for the C++ code:
Identify the changes in this diagram.

```
hello_world_cpp                
├── CMakeLists.txt             1.
├── example_test.py            
├── main
│   ├── CMakeLists.txt         3.
│   ├── component.mk           
│   └── main.cpp     4.  5.
├── Makefile                   2.
└── README.md                  
```

1. Open “project_name\CMakeList.txt” file using any text editor and edit: change “project(hello-world)” into “project(project-name)”, save the file.
2. Open “project_name\Makefile” file using any text editor and edit: “PROJECT_NAME := hello-world” into “PROJECT_NAME := project-name”, save the file.
3. Open “project_name\main\CMakeList.txt” file using any text editor and edit: change “hello_world_main.c” into “main.cpp”, save the file.
4. Rename the file “hello_world_main.c” in the folder “project_name\main\ ” into “main.cpp”.
5. Open “project_name\main\main.cpp” file using any text editor and edit: add the following statement extern “C” { void app_main(); } before void app_main() , see Figure 4, save the file.

I presume that 3,4 and 5 are the essential changes.

contents of hello_world_main.c:

```
#include "esp_system.h"
#include "esp_spi_flash.h"

void app_main(void)
{
    printf("Hello world of C!\n");

    /* Print chip information */
```

contents of main.cpp:

```
#include "esp_system.h"
#include "esp_spi_flash.h"

extern “C” { void app_main(); }

void app_main(void)
{
    printf("Hello world of C++!\n");

    /* Print chip information */
```
