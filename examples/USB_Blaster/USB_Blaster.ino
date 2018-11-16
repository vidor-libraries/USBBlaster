#include "Blaster.h"

static bool activityLed = true;

void setup() {
  USBBlaster.begin(activityLed);
  enableFpgaClock();
}

void loop() {
  USBBlaster.loop();
}
