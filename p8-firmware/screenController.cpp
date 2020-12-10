#include "headers/screenController.h"

#define NUM_SCREENS 6

uint8_t screenUpdateMS = 20;  //Screen update time, defaults to 20ms (50hz)

long lastScreenUpdate = 0;
/*
  Similar to ATCWatch, an instance of every screen will be instantiated at bootup
  There will be a pointer to the current screen which will have the methods called on it
  Finally a screen will be switched by moving the pointer to a different instance of a different screen
*/
TimeApp timeScreen;
StopwatchApp stopWatchScreen;
SettingsApp timeDateSetScreen;
DemoScreen demoScreen;
InfoApp infoScreen;
PowerApp powerScreen;

int currentHomeScreenIndex = 0;
WatchAppBase* homeScreens[NUM_SCREENS] = {&timeScreen, &stopWatchScreen, &timeDateSetScreen, &infoScreen, &powerScreen, &demoScreen};

WatchAppBase* currentScreen = homeScreens[currentHomeScreenIndex];

/*
  This is called whenever a new screen is loaded
  It will setup the screen and draw the indicator and update the screen refresh time
*/
void initScreen() {
  currentScreen->onInit();                             //Call screenSetup() on the current screen
  drawAppIndicator();                                       //Draw the app bar
  screenUpdateMS = currentScreen->getScreenUpdateTimeMS();  //Set the current screen update time
}

/* 
  Move to the right screen if the current screen doesn't have a handler for the right swipe,
  else call that handler 
*/
void handleLeftSwipe() {
  if (currentScreen->onSwipeLeft() == false)
    nextScreen();
}

/* 
  Move to the left screen if the current screen doesn't have a handler for the left swipe,
  else call that handler
 */
void handleRightSwipe() {
  if (currentScreen->onSwipeRight() == false)
    prevScreen();
}

/* 
  Move to the left screen if you are not at screen 0
 */
void prevScreen() {
  if (currentHomeScreenIndex != 0) {
    currentScreen->onHide();  //Call 'destructor' for current screen
    currentHomeScreenIndex--;
    currentScreen = homeScreens[currentHomeScreenIndex];
    initScreen();
  }
}

/* 
  Move to the right screen if you aren't at the rightmost screen
 */
void nextScreen() {
  if (currentHomeScreenIndex != NUM_SCREENS - 1) {
    currentScreen->onHide();  //Call 'destructor' for current screen
    currentHomeScreenIndex++;
    currentScreen = homeScreens[currentHomeScreenIndex];
    initScreen();
  }
}

/*
  Since the main UI doesn't need a swipe up or down event (yet), just call the handler of the current screen
*/
void handleUpSwipe() {
  currentScreen->onSwipeUp();
}

/* 
  Ditto as above 
*/
void handleDownSwipe() {
  currentScreen->onSwipeDown();
}

/* 
  A button press will ALWAYS return to the time screen NO MATTER WHAT (no application 
  can have access to a button press event)
 */
void handleButtonPress() {
  if (currentHomeScreenIndex != 0) {
    currentHomeScreenIndex = 0;
    currentScreen = homeScreens[currentHomeScreenIndex];
    initScreen();
  }
}

/* 
  Function called when a tap event is received by the interrupt handler 
  The parameters are the x and y coords of the tap
*/
void handleTap(uint8_t x, uint8_t y) {
  if (y < 212) {  //If the tap is on the main application
    currentScreen->onTap(x, y);
  } else {  //Else we are pressing in the app drawer buttons, so go to the prev or next screen
    if (x < 100) {
      prevScreen();
    } else if (x > 160) {
      nextScreen();
    }
  }
}

/* 
  Sleep when we receive a long tap 
*/
void handleLongTap(uint8_t x, uint8_t y) {
  if (currentScreen->onLongTap(x, y) == false) {  //Make sure the current screen doesn't implement the long tap
    enterSleep();
  }
}

