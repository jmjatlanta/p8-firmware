#pragma once

#include "WatchAppBase.h"
/* 
  Screen that allows rebooting and reboot to bootloader
 */
class PowerApp : public WatchAppBase {
 public:
  void onInit() override {
    clearDisplay(true);
    drawUnfilledRectWithChar({0, 0}, 70, 70, 5, COLOUR_WHITE, GLYPH_REBOOT_UNSEL, 4);
    drawUnfilledRectWithChar({85, 0}, 70, 70, 5, COLOUR_WHITE, GLYPH_BOOTLOADER_UNSEL, 4);
    drawUnfilledRect({170, 0}, 70, 70, 5, COLOUR_WHITE);
  }

  bool onTap(uint8_t x, uint8_t y) override {
    if (y < 70 && x < 70) {
      __DSB(); /* Ensure all outstanding memory accesses included
                  buffered write are completed before reset */

      //We need to make sure we write the correct key into vectkey otherwise the write will be ignored
      SCB->AIRCR = ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                    SCB_AIRCR_SYSRESETREQ_Msk);
      __DSB(); /* Ensure completion of memory access */

      for (;;) /* wait until reset */
      {
        __NOP();
      }
    } else if (x > 70 && x < 140 && y < 70) {
      //Enter the bootloader by setting the general purpose retention register to 1 and rebooting
      NRF_POWER->GPREGRET = 0x01;
      NVIC_SystemReset();
    }
    return true;
  }
};