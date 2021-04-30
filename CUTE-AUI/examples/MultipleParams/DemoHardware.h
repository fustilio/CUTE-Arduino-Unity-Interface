#ifndef __DEMO_HARDWARE__
#define __DEMO_HARDWARE__

#include "CUTE_HardwareModule.h"

#define DEFAULT_INTERNAL_VALUE 500
#define DEFAULT_INTERVAL 50

class _DEMO_HARDWARE: public CUTE_HardwareModule
{
  public:
    // Constructor
    _DEMO_HARDWARE();

    void Init(CUTE_AUI);
    void ReadInternal(unsigned long currentMillis);
    void WriteInternal(int, int);

  private:
    int internalValue1;
    int internalValue2;
    unsigned intervalValue;

};

extern _DEMO_HARDWARE DEMO_HARDWARE;

#endif
