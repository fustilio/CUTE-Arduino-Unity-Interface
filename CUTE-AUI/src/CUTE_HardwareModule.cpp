#include "CUTE_HardwareModule.h"

// Constructor
CUTE_HardwareModule::CUTE_HardwareModule() {
  previousMillis = 0;
}

bool CUTE_HardwareModule::IsActive() {
   return active;
}


void CUTE_HardwareModule::SetActive(bool val)
{
    active = val;
}
