#ifndef SYSTEMINFO_H_
#define SYSTEMINFO_H_
 
#include &lt;stdio.h>
#include "esp_system.h"
#include "esp_spi_flash.h"
 
class esp_systeminfo
{
	private:
		esp_chip_info_t chip_info;
	public:
		void print();
	
};
 
#endif