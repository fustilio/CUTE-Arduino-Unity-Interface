#include "DemoHardware.h"

_DEMO_HARDWARE DEMO_HARDWARE;

// Constructor
_DEMO_HARDWARE::_DEMO_HARDWARE() {}

void _DEMO_HARDWARE::Init(CUTE_AUI ca)
{
  this->ca = ca;

  for (int i = 0; i < INTERNAL_VALUES_MAX_SIZE; i++) 
  {
    internalValues[i] = DEFAULT_INTERNAL_VALUE;
  }
  
  intervalValue = DEFAULT_INTERVAL;
}

void _DEMO_HARDWARE::ReadInternal(unsigned long currentMillis)
{
  if (!active) return;

  if (currentMillis - previousMillis > intervalValue) // if duration has passed interval indicated previously
  {
    previousMillis = currentMillis;     // save the last time serial check
    PrintInternal();
  }
}

void _DEMO_HARDWARE::PrintInternal()
{
  ca.WriteToUnity("Demo hardware values: "); 
  for (int i = 0; i < INTERNAL_VALUES_MAX_SIZE; i++) 
  {
    ca.WriteToUnity(internalValues[i]);
    ca.WriteToUnity(" ");
  }

  ca.WriteLineToUnity("");
}

void _DEMO_HARDWARE::WriteInternal(int val)
{
  internalValues[0] = val;
  PrintInternal();
}


void _DEMO_HARDWARE::WriteInternal(int val1, int val2)
{
  internalValues[1] = val2;
  WriteInternal(val1);
}

void _DEMO_HARDWARE::WriteInternal(int val1, int val2, int val3)
{
  internalValues[2] = val3;
  WriteInternal(val1, val2);
}

void _DEMO_HARDWARE::WriteInternal(int val1, int val2, int val3, int val4)
{
  internalValues[3] = val4;
  WriteInternal(val1, val2, val3);
}
