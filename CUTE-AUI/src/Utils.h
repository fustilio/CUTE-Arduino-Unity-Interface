#ifndef __CUTE_UTILS__
#define __CUTE_UTILS__

#include <ctype.h>
#include <string.h>

class Smoother
{
  public:
    Smoother(unsigned int numberOfReadings);
    int Smooth(int input);

  private:
    unsigned int NUMBER_OF_READINGS;
    unsigned int readIndex;
    signed int total;
    int* readings; // the readings from the analog input

};

#endif
