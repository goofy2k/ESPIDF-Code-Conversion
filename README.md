# ESP-IDF Code Conversion
 Conversion from C to C++ to Arduino .ino to support re-use of snippets

## Purpose

I have been using the Arduino IDE for creation of firmware for ESP32/ESP8266 boards quite a while now. Recently I acquired a board with very interesting **hardware** (TTGO TAudio 9 V1.6 by Lilygo). Work on the mining of this board's capabilities will be described in other repos. Many times, the capabilities of such boards are documented very poorly. You can be lucky when the inputs/outputs and product codes of onboard additional hardware components are given. And last but not least: when it is clear which version of a board you have in hands such that you know that the hardware info belongs to your board.

Similar things are true for the **software**. You are lucky when the manufacturer offers a Github repo that contains well documented examples of code for applications. However, it happens that you have to find snippets of code on the web for the onboard hardware components. Together with the information on usage of controller ports for these hardware components it is then possible to re-write those snippets to fit them to the available hardware.

There are all kinds of code snippets on the web. Some of them are specific for the Arduino IDE (C++-like), but most of them are written in either C or C++. This implies that I have to abandon the Arduino IDE and go for a programming environment that can handle C / C++ only code. In fact the best way would be to go the system supported by the manufacturer of the heart of the boards: Espressif.

Espressif offers a extensively documented (link) firmware development system (ESP-IDF). This can be used from the command line (with calls to idf.py) or via IDEs such as Eclipse or Visual Studio with the ESP-idf extension. None of these environments is very easy to use. Currently I have the best experience with **ESP-IDF from the command line**.  In the ESP-IDF package (Github link) is a large number of examples, well sorted per application area. This gives development of own code based on them a headstart . They are very well documented in the README files. There are several hurdles to take in using these examples and developing own code based on them: 
- most of them (if not all) are written in C and my knowledge of C is poor. 
- the Espressif-IDF documentation does not describe how to start a project from scratch (not for C++ projects, but even not for C projects !). 

The solution is nearby!

Recently I found this article ( https://www.deeptronic.com/software-design/developing-esp32-application-with-esp-idf-and-c-in-windows). It is on "conversion" of a C example code into C++ code or, better, on creation of a C++ wrapper around the original code such that it can be built and flashed from the ESP-IDF environment as C++ code. A subsequent described step is to extract relevant portions of the C code and convert that into C++ modules or libraries. This may open up a way to use existing C++ libraries in the code, which is of course a huge advantage.

In this repo I do the walktrough example described in the article. This starts with the Espressif hello_world example written in C (folder name) and goes via functionally identical code that wraps the C code but that can be complied in C++ (folder name) and ends with code where parts of the C code have been replaced by C++ code. I **do NOT** describe the details of the walktrough as the article does that perfectly. I may note down some learnings or summarizing remarks.

One step further (not described in the article) would be to wrap the original C code in an Arduino sketch (folder name).

Each folder contains the original README that describes how to compile the example in the ESP-IDF.

## Learnings / summary

...
