#ifndef __EECONFIG_H
#define __EECONFIG_H

#define   _EE_USE_FLASH_PAGE_OR_SECTOR              (5)  //PAGE OR SECTOR TO BE USED
#define   _EE_USE_RAM_BYTE                          (1024) //first we write data into the intrnal buffer, then we tell the program to commit data to the flash
#define   _EE_VOLTAGE                               FLASH_VOLTAGE_RANGE_3 //  use in some devices
#endif
