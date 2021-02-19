#ifndef __CUTE_AUI__
#define __CUTE_AUI__

#include <Arduino.h>
#include <Functor.h>
#include "Utils.h"

#define DATA_RATE_DEFAULT 9600
#define COMMAND_BUFFER_SIZE 50
#define PARAMETER_DELIMITER ' '

const char CMD_TERMINATOR = '#';

enum FUNC_TYPE { func0, func1 };

struct CMD_FUNC_PAIR {
  FUNC_TYPE funcType;
  const char *cmd; 
  Functor0 func0;
  Functor1<int> func1;
};

class CUTE_AUI
{
  public:
    CUTE_AUI();

    void Init(HardwareSerial *port, unsigned short int);
    void WaitUnityCommand();
    void AddCmdFuncPair(CMD_FUNC_PAIR);
    void AddCommand(const char *, void (*func)());
    void AddCommand(const char *, void (*func)(int));

    void WriteToUnity(int);
    void WriteToUnity(String);
    void WriteLineToUnity(int);
    void WriteLineToUnity(String);
  
  private:
    HardwareSerial *port;
    CMD_FUNC_PAIR *commandList;
    unsigned short int commandListSize;
    unsigned short int commandListMaxSize;
    String outputBuffer = "";
    int paramOne;
};

#endif
