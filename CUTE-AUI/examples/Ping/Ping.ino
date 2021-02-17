/*************************** HEADERS *******************************/
#include <CUTE_AUI.h> // Library Header file

/*************************** SETTINGS *******************************/
// The rate that is agreed between devices accessing the serial port 
#define DATA_RATE 9600
// The maximum number of commands that the CUTE_AUI object can store
#define NUMBER_OF_COMMANDS 1 

/*************************** VARIABLES ******************************/
CUTE_AUI ca;

/************************* COMMAND HOOKS ****************************/
// The command string invokes the corresponding command
#define COMMAND_STRING_PING "PING"  


/*********************** COMMAND DEFINITIONS*************************/
// Basic command to signal that a two-way connection has been established
void CommandPing()
{
  Serial.println("Ping");
}

/**************************** SETUP *********************************/
void setup()
{
  Serial.begin(DATA_RATE); // Opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(1);

  ca.Init(&Serial, NUMBER_OF_COMMANDS);  // Initialize the CUTE_AUI object

  // Configure the command string and command to be invoked
  ca.AddCommand(COMMAND_STRING_PING, CommandPing);
  
  delay(500);
}

/*************************** MAIN LOOP ********************************/
void loop()
{
  // The CUTE_AUI object listens for commands on the serial port
  ca.WaitUnityCommand();
}
