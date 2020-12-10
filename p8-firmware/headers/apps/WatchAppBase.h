#pragma once

#include <cstdint>

class WatchAppBase 
{
public:
   /***
    * Initialize the app for the first time
    */
   virtual void onInit() {}
   /***
    * Display the application
    */
   virtual void onShow() {}
   /***
    * The application will be replaced by another on the screen
    */ 
   virtual void onHide() {}
   /***
    * Do whatever periodic processing is necessary
    */
   virtual void onUpdate() {}
   /***
    * Handle a tap on the screen
    * @param x the x coordinate of the tap
    * @param y the y coordinate of the tap
    * @returns true if the action was handled, false if not
    */
   virtual bool onTap(uint8_t x, uint8_t y) { return false; }
   /****
    * Handle a long-tap on the screen
    * @param x the x coordinate
    * @param y the y coordinate
    * @returns true if the action was handled
    */
   virtual bool onLongTap(uint8_t x, uint8_t y) { return false; }
   /***
    * Handle the user swiping from right to left
    * @returns true if the action was handled
    */
   virtual bool onSwipeLeft() { return false; }
   /***
    * Handle the user swiping from left to right
    * @returns true if the action was handled
    */
   virtual bool onSwipeRight() { return false; }
   /***
    * Handle the user swiping from bottom to top
    * @returns true if the action was handled
    */
   virtual bool onSwipeUp() { return false; }
   /***
    * Handle the user swiping from top to bottom
    * @returns true if the action was handled
    */
   virtual bool onSwipeDown() { return false; }
   /***
    * Reports how often onUpdate should be called (approximate)
    * @returns the screen update time in milliseconds
    */
   virtual uint8_t getScreenUpdateTimeMS() { return 20; }
};
