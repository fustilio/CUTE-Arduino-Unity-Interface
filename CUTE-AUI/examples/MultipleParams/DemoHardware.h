#ifndef __DEMO_HARDWARE__
#define __DEMO_HARDWARE__

#include "CUTE_HardwareModule.h"

#define DEFAULT_INTERNAL_VALUE 500
#define DEFAULT_INTERVAL 50
#define INTERNAL_VALUES_MAX_SIZE 4

class _DEMO_HARDWARE: public CUTE_HardwareModule
{
  public:
    // Constructor
    _DEMO_HARDWARE();

    void Init(CUTE_AUI);
    void ReadInternal(unsigned long currentMillis);
    void PrintInternal();
    void WriteInternal(int);
    void WriteInternal(int, int);
    void WriteInternal(int, int, int);
    void WriteInternal(int, int, int, int);


  private:
    int internalValues[INTERNAL_VALUES_MAX_SIZE];
    unsigned intervalValue;

};

extern _DEMO_HARDWARE DEMO_HARDWARE;

#endif
