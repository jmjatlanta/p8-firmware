#pragma once

#include "WatchAppBase.h"
#include "../display.h"

/* 
  Device info screen, with uptime, compile time and other info
 */
class InfoApp : public WatchAppBase {
 private:
  char timeBuf[9];

 public:
  void onInit() override {
    clearDisplay(true);
    drawString({0, 0}, 1, "Firmware by:");
    drawString({0, 10}, 2, "Alex Underwood");
    drawString({0, 30}, 1, "Uptime:");
    drawString({0, 80}, 1, "Compiled:");
    drawString({0, 90}, 2, __DATE__);
    drawString({0, 110}, 2, __TIME__);
  }
  void onUpdate() override {
    drawIntWithPrecedingZeroes({0, 40}, 2, millis());
    drawIntWithoutPrecedingZeroes({0, 60}, 2, millis() / 1000 / 60 / 60 / 24);
    getStopWatchTime(timeBuf, 0, millis() % 86400000);
    drawString({35, 60}, 2, timeBuf);
  }
  uint8_t getScreenUpdateTimeMS() { return 200; }  //Slow update time
};
