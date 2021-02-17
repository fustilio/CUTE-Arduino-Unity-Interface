/*************************** HEADERS *******************************/
#include <CUTE_AUI.h> // Library Header file
#include "DemoHardware.h" // Project Header file

/*************************** SETTINGS *******************************/
// The rate that is agreed between devices accessing the serial port
#define DATA_RATE 9600
// The maximum number of commands that the CUTE_AUI object can store
#define NUMBER_OF_COMMANDS 4

/*************************** VARIABLES ******************************/
unsigned long currentMillis;
CUTE_AUI ca;

/************************* COMMAND HOOKS ****************************/
// The command strings that invokes the corresponding command
#define COMMAND_STRING_PING "PING"
#define COMMAND_STRING_DEMO_ON "DEMO_ON"
#define COMMAND_STRING_DEMO_OFF "DEMO_OFF"
#define COMMAND_STRING_DEMO_WRITE "WRITE"

/*********************** COMMAND DEFINITIONS*************************/
// Basic command to signal that a two-way connection has been established
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

// Command that writes to a internal variable of the demo hardware object
void CommandWriteVal(int val)
{
  Serial.print("Demo hardware: Write value: ");
  Serial.println(val);
  DEMO_HARDWARE.WriteInternal(val);
}

/**************************** SETUP *********************************/
void setup()
{
  Serial.begin(DATA_RATE); // opens serial port, sets data rate to 9600 bps

  
  ca.Init(&Serial, NUMBER_OF_COMMANDS); // Initialize the CUTE_AUI object
  // Configure the command string and command to be invoked
  ca.AddCommand(COMMAND_STRING_PING, CommandPing);
  ca.AddCommand(COMMAND_STRING_DEMO_ON, CommandDemoOn);
  ca.AddCommand(COMMAND_STRING_DEMO_OFF, CommandDemoOff);
  ca.AddCommand(COMMAND_STRING_DEMO_WRITE, CommandWriteVal);

  // Initialize demo hardware
  DEMO_HARDWARE.Init(ca);
}

/*************************** MAIN LOOP ********************************/
void loop()
{
  // The CUTE_AUI object listens for commands on the serial port
  ca.WaitUnityCommand();
  
  currentMillis = millis(); // get current time elapsed
  // invoke a demo function that reads an internal variable and prints to serial
  DEMO_HARDWARE.ReadInternal(currentMillis); 
}
