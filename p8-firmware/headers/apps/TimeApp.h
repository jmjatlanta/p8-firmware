#pragma once

#include "WatchAppBase.h"
#include "../display.h"
#include "../p8Time.h"
#include "../powerControl.h"
/* 
  Main screen of the watch, shows time and other info
 */
class TimeApp : public WatchAppBase {
 private:
  uint8_t lastDay = 255;
  char distanceChar[10];
  char timeStr[6];   //00:00\0
  char dateStr[11];  //01.01.1970\0
  char dayStr[10];   //wednesday\0

 public:
  void onInit() override
  {
    clearDisplay(true);
    drawChar({80, 145}, 3, '%', COLOUR_WHITE, COLOUR_BLACK);
  }
  void onUpdate() override
  {
    getTime(timeStr);
    drawString({20, 15}, 5, timeStr);
    getDate(dateStr);
    drawString({20, 70}, 3, dateStr);
    //If we are on a new day, reset the current step count
    if (getDayOfWeek() != lastDay) {
      lastDay = getDayOfWeek();
      drawString({20, 100}, 3, "          ");  //Clear day
    }
    getDay(dayStr);
    drawString({20, 100}, 3, dayStr);

    if (!getChargeState()) {
      if (getBatteryPercent() < 99)
        drawChar({20, 142}, 3, GLYPH_BATTERY, COLOUR_RED, COLOUR_BLACK);
      else
        drawChar({20, 142}, 3, GLYPH_BATTERY, COLOUR_GREEN, COLOUR_BLACK);
    } else {
      drawChar({20, 142}, 3, GLYPH_BATTERY, COLOUR_WHITE, COLOUR_BLACK);
    }
    drawIntWithoutPrecedingZeroes({40, 145}, 3, getBatteryPercent());
  }
};