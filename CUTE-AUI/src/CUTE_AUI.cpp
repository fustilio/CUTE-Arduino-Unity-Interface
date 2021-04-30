#include "CUTE_AUI.h"

// Constructor
CUTE_AUI::CUTE_AUI() {}

void CUTE_AUI::Init(
  HardwareSerial *serialPort, 
  unsigned short int listMaxSize)
{
  Init(serialPort, listMaxSize, DEFAULT_PARAMETER_DELIMITER, DEFAULT_COMMAND_TERMINATOR);
}


void CUTE_AUI::Init(
  HardwareSerial *serialPort, 
  unsigned short int listMaxSize, 
  char delimChar)
{
  Init(serialPort, listMaxSize, delimChar, DEFAULT_COMMAND_TERMINATOR);
}


void CUTE_AUI::Init(
  HardwareSerial *serialPort, 
  unsigned short int listMaxSize, 
  char delimChar,
  char endChar)
{
  port = serialPort;
  
  if (commandList != NULL) {
    free(commandList);
  }
  
  commandList = (CMD_FUNC_PAIR*)malloc(sizeof(CMD_FUNC_PAIR)*listMaxSize);
  commandListSize = 0;
  commandListMaxSize = listMaxSize;
  commandEndChar = endChar;
  commandDelimChar = delimChar;
}

void CUTE_AUI::AddCmdFuncPair(CMD_FUNC_PAIR func_pair)
{
  if (commandListSize < commandListMaxSize) {
    commandList[commandListSize++] = func_pair;
  } else {
    port->println("Error: Functor list is full");
  }
}

void CUTE_AUI::AddCommand(const char *cmd, void (*func)())
{ 
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func0, cmd, makeFunctor((Functor0 *)0,func), nullptr, nullptr};
  AddCmdFuncPair(cf_pair);
}

void CUTE_AUI::AddCommand(const char *cmd, void (*func)(int))
{ 
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func1, cmd, nullptr, makeFunctor((Functor1<int> *)0,func), nullptr};
  AddCmdFuncPair(cf_pair);
}

void CUTE_AUI::AddCommand(const char *cmd, void (*func)(int, int))
{
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func2, cmd, nullptr, nullptr, makeFunctor((Functor2<int, int> *)0,func)};
  AddCmdFuncPair(cf_pair);
}

// Wait for commands from Unity
void CUTE_AUI::WaitUnityCommand()
{ 
  if (port->available())
  {
    String str = port->readString();

    for (unsigned int i = 0; i < str.length(); i++) {
      char c = str.charAt(i);
  
      // end token, process command
      if (c == commandEndChar) 
      {
        outputBuffer.trim();

        bool commandExecuted = false;

        int separatorIndex = outputBuffer.lastIndexOf(commandDelimChar);
        unsigned char delimeterCount = 0;
        while (separatorIndex >= 0)
        {
          // overflow
          if (delimeterCount == PARAM_BUFFER_MAX_SIZE) {
            port->println("ERROR: Too many parameters!");
            
            outputBuffer = ""; // empty buffer
            return;
          }

          // Extract and parse parameter into integer
          paramBuffer[delimeterCount++] = atoi(outputBuffer.substring(separatorIndex + 1).c_str());
          outputBuffer = outputBuffer.substring(0, separatorIndex);
          separatorIndex = outputBuffer.lastIndexOf(commandDelimChar);
        }

        // be flexible about the input keyword
        outputBuffer.toUpperCase();
        
        for (unsigned short int i = 0; i < commandListSize; i++)
        {
          if (outputBuffer == commandList[i].cmd)
          {
            switch (delimeterCount)
            {
              case 0:
                commandList[i].func0();
                commandExecuted = true;
                break;
              case 1:
                commandList[i].func1(paramBuffer[0]);
                commandExecuted = true;
                break;
              case 2:
                commandList[i].func2(paramBuffer[1], paramBuffer[0]);
                commandExecuted = true;
                break;
              default:
                port->println("ERROR: Shouldn't reach here");
            }
          }
        }

        if (!commandExecuted)
        {
          port->println("ERROR: Invalid Command");
        }
        
        outputBuffer = ""; // empty buffer
      }
      else // otherwise, keep adding to buffer
      {
        outputBuffer += c;
      }
    }
  }
}

void CUTE_AUI::WriteToUnity(int i)
{
  port->print(i);
}

void CUTE_AUI::WriteToUnity(String str)
{
  port->print(str);
}

void CUTE_AUI::WriteLineToUnity(int i)
{
  port->println(i);
}

void CUTE_AUI::WriteLineToUnity(String str)
{
  port->println(str);
}