/* 
  This method is called AFAP by the main loop() in p8-firmware.ino
  The loop method of a screen should be as efficient as possible
    For example if any graphics are used, they should be drawn in setup rather than being redrawn every loop
 */
void screenControllerLoop() {
  if (millis() - lastScreenUpdate > screenUpdateMS) {
    //The refresh time is variable depending on the current screen
    currentScreen->onUpdate();
    lastScreenUpdate = millis();
  }
}

/*
Draw an indicator as to which screen you are currently on
*/
void drawAppIndicator() {
  drawFilledRect({0, 213}, 240, 1, COLOUR_WHITE);
  uint8_t indicatorFontSize = 3;
  uint8_t widthOfIndicator = NCHAR_WIDTH(NUM_SCREENS, 3);
  uint8_t startOfString = 120 - (widthOfIndicator / 2);
  //Draw the current screen indicators
  drawChar({startOfString + (0 * indicatorFontSize * FONT_WIDTH) + (0 * indicatorFontSize), 216}, indicatorFontSize, (currentHomeScreenIndex == 0) ? GLYPH_CLOCK_SEL : GLYPH_CLOCK_UNSEL, COLOUR_WHITE, COLOUR_BLACK);
  drawChar({startOfString + (1 * indicatorFontSize * FONT_WIDTH) + (1 * indicatorFontSize), 216}, indicatorFontSize, (currentHomeScreenIndex == 1) ? GLYPH_STOPWATCH_SEL : GLYPH_STOPWATCH_UNSEL, COLOUR_WHITE, COLOUR_BLACK);
  drawChar({startOfString + (2 * indicatorFontSize * FONT_WIDTH) + (2 * indicatorFontSize), 216}, indicatorFontSize, (currentHomeScreenIndex == 2) ? GLYPH_SETTINGS_SEL : GLYPH_SETTINGS_UNSEL, COLOUR_WHITE, COLOUR_BLACK);
  drawChar({startOfString + (3 * indicatorFontSize * FONT_WIDTH) + (3 * indicatorFontSize), 216}, indicatorFontSize, (currentHomeScreenIndex == 3) ? GLYPH_INFO_SEL : GLYPH_INFO_UNSEL, COLOUR_WHITE, COLOUR_BLACK);
  drawChar({startOfString + (4 * indicatorFontSize * FONT_WIDTH) + (4 * indicatorFontSize), 216}, indicatorFontSize, (currentHomeScreenIndex == 4) ? GLYPH_POWER_SEL : GLYPH_POWER_UNSEL, COLOUR_WHITE, COLOUR_BLACK);
  drawChar({startOfString + (5 * indicatorFontSize * FONT_WIDTH) + (5 * indicatorFontSize), 216}, indicatorFontSize, (currentHomeScreenIndex == 5) ? GLYPH_DATA_SEL : GLYPH_DATA_UNSEL, COLOUR_WHITE, COLOUR_BLACK);
  //Draw the "can scroll left/right" indicators in the corners of the screen
  switch (currentHomeScreenIndex) {
    case 0:
      drawChar({0, 216}, indicatorFontSize, GLYPH_ARROW_LEFT, 0b1000010000010000, COLOUR_BLACK);
      drawChar({225, 216}, indicatorFontSize, GLYPH_ARROW_RIGHT, COLOUR_WHITE, COLOUR_BLACK);
      break;
    case 1:
    case 2:
    case 3:
    case 4:
      drawChar({0, 216}, indicatorFontSize, GLYPH_ARROW_LEFT, COLOUR_WHITE, COLOUR_BLACK);
      drawChar({225, 216}, indicatorFontSize, GLYPH_ARROW_RIGHT, COLOUR_WHITE, COLOUR_BLACK);
      break;
    case 5:
      drawChar({0, 216}, indicatorFontSize, GLYPH_ARROW_LEFT, COLOUR_WHITE, COLOUR_BLACK);
      drawChar({225, 216}, indicatorFontSize, GLYPH_ARROW_RIGHT, 0b1000010000010000, COLOUR_BLACK);
      break;
  }
}