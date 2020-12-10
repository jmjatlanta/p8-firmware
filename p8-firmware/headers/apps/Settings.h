#pragma once

#include "../display.h"
#include "WatchAppBase.h"

/* 
  "Settings" app where you can set the time and date, and the brightness
  _Awefully_ written
 */
class SettingsApp : public WatchAppBase 
{
private:
  int8_t setHour = 12;
  int8_t setMinute = 30;
  int8_t setSecond = 0;
  int setYear = 2020;
  int8_t setMonth = 6;
  int8_t setDay = 15;

public:
  enum settingsWindow {
    BRIGHTNESS,
    SECOND,
    MINUTE,
    HOUR,
    DAY,
    MONTH,
    YEAR
  };

  settingsWindow currentSettingsWindow = BRIGHTNESS;

  void onInit() override {
    clearDisplay(true);
    drawRects();
    currentSettingsWindow = BRIGHTNESS;
  }

  void onUpdate() override 
  {
    switch (currentSettingsWindow) {
      case BRIGHTNESS:
        drawString({0, 0}, 3, "Brightness");
        drawIntWithPrecedingZeroes({0, 26}, 3, getBrightness());
        break;
      case SECOND:
        drawString({0, 0}, 3, "Second");
        drawIntWithPrecedingZeroes({0, 26}, 3, setSecond);
        break;
      case MINUTE:
        drawString({0, 0}, 3, "Minute");
        drawIntWithPrecedingZeroes({0, 26}, 3, setMinute);
        break;
      case HOUR:
        drawString({0, 0}, 3, "Hour");
        drawIntWithPrecedingZeroes({0, 26}, 3, setHour);
        break;
      case DAY:
        drawString({0, 0}, 3, "Day");
        drawIntWithPrecedingZeroes({0, 26}, 3, setDay);
        break;
      case MONTH:
        drawString({0, 0}, 3, "Month");
        drawIntWithPrecedingZeroes({0, 26}, 3, setMonth);
        break;
      case YEAR:
        drawString({0, 0}, 3, "Year");
        drawIntWithPrecedingZeroes({0, 26}, 3, setYear);
        setTimeWrapper(setYear, setMonth, setDay, setHour, setMinute, setSecond);
        break;
    }
  }

  bool onTap(uint8_t x, uint8_t y) override 
  {
    if (x <= 120) {
      switch (currentSettingsWindow) {
        case BRIGHTNESS:
          decBrightness();
          break;
        case SECOND:
          if (setSecond > 0)
            setSecond--;
          break;
        case MINUTE:
          if (setMinute > 0)
            setMinute--;
          break;
        case HOUR:
          if (setHour > 0)
            setHour--;
          break;
        case DAY:
          if (setDay > 0)
            setDay--;
          break;
        case MONTH:
          if (setMonth > 0)
            setMonth--;
          break;
        case YEAR:
          if (setYear > 0)
            setYear--;
          break;
      }
    } else if (x > 120) {
      switch (currentSettingsWindow) {
        case BRIGHTNESS:
          incBrightness();
          break;
        case SECOND:
          if (setSecond < 60)
            setSecond++;
          break;
        case MINUTE:
          if (setMinute < 60)
            setMinute++;
          break;
        case HOUR:
          if (setHour < 23)
            setHour++;
          break;
        case DAY:
          if (setDay < 31)
            setDay++;
          break;
        case MONTH:
          if (setMonth < 12)
            setMonth++;
          break;
        case YEAR:
          setYear++;
          break;
      }
    }
    return true;
  }
  bool onSwipeDown() override {
    switch (currentSettingsWindow) {
      case BRIGHTNESS:
        currentSettingsWindow = SECOND;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case SECOND:
        currentSettingsWindow = MINUTE;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case MINUTE:
        currentSettingsWindow = HOUR;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case HOUR:
        currentSettingsWindow = DAY;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case DAY:
        currentSettingsWindow = MONTH;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case MONTH:
        currentSettingsWindow = YEAR;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      default:
        break;
    }
    return true;
  }

  bool onSwipeUp() override {
    switch (currentSettingsWindow) {
      case SECOND:
        currentSettingsWindow = BRIGHTNESS;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case MINUTE:
        currentSettingsWindow = SECOND;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case HOUR:
        currentSettingsWindow = MINUTE;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case DAY:
        currentSettingsWindow = HOUR;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case MONTH:
        currentSettingsWindow = DAY;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      case YEAR:
        currentSettingsWindow = MONTH;
        drawFilledRect({0, 0}, 240, 50, COLOUR_BLACK);
        break;
      default:
        break;
    }
    return true;
  }
  
  void drawRects() {
    drawUnfilledRectWithChar({0, 60}, 115, 130, 8, COLOUR_RED, '-', 6);
    drawUnfilledRectWithChar({120, 60}, 115, 130, 8, COLOUR_GREEN, '+', 6);
  }
};
