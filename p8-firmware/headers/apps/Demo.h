#pragma once

#include "WatchAppBase.h"
#include "../display.h"
/* 
  Random screen for messing with and testing stuff 
*/
class DemoScreen : public WatchAppBase {
 private:
  uint8_t charX, charY;
  char charToWrite = '~';

 public:
  void onInit() override {
    clearDisplay(true);
    writeNewChar({0, 0}, charToWrite);
  }
  void onUpdate() override {}

  uint8_t getScreenUpdateTimeMS() { return 1; }  //Fast update time
};