#include "Blaster.h"

static bool activityLed = true;

extern void enableFpgaClock();

void setup() {
  USBBlaster.begin(activityLed);
  // also start the 48MHz clock feed for the FPGA, in case we need to run the bitstream and need this clock
  enableFpgaClock();
}

void loop() {
  USBBlaster.loop();
}
