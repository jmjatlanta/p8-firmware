#include "pinoutP8.h"
#include "watchdog.h"
#include "ioControl.h"
#include "fastSPI.h"
#include "display.h"
#include "p8Time.h"

void setup() {
  delay(500); //Coldboot cooldown time
  initIO(); //Init GPIOs
  if (getButton()){ //If the button is held at boot, go to the bootloader
    NRF_POWER->GPREGRET = 0x01;
    NVIC_SystemReset();
  }
  initWatchdog(); //Start the watchdog
  initFastSPI(); //Initialize EasyDMA SPI
  initDisplay(); //Initialize display
  randomTests();
}

void randomTests(){
  setTimeWrapper(2020,6,17,21,03,00);
}

void loop(){
  if (!getButton()){
    feedWatchdog();
  }
  writeString(20,20,3,getTimeWithSecs());
  writeString(20,45,3,getDate());
}