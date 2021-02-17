#include "Utils.h"


Smoother::Smoother(unsigned int numberOfReadings) : NUMBER_OF_READINGS(numberOfReadings)
{
    readIndex = 0;
    total = 0;

    readings = new int[NUMBER_OF_READINGS];
    
    // Init array for smoothing process used to read potentiometer
    for (int i = 0; i < NUMBER_OF_READINGS; i++)
    {
        readings[i] = 0;
    }
}

// Smoothing: get N readings and average it out
// Source: https://www.arduino.cc/en/tutorial/smoothing
int Smoother::Smooth(int input)
{
  total = total - readings[readIndex];

  readings[readIndex] = input;

  total = total + readings[readIndex];

  readIndex = readIndex + 1;

  if (readIndex >= NUMBER_OF_READINGS)
  {
    readIndex = 0;
  }

  return total / NUMBER_OF_READINGS;
}
