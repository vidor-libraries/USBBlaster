# USBBlaster Arduino library === EXPERIMENTAL

This library implements a JTAG programmer based on Altera USB Blaster protocol as a PluggableUSB module.
Due to license issues we can only distribute the precompiled library (and the headers), so the minimum required version of SAMD core is 1.6.25.

## Usage

Include the library with 
```C++
#include "Blaster.h"
```

This will create a composite USB device mocking the original Blaster VID/PID so Quartus can happily use it as a programmer/debugger without any patching.

To attach the JTAG pins call
```C++
USBBlaster.begin(bool status_led)
```
If `status_led` is true the builtin LED will show the programmer's activity.

To perform the USB communication the user must call
```C++
USBBlaster.loop()
```
every once in a while. Adding it once inside the main `loop()` function is usually enough.

You can then connect with the programmer using Quartus programmer/urjtag/openocd to load a bitstream in FPGA RAM or debug a running softcore.

### Known issues

#### All OS
Depending on the underlying USB library (libusb or similar) the OS may send/receive more bytes than declared in the USB endpoint.
The board often hangs when this happens; if you are facing this situation, please call
```C++
USBBlaster.setOutEpSize(60)
```
before calling `USBBlaster.begin()` . This will change the endpoint size (OS side) so it's less likely to send more than 64 bytes in a single chunk.
Replace `60` with a number that fits your setup.

#### Windows
**Using this library may provoke blue screen of deaths!** This is due to:
* windows trying to load the original Altera driver (which does not expose a composite interface).

  Fix: uninstall the original driver before plugging in the board
* if `USBBlaster.loop()` is not called often enough, the Altera driver may "complain" with a BSOD... 

  Fix: try to avoid long pauses/delays between two calls to `USBBlaster.loop()`
  
#### Linux
Quartus programmer may hang on any operation you perform.
Root causes:
* udev permissions are not ok

  Fix: add an udev rule (`/etc/udev/rules.d/51-altera-usb-blaster.rules`) with this content
  ```
  SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6001", MODE="0666"
  SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6002", MODE="0666"
  SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6003", MODE="0666"
  SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6010", MODE="0666"
  SUBSYSTEM=="usb", ATTR{idVendor}=="09fb", ATTR{idProduct}=="6810", MODE="0666"
  ```
* `libudev.so.0` is not installed in the system (because we are in 2018)

  Fix: symlink `libudev.so.1` to `libudev.so.0` in `/usr/lib` (or install `libusb0-shim`)
* jtag operations hangs

  Fix: forcibly kill `jtagd` and relaunch it manually
