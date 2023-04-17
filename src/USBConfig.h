#ifndef USBBlaster_h
#define USBBlaster_h

#include <stdint.h>
#include <Arduino.h>

#if ARDUINO < 10606
#error USBBlaster requires Arduino IDE 1.6.6 or greater. Please update your IDE.
#endif

#if !defined(USBCON)
#error USBBlaster can only be used with an USB MCU.
#endif

#if defined(ARDUINO_ARCH_AVR)

#include "PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE      uint8_t
#define EP_TYPE_BULK_IN_BLASTER     EP_TYPE_BULK_IN
#define EP_TYPE_BULK_OUT_BLASTER    EP_TYPE_BULK_OUT
#define BLASTER_BUFFER_SIZE         USB_EP_SIZE
#define is_write_enabled(x)         (1)

#elif defined(ARDUINO_ARCH_SAM)

#include "USB/PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE      uint32_t
#define EP_TYPE_BULK_IN_BLASTER     (UOTGHS_DEVEPTCFG_EPSIZE_512_BYTE |   \
                                     UOTGHS_DEVEPTCFG_EPDIR_IN |          \
                                     UOTGHS_DEVEPTCFG_EPTYPE_BLK |        \
                                     UOTGHS_DEVEPTCFG_EPBK_1_BANK |       \
                                     UOTGHS_DEVEPTCFG_NBTRANS_1_TRANS |   \
                                     UOTGHS_DEVEPTCFG_ALLOC)
#define EP_TYPE_BULK_OUT_BLASTER    (UOTGHS_DEVEPTCFG_EPSIZE_512_BYTE |   \
                                     UOTGHS_DEVEPTCFG_EPTYPE_BLK |        \
                                     UOTGHS_DEVEPTCFG_EPBK_1_BANK |       \
                                     UOTGHS_DEVEPTCFG_NBTRANS_1_TRANS |   \
                                     UOTGHS_DEVEPTCFG_ALLOC)
#define BLASTER_BUFFER_SIZE     EPX_SIZE
#define USB_SendControl         USBD_SendControl
#define USB_Available           USBD_Available
#define USB_Recv                USBD_Recv
#define USB_Send                USBD_Send
#define USB_Flush               USBD_Flush
#define is_write_enabled(x)     Is_udd_write_enabled(x)

#elif defined(ARDUINO_ARCH_SAMD)

#include "api/PluggableUSB.h"

#define EPTYPE_DESCRIPTOR_SIZE      unsigned int
#define EP_TYPE_BULK_IN_BLASTER     USB_ENDPOINT_TYPE_BULK | USB_ENDPOINT_IN(0);
#define EP_TYPE_BULK_OUT_BLASTER    USB_ENDPOINT_TYPE_BULK | USB_ENDPOINT_OUT(0);
#define BLASTER_BUFFER_SIZE         EPX_SIZE
#define USB_SendControl             USBDevice.sendControl
#define USB_Available               USBDevice.available
#define USB_Recv                    USBDevice.recv
#define USB_Send                    USBDevice.send
#define USB_Flush                   USBDevice.flush
#define is_write_enabled(x)         (1)

#else

#error "Unsupported architecture"

#endif

/* FTDI events on USB */

#define FTDI_VEN_REQ_RESET              0x00
#define FTDI_VEN_REQ_SET_BAUDRATE       0x01
#define FTDI_VEN_REQ_SET_DATA_CHAR      0x02
#define FTDI_VEN_REQ_SET_FLOW_CTRL      0x03
#define FTDI_VEN_REQ_SET_MODEM_CTRL     0x04
#define FTDI_VEN_REQ_GET_MODEM_STA      0x05
#define FTDI_VEN_REQ_SET_EVENT_CHAR     0x06
#define FTDI_VEN_REQ_SET_ERR_CHAR       0x07
#define FTDI_VEN_REQ_SET_LAT_TIMER      0x09
#define FTDI_VEN_REQ_GET_LAT_TIMER      0x0A
#define FTDI_VEN_REQ_SET_BITMODE        0x0B
#define FTDI_VEN_REQ_RD_PINS            0x0C
#define FTDI_VEN_REQ_RD_EEPROM          0x90
#define FTDI_VEN_REQ_WR_EEPROM          0x91
#define FTDI_VEN_REQ_ES_EEPROM          0x92

#define FTDI_MODEM_STA_SIZE             0x02
#define FTDI_MODEM_STA_DUMMY0           0x01
#define FTDI_MODEM_STA_DUMMY1           0x60


#define WEAK __attribute__ ((weak))

typedef struct
{
  InterfaceDescriptor dif;
  EndpointDescriptor  in;
  EndpointDescriptor  out;
} USBBlasterDescriptor;


/**
   Concrete USB Blaster implementation of a PluggableUSBModule
*/
class USBBlaster_ : public PluggableUSBModule
{
  private:
    EPTYPE_DESCRIPTOR_SIZE epType[2];
    uint32_t available(void);
    size_t read(uint8_t *buffer, size_t size);
    void flush(void);
    size_t write(const uint8_t *buffer, size_t size);
    int usbrecv();
    void usbsend();
    void ioproc();
    bool leds = false;
    int usb_out_ep_size = 64;
    long lastAction = 0;

  protected:
    int getInterface(uint8_t* interfaceNum);
    int getDescriptor(USBSetup& setup);
    bool setup(USBSetup& setup);
    uint8_t getShortName(char* name);

  public:
    USBBlaster_(void);
    void begin(bool use_leds = false);
    int loop();
    bool idle();
    void setOutEpSize(int size);
    uint8_t getJSM(void);
    uint8_t setJSM(uint8_t state);
    operator bool();
};

extern USBBlaster_ USBBlaster;

#endif  /* USBBlaster_h */
