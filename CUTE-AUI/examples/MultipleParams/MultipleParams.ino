#include <CUTE_AUI.h>
#include "DemoHardware.h"

/*************************** SETTINGS *******************************/
#define DATA_RATE 9600
#define NUMBER_OF_COMMANDS 8

/*************************** VARIABLES *******************************/
unsigned long currentMillis;
CUTE_AUI ca;  

/*************************** COMMAND HOOKS ********************************************/
#define COMMAND_STRING_PING "PING"
#define COMMAND_STRING_DEMO_ON "DEMO_ON"
#define COMMAND_STRING_DEMO_OFF "DEMO_OFF"
#define COMMAND_STRING_DEMO_READ "READ"
#define COMMAND_STRING_DEMO_WRITE1 "WRITE1"
#define COMMAND_STRING_DEMO_WRITE2 "WRITE2"
#define COMMAND_STRING_DEMO_WRITE3 "WRITE3"
#define COMMAND_STRING_DEMO_WRITE4 "WRITE4"


void CommandPing()
{
  Serial.println("MultipleParams.ino: Ping");
}

void CommandDemoOn()
{
  Serial.println("Demo hardware: On");
  DEMO_HARDWARE.SetActive(true);
}

void CommandDemoOff()
{
  Serial.println("Demo hardware: Off");
  DEMO_HARDWARE.SetActive(false);
}


void CommandRead()
{
  Serial.println("Demo hardware: Read");
  DEMO_HARDWARE.PrintInternal();
}


void CommandWrite1Val(int val)
{
  Serial.print("Demo hardware write values: ");
  Serial.println(val);
  DEMO_HARDWARE.WriteInternal(val);
}

void CommandWrite2Val(int val1, int val2)
{
  Serial.print("Demo hardware write values: ");
  Serial.println(val1);
  Serial.print(", ");
  Serial.println(val2);
  DEMO_HARDWARE.WriteInternal(val1, val2);
}

void CommandWrite3Val(int val1, int val2, int val3)
{
  Serial.print("Demo hardware write values: ");
  Serial.print(val1);
  Serial.print(", ");
  Serial.print(val2);
  Serial.print(", ");
  Serial.println(val3);
  DEMO_HARDWARE.WriteInternal(val1, val2, val3);
}


void CommandWrite4Val(int val1, int val2, int val3, int val4)
{
  Serial.print("Demo hardware write values: ");
  Serial.print(val1);
  Serial.print(", ");
  Serial.print(val2);
  Serial.print(", ");
  Serial.print(val3);
  Serial.print(", ");
  Serial.println(val4);
  DEMO_HARDWARE.WriteInternal(val1, val2, val3, val4);
}



/*************************** SETUP *******************************/
void setup()
{
  Serial.begin(DATA_RATE); // opens serial port, sets data rate to 9600 bps
  
  ca.Init(&Serial, NUMBER_OF_COMMANDS);
  ca.AddCommand(COMMAND_STRING_PING, CommandPing);
  ca.AddCommand(COMMAND_STRING_DEMO_ON, CommandDemoOn);
  ca.AddCommand(COMMAND_STRING_DEMO_OFF, CommandDemoOff);
  ca.AddCommand(COMMAND_STRING_DEMO_READ, CommandRead);
  ca.AddCommand(COMMAND_STRING_DEMO_WRITE1, CommandWrite1Val);
  ca.AddCommand(COMMAND_STRING_DEMO_WRITE2, CommandWrite2Val);
  ca.AddCommand(COMMAND_STRING_DEMO_WRITE3, CommandWrite3Val);
  ca.AddCommand(COMMAND_STRING_DEMO_WRITE4, CommandWrite4Val);

  DEMO_HARDWARE.Init(ca);
}

/**************************** MAIN LOOP *******************************/
void loop()
{
  ca.WaitUnityCommand();

  currentMillis = millis();
  DEMO_HARDWARE.ReadInternal(currentMillis);
}
