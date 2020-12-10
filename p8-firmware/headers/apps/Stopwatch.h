#pragma once

#include "WatchAppBase.h"

/* 
  Screen that has stopwatch on it
 */
class StopwatchApp : public WatchAppBase {
 private:
  bool hasStarted = false;
  long startTime = 0;
  char timeBuf[9];

 public:
  void onInit() override {
    clearDisplay(true);
    drawUnfilledRect({0, 0}, 110, 60, 7, COLOUR_GREEN);
    drawUnfilledRect({130, 0}, 110, 60, 7, COLOUR_RED);
    drawString({55 - STR_WIDTH("Start", 3) / 2, 18}, 3, "Start");  //Look at screenTap() for more info
    drawString({185 - STR_WIDTH("Stop", 3) / 2, 18}, 3, "Stop");
  }
  
  void onUpdate() override {
    if (hasStarted) {
      getStopWatchTime(timeBuf, startTime, millis());
      drawString({120 - STR_WIDTH("00:00:00", 4) / 2, 115}, 4, timeBuf);
    }
  }

  bool onTap(uint8_t x, uint8_t y) override {
    //This is effectively a button touch listener, making sure the touch is in bounds of the button
    if (x < 120 && y < 60) 
    {
      startStopWatch();
      return true;
    } else if (x > 120 && y < 60) 
    {
      stopStopWatch();
      return true;
    }
    return false;
  }

  void startStopWatch() {
    startTime = millis();
    hasStarted = true;
  }
  void stopStopWatch() {
    hasStarted = false;
  }
};