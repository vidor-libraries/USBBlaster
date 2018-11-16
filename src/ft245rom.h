/*
  ft245rom.h

  MIT License

  Copyright (c) 2016 Yongqian Tang

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef __FT245ROM_H__
#define __FT245ROM_H__

#include "base.h"

#define FT245ROM_SIZE           (128)
#define FT245ROM_STR_LIMIT      (100)

#ifdef __cplusplus
extern "C" {
#endif
int ft245rom_init(void);
uint16_t ft245rom_read(uint8_t addr);
#ifdef __cplusplus
}
#endif

#define BLASTER_SIZ_DEVICE_DESC                 18
#define BLASTER_SIZ_CONFIG_DESC                 32
#define BLASTER_SIZ_STRING_LANGID               4
#define BLASTER_SIZ_STRING_VENDOR               14
#define BLASTER_SIZ_STRING_PRODUCT              24
#define BLASTER_SIZ_STRING_SERIAL               18


/* USB Standard Device Descriptor */
const uint8_t Blaster_DeviceDescriptor[BLASTER_SIZ_DEVICE_DESC] = {
  0x12,                       /*bLength */
  USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
  0x00,                       /*bcdUSB */
  0x02,
  0x00,                       /*bDeviceClass*/
  0x00,                       /*bDeviceSubClass*/
  0x00,                       /*bDeviceProtocol*/
  0x40,                       /*bMaxPacketSize(64bytes)*/
  0xFB,                       /*idVendor (0x09FB=Altera)*/
  0x09,
  0x01,                       /*idProduct(0x6001=USB-Blaster)*/
  0x60,
  0x00,                       /*bcdDevice rel. B*/
  0x04,
  1,                          /*Index of string descriptor describing manufacturer */
  2,                          /*Index of string descriptor describing product*/
  3,                          /*Index of string descriptor describing the device serial number */
  0x01                        /*bNumConfigurations*/
};

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Blaster_ConfigDescriptor[BLASTER_SIZ_CONFIG_DESC] = {
  /* Configuration Descriptor */
  /* 00 */
  0x09,         /* bLength: Configuration Descriptor size */
  USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
  BLASTER_SIZ_CONFIG_DESC,  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /* bNumInterfaces: 1 interface */
  0x01,         /* bConfigurationValue: Configuration value */
  0x00,         /* iConfiguration: Index of string descriptor describing the configuration*/
  0x80,         /* bmAttributes: Bus powered(bit6=0) */
  0xE1,         /* MaxPower 450mA(225*2) */

  /* Interface Descriptor */
  /* 09 */
  0x09,         /* bLength: Interface Descriptor size */
  USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
  0x00,         /* bInterfaceNumber: Number of Interface */
  0x00,         /* bAlternateSetting: Alternate setting */
  2 - 1,   /* bNumEndpoints */
  0xFF,         /* bInterfaceClass: NA */
  0xFF,         /* bInterfaceSubClass : NA */
  0xFF,         /* nInterfaceProtocol : NA */
  0,            /* iInterface: Index of string descriptor */

  /* Endpoint Descriptor */
  /* 18 */
  0x07,          /* bLength: Endpoint Descriptor size */
  USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: Endpoint descriptor */
  2,        /* bEndpointAddress: Endpoint 1 IN */
  0x02,          /* bmAttributes: Bulk endpoint */
  64,  /* wMaxPacketSize: 64 Bytes max */
  0x00,
  0x01,          /* bInterval: Polling Interval (1 ms) */
  /* 25 */
  0x07,          /* bLength: Endpoint Descriptor size */
  USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint descriptor */
  3,       /* bEndpointAddress: Endpoint 2 OUT */
  0x02,          /* bmAttributes: Bulk endpoint */
  64,  /* wMaxPacketSize: 64 Bytes max  */
  0x00,
  0x01,          /* bInterval: Polling Interval (1 ms) */
  /* 32 */
};


const uint8_t Blaster_StringVendor[BLASTER_SIZ_STRING_VENDOR] = {
    BLASTER_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    'A', 0, 'l', 0, 't', 0, 'e', 0, 'r', 0, 'a', 0 /* Manufacturer: "Altera" */
};

const uint8_t Blaster_StringProduct[BLASTER_SIZ_STRING_PRODUCT] = {
    BLASTER_SIZ_STRING_PRODUCT,   /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,     /* bDescriptorType */
    'U', 0, 'S', 0, 'B', 0, '-', 0, 'B', 0, 'l', 0, 'a', 0, 's', 0, 't', 0, 'e', 0, 'r', 0  /* "USB-Blaster" */
};

const uint8_t Blaster_StringSerial[BLASTER_SIZ_STRING_SERIAL] = {
    BLASTER_SIZ_STRING_SERIAL,    /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,     /* bDescriptorType */
    '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0  /* "12345678" */
};
#endif //__FT245ROM_H__
