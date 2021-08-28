#include "systeminfo.h"
 
void esp_systeminfo::print()
{
	esp_chip_info(&amp;chip_info);
	printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features &amp; CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features &amp; CHIP_FEATURE_BLE) ? "/BLE" : "");
 
    printf("silicon revision %d, ", chip_info.revision);
 
    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features &amp; CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
}