#ifndef __CUTE_HW__
#define __CUTE_HW__

#include "CUTE_AUI.h"

class CUTE_HardwareModule {

  public:
    CUTE_HardwareModule();
    bool IsActive();
    void SetActive(bool);
    
  protected:
    unsigned long previousMillis = 0;
    bool active = false;
    CUTE_AUI ca;
 };

#endif
