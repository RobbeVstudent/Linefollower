#include "SerialCommand.h"
#include "EEPROMAnything.h"

#define SerialPort Serial
#define Baudrate 9600

#define MotorLeftForward 3
#define MotorLeftBackward 9

#define MotorRightForward 10
#define MotorRightBackward 11

//variabelen
SerialCommand sCmd(SerialPort); // SerialCommand object declaration
bool run = false;
unsigned long previous, calculationTime;

const int led = 12;
const int sensor[] = {A7, A6, A5, A4, A3, A2, A1, A0};
int normalised[8];
float debugPosition;
    
//EEPROM variabelen
struct param_t
{
  unsigned long cycleTime;
  int black[8];
  int white[8];
  int power;
  float diff;
  float kp;
  //ANDERE OP TE SLAAN VARIABELEN
}params;

void setup()
{
  pinMode(led,OUTPUT);
  for (int i=0;i<8;i++){
    pinMode(sensor[i], INPUT);
  }
  
  SerialPort.begin(Baudrate); // set serial baudrate at 9600

  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("run", onRun);
  sCmd.addCommand("stop", onStop);
  sCmd.addCommand("calibrate", onCalibrate);
  sCmd.setDefaultHandler(onUnknownCommand);
  
  EEPROM_readAnything(0, params);
  
  SerialPort.println("ready");
  SerialPort.print("cycleTime in EEPROM: ");
  SerialPort.println(params.cycleTime);
}

void loop() {
  sCmd.readSerial();
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;
    
    //NORMALISEREN:

    //SerialPort.print ("norm Value: ");
    for (int i=0;i<8;i++)
    {
      normalised[i] = map(analogRead(sensor[i]),params.black[i],params.white[i],0,1000);
    }

   //LOCALISEREN:
   float position;
   int index = 0;
   for (int i=1;i<8;i++) if (normalised[i] < normalised[index]) index = i;

   if (normalised[index] > 400)
   {
    run = false;
   }
   else 
   {
     if (index==0) position = -30;
     else if (index==7) position = 30;
     else
     {
       int sNul = normalised[index];
       int sMinEen = normalised[index-1];
       int sPlusEen = normalised[index+1];
    
       float b = (sPlusEen - sMinEen);
       b = b/2;
    
       float a = sPlusEen - b -sNul;
    
       position = -b / (2*a);
       position += index;
       position -= 3.5;
    
       position *= 10;
     }
     debugPosition = position;

     //Regelaar:
     float error = -position;
     float output = error * params.kp;

     output = constrain(output,-510,510);

     int powerLeft = 0;
     int powerRight = 0; 

     if (run) if (output >=0)
     {
      powerLeft = constrain(params.power + params.diff * output,-255,255);
      powerRight = constrain(powerLeft - output,-255,255);
      powerLeft = powerRight + output;
     }
     else
     {
      powerRight = constrain(params.power + params.diff * output,-255,255);
      powerLeft = constrain(powerLeft - output,-255,255);
      powerRight = powerRight + output;
     }
     analogWrite(MotorLeftForward,powerLeft > 0? powerLeft : 0);
     analogWrite(MotorLeftBackward,powerLeft < 0? -powerLeft : 0);
     analogWrite(MotorRightForward,powerRight > 0? powerRight : 0);
     analogWrite(MotorRightBackward,powerRight < 0? -powerRight : 0);
   }
 }
  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference; 
}
void onUnknownCommand(char *command)
{
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void onSet(){
  char* param = sCmd.next();
  char* value = sCmd.next();  

  if (strcmp(param, "cycle") == 0) params.cycleTime = atol(value); //set cycleTime
  else if (strcmp(param, "power") == 0) params.power = atol(value);
  else if (strcmp(param, "diff") == 0) params.diff = atof(value);
  else if (strcmp(param, "kp") == 0) params.kp = atof(value);

  EEPROM_writeAnything(0, params);
}

void onDebug(){
  SerialPort.print("cycle time: ");
  SerialPort.println(params.cycleTime);
 
  SerialPort.print("black: ");
  for (int i=i;i<8;i++)
  {
    SerialPort.print(params.black[i]);
    SerialPort.print (" ");
  }
  
  SerialPort.println();
  SerialPort.print("white: ");
  for (int i=i;i<8;i++)
  {
    SerialPort.print(params.white[i]);
    SerialPort.print (" ");
  }
  SerialPort.println();

  SerialPort.print("normalised: ");
  for (int i=0;i<8;i++)
  {
    SerialPort.print(normalised[i]);
    SerialPort.print(" ");
  }
  SerialPort.println();

  SerialPort.print("position: ");
  SerialPort.println(debugPosition);

  SerialPort.print("power: ");
  SerialPort.println(params.power);
  SerialPort.print("diff: ");
  SerialPort.println(params.diff);
  SerialPort.print("kp: ");
  SerialPort.println(params.kp);
  
  SerialPort.print("calculation time: "); //show biggest duration of cycle
  SerialPort.println(calculationTime);
  calculationTime = 0;
}

void onRun(){
  run = true;
  SerialPort.println("Let's go!");
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
}

void onStop(){
  run = false;
  SerialPort.println("Stopped");
}

void onCalibrate()
{
  char* param = sCmd.next();

  if (strcmp(param, "black") == 0)
  {
    SerialPort.print("start calibrating black... ");
    for (int i = 0; i < 8; i++) params.black[i]=analogRead(sensor[i]);
    SerialPort.println("done");
  }
  else if (strcmp(param, "white") == 0)
  {
    SerialPort.print("start calibrating white... ");    
    for (int i = 0; i < 8; i++) params.white[i]=analogRead(sensor[i]);  
    SerialPort.println("done");      
  }

  EEPROM_writeAnything(0, params);
}
