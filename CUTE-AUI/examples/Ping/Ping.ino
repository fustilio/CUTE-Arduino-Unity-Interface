#include <CUTE_AUI.h>

/*************************** SETTINGS *******************************/
#define DATA_RATE 9600
#define NUMBER_OF_COMMANDS 1

/*************************** VARIABLES *******************************/
CUTE_AUI ca;

/*************************** COMMAND HOOKS ********************************************/
#define COMMAND_STRING_PING "PING"

void CommandPing()
{
  Serial.println("Ping");
}

/*************************** SETUP *******************************/
void setup()
{
  Serial.begin(DATA_RATE); // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(1);
  
  ca.Init(&Serial, NUMBER_OF_COMMANDS);
  ca.AddCommand(COMMAND_STRING_PING, CommandPing);
  
  delay(500);
}

/**************************** MAIN LOOP *******************************/
void loop()
{
  ca.WaitUnityCommand();
}
