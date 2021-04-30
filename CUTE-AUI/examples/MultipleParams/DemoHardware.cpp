#include "DemoHardware.h"

_DEMO_HARDWARE DEMO_HARDWARE;

// Constructor
_DEMO_HARDWARE::_DEMO_HARDWARE() {}

void _DEMO_HARDWARE::Init(CUTE_AUI ca)
{
  this->ca = ca;

  internalValue1 = DEFAULT_INTERNAL_VALUE;
  internalValue2 = DEFAULT_INTERNAL_VALUE;
  
  intervalValue = DEFAULT_INTERVAL;
}

void _DEMO_HARDWARE::ReadInternal(unsigned long currentMillis)
{
  if (!active) return;

  if (currentMillis - previousMillis > intervalValue) // if duration has passed interval indicated previously
  {
    previousMillis = currentMillis;     // save the last time serial check
    ca.WriteToUnity(internalValue1); // write out the value in serial monitor, will be read by unity
    ca.WriteToUnity(", ");
    ca.WriteLineToUnity(internalValue2); 
  }
}

void _DEMO_HARDWARE::WriteInternal(int val1, int val2)
{
  internalValue1 = val1;
  internalValue2 = val2;

  ca.WriteToUnity("Demo hardware: Value1 written: "); 
  ca.WriteLineToUnity(internalValue1); 
  ca.WriteToUnity("Demo hardware: Value2 written: ");
  ca.WriteLineToUnity(internalValue2); 
}
