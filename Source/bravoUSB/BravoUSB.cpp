//
//  BravoUSB.cpp
//  BravoLights
//
//  Created by Steve Proctor on 05/06/2023.
//

/*
 *   X-Plane 12 Plugin for Apple Silicon Computers
 *
 *   Copyright (C) 2024 Steve Proctor <swp336@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "BravoUSB.hpp"
#include "hidapi_darwin.h"

/*
const char *hid_bus_name(hid_bus_type bus_type) {
    static const char *const HidBusTypeName[] = {
        "Unknown",
        "USB",
        "Bluetooth",
        "I2C",
        "SPI",
    };

    if ((int)bus_type < 0)
        bus_type = HID_API_BUS_UNKNOWN;
    if ((int)bus_type >= (int)(sizeof(HidBusTypeName) / sizeof(HidBusTypeName[0])))
        bus_type = HID_API_BUS_UNKNOWN;

    return HidBusTypeName[bus_type];
}


void print_device(struct hid_device_info *cur_dev) {
    printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
    printf("\n");
    printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
    printf("  Product:      %ls\n", cur_dev->product_string);
    printf("  Release:      %hx\n", cur_dev->release_number);
    printf("  Interface:    %d\n",  cur_dev->interface_number);
    printf("  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page);
    printf("  Bus type: %d (%s)\n", cur_dev->bus_type, hid_bus_name(cur_dev->bus_type));
    printf("\n");
}


void print_devices_with_descriptor(struct hid_device_info *cur_dev) {
    for (; cur_dev; cur_dev = cur_dev->next) {
        print_device(cur_dev);
   //     print_hid_report_descriptor_from_path(cur_dev->path);
    }
}

 */

BravoUSB::BravoUSB() {
      
    //hid_darwin_set_open_exclusive(0);
    hid_init();
    
//    bravoDevice = hid_open(0x294B, 0x1901, NULL);
}

BravoUSB::~BravoUSB() {
    hid_exit();
}

void BravoUSB::setLights(uint64_t thisMask) {
    
    unsigned char buffer[5];
    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;
    buffer[4] = 0;
    
    uint64_t byte1 = thisMask;
    uint64_t byte2 = thisMask;
    uint64_t byte3 = thisMask;
    uint64_t byte4 = thisMask;
    
    byte1 = byte1 & 255;              // 0b11111111
    buffer[1] = byte1;
    byte2 = byte2 & 65280;            // 0b1111111100000000
    buffer[2] = byte2 >> 8;
    byte3 = byte3 & 16711680;         // 0b111111110000000000000000;
    buffer[3] = byte3 >> 16;
    byte4 = byte4 & 4278190080;       //0b11111111000000000000000000000000;
    buffer[4] = byte4 >> 24;
    bravoDevice = hid_open(0x294B, 0x1901, NULL);
    if (bravoDevice != NULL)
    {   hid_send_feature_report(bravoDevice, buffer, 5);
        hid_close(bravoDevice);
    }
}


bool BravoUSB::getCurrentSettings(unsigned char* data) {
    
    bravoDevice = hid_open(0x294B, 0x1901, NULL);

    if (bravoDevice != NULL) {
        int result = hid_read(bravoDevice, data, 18);
        hid_close(bravoDevice);
        return (result != -1);
    }
    else return false;
}
