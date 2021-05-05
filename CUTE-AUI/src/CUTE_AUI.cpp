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
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func0, cmd, makeFunctor((Functor0 *)0,func), nullptr, nullptr, nullptr, nullptr};
  AddCmdFuncPair(cf_pair);
}

void CUTE_AUI::AddCommand(const char *cmd, void (*func)(int))
{ 
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func1, cmd, nullptr, makeFunctor((Functor1<int> *)0,func), nullptr, nullptr, nullptr};
  AddCmdFuncPair(cf_pair);
}

void CUTE_AUI::AddCommand(const char *cmd, void (*func)(int, int))
{
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func2, cmd, nullptr, nullptr, makeFunctor((Functor2<int, int> *)0,func), nullptr, nullptr};
  AddCmdFuncPair(cf_pair);
}


void CUTE_AUI::AddCommand(const char *cmd, void (*func)(int, int, int))
{
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func3, cmd, nullptr, nullptr, nullptr, makeFunctor((Functor3<int, int, int> *)0,func), nullptr};
  AddCmdFuncPair(cf_pair);
}

void CUTE_AUI::AddCommand(const char *cmd, void (*func)(int, int, int, int))
{
  CMD_FUNC_PAIR cf_pair = {FUNC_TYPE::func4, cmd, nullptr, nullptr, nullptr, nullptr, makeFunctor((Functor4<int, int, int, int> *)0,func)};
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
        
        String commandKey = "";
        String paramStringBuffer = "";
        CMD_FUNC_PAIR *cmdFuncPair = nullptr;
        bool commandFound = false;
        int commandNumberParams = 0;
        bool error = false;
        
        int splitIndex = outputBuffer.indexOf(commandDelimChar);
        if (splitIndex < 0) // EXAMPLE COMMAND: "FOO"
        {
          commandKey = outputBuffer;
        }
        else // EXAMPLE COMMAND: "FOO 123 456" => "FOO" and "123 456"
        {
          commandKey = outputBuffer.substring(0, splitIndex);
          paramStringBuffer = outputBuffer.substring(splitIndex + 1);
        }
        
        // be flexible about the command keyword
        commandKey.toUpperCase();

        for (unsigned short int i = 0; i < commandListSize; i++)
        {
          if (commandKey == commandList[i].cmd)
          {
            cmdFuncPair = &commandList[i];
            commandNumberParams = (int) cmdFuncPair->funcType;
            commandFound = true;
            break;
          }
        }

        if (!commandFound)
        {
          port->print("ERROR: Can't find command with name ");
          port->println(commandKey);
        }
        else
        {
          unsigned char paramCount = 0;
          int separatorIndex;
          while (paramStringBuffer.length() > 0)
          {
            if (paramCount >= commandNumberParams) 
            {
              port->print("ERROR: Too many parameters, expected only ");
              port->print(commandNumberParams);
              port->println(" parameter(s)");
              error = true;
              break;
            }

            separatorIndex = paramStringBuffer.indexOf(commandDelimChar);
            if (separatorIndex >= 0)
            {
              // Extract and parse parameter into integer
              paramBuffer[paramCount++] = atoi(paramStringBuffer.substring(0, separatorIndex).c_str());
              paramStringBuffer = paramStringBuffer.substring(separatorIndex + 1);
              paramStringBuffer.trim(); // to remove extra spaces
            }
            else
            {
              // add the last element into buffer
              paramBuffer[paramCount++] = atoi(paramStringBuffer.c_str());
              paramStringBuffer = "";
            }
          }

          if (paramCount < commandNumberParams)
          {
            port->print("ERROR: Too few parameters, expected ");
            port->print(commandNumberParams);
            port->println(" parameter(s)");
            error = true;
          }

          if (!error) {
            switch (cmdFuncPair->funcType)
            {
              case FUNC_TYPE::func0:
                cmdFuncPair->func0();
                break;
              case FUNC_TYPE::func1:
                cmdFuncPair->func1(paramBuffer[0]);
                break;
              case FUNC_TYPE::func2:
                cmdFuncPair->func2(paramBuffer[0], paramBuffer[1]);
                break;
              case FUNC_TYPE::func3:
                cmdFuncPair->func3(paramBuffer[0], paramBuffer[1], paramBuffer[1]);
                break;
              case FUNC_TYPE::func4:
                cmdFuncPair->func4(paramBuffer[0], paramBuffer[1], paramBuffer[2], paramBuffer[3]);
                break;
              default:
                // shouldn't ever reach here
                port->println("ERROR: Internal library error");
            }
          }
          else
          {
            port->println("ERROR: Command execution failed");
          }
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
