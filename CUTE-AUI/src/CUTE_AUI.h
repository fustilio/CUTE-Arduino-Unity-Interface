#ifndef __CUTE_AUI__
#define __CUTE_AUI__

#include <Arduino.h>
#include <Functor.h>
#include "Utils.h"

#define DATA_RATE_DEFAULT 9600
#define COMMAND_BUFFER_SIZE 50
#define PARAMETER_DELIMITER ' '

const char CMD_TERMINATOR = '#';

typedef Functor1<int> FtorType;

struct CMD_FUNC_PAIR {
  const char *cmd; 
  FtorType func;
};

class CUTE_AUI
{
  public:
    CUTE_AUI();

    void Init(HardwareSerial *port, unsigned int);
    void WaitUnityCommand();
    void AddCmdFuncPair(CMD_FUNC_PAIR);
    void AddCommand(const char *, void (*func)(int));

    void WriteToUnity(int);
    void WriteToUnity(String);
    void WriteLineToUnity(int);
    void WriteLineToUnity(String);
  
  private:
    HardwareSerial *port;
    CMD_FUNC_PAIR *commandList;
    unsigned int commandListSize;
    unsigned int commandListMaxSize;
    String outputBuffer = "";
    int paramOne;
};

extern CUTE_AUI;

#endif
