#include "DemoHardware.h"

_DEMO_HARDWARE DEMO_HARDWARE;

// Constructor
_DEMO_HARDWARE::_DEMO_HARDWARE() {}

void _DEMO_HARDWARE::Init(CUTE_AUI ca)
{
  this->ca = ca;

  internalValue = DEFAULT_INTERNAL_VALUE;
  intervalValue = DEFAULT_INTERVAL;
}

void _DEMO_HARDWARE::ReadInternal(unsigned long currentMillis)
{
  if (!active) return;

  if (currentMillis - previousMillis > intervalValue) // if duration has passed interval indicated previously
  {
    previousMillis = currentMillis; // save the last time serial check
    ca.WriteLineToUnity(internalValue); // write out the value in serial monitor, will be read by unity
  }
}

void _DEMO_HARDWARE::WriteInternal(int val)
{
  internalValue = val;

  ca.WriteToUnity("Demo hardware: Value written: "); // write out the value in serial monitor, will be read by unity
  ca.WriteLineToUnity(val); 
}
