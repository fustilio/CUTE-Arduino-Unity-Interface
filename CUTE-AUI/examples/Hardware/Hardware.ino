#include <CUTE_AUI.h>
#include "DemoHardware.h"

/*************************** SETTINGS *******************************/
#define DATA_RATE 9600
#define NUMBER_OF_COMMANDS 3

/*************************** VARIABLES *******************************/
unsigned long currentMillis;
CUTE_AUI ca;

/*************************** COMMAND HOOKS ********************************************/
#define COMMAND_STRING_PING "PING"
#define COMMAND_STRING_DEMO_ON "DEMO_ON"
#define COMMAND_STRING_DEMO_OFF "DEMO_OFF"
#define COMMAND_STRING_DEMO_WRITE "WRITE"


void CommandPing()
{
  Serial.println("Hardware.ino: Ping");
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

void CommandWriteVal(int val)
{
  Serial.print("Demo hardware: Write val: ");
  Serial.println(val);
  DEMO_HARDWARE.WriteInternal(val);
}

/*************************** SETUP *******************************/
void setup()
{
  Serial.begin(DATA_RATE); // opens serial port, sets data rate to 9600 bps
  
  ca.Init(&Serial, NUMBER_OF_COMMANDS);
  ca.AddCommand(COMMAND_STRING_PING, CommandPing);
  ca.AddCommand(COMMAND_STRING_DEMO_ON, CommandDemoOn);
  ca.AddCommand(COMMAND_STRING_DEMO_OFF, CommandDemoOff);
  ca.AddCommand(COMMAND_STRING_DEMO_WRITE, CommandWriteVal);

  DEMO_HARDWARE.Init(ca);
}

/**************************** MAIN LOOP *******************************/
void loop()
{
  ca.WaitUnityCommand();

  currentMillis = millis();
  DEMO_HARDWARE.ReadInternal(currentMillis);
}
