#include "CUTE_AUI.h"

// Constructor
CUTE_AUI::CUTE_AUI() {}

void CUTE_AUI::Init(HardwareSerial *serialPort, unsigned short int listMaxSize)
{
  port = serialPort;
  
  if (commandList != NULL) {
    free(commandList);
  }

  listMaxSize++;
  
  commandList = (CMD_FUNC_PAIR*)malloc(sizeof(CMD_FUNC_PAIR)*listMaxSize);
  commandListSize = 0;
  commandListMaxSize = listMaxSize;
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
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func0, cmd, makeFunctor((Functor0 *)0,func), nullptr};
  AddCmdFuncPair(cf_pair);
}

void CUTE_AUI::AddCommand(const char *cmd, void (*func)(int))
{ 
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func1, cmd, nullptr, makeFunctor((Functor1<int> *)0,func)};
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
      if (c == CMD_TERMINATOR) 
      {
        outputBuffer.trim();

        int separatorIndex = outputBuffer.indexOf(PARAMETER_DELIMITER);
        bool commandExecuted = false;
        
        // No space in command indicates
        if (separatorIndex < 0)
        {
          // Handle commands with no parameters
          for (unsigned short int i = 0; i < commandListSize; i++)
          {
            if (outputBuffer == commandList[i].cmd)
            {
              commandList[i].func0();
              commandExecuted = true;
              break;
            }
          }
        }
        else 
        {
          // Extract and parse first parameter into integer
          paramOne = atoi(outputBuffer.substring(separatorIndex + 1).c_str());
          outputBuffer = outputBuffer.substring(0, separatorIndex);
          
          // Handle commands with one parameter
          for (unsigned short int i = 0; i < commandListSize; i++)
          {
            if (outputBuffer == commandList[i].cmd)
            {
              commandList[i].func1(paramOne);
              commandExecuted = true;
              break;
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
