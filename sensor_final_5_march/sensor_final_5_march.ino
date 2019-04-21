

//MEGA --> 0,1
//NODE MCU --> RX,TX        -->  TX-RX ,, RX-TX

//NEED TO GET KEYSTROKES FROM KEYPAD

#include <dht.h>
#include<Keypad.h>


#include <LiquidCrystal.h>
#define IRSENSOR_PIN 50
#define PIRSENSOR_PIN 51
#define TEMPERATURE_PIN A11
#define HUMIDITY_PIN A9
#define SWITCH_PIN 31
#define VOLTAGE_SENSOR_PIN A7
#define BAROMETRIC_SENSOR_PIN A5
#define RAIN_SENSOR_PIN 35


uint8_t first_menu ;



const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char Keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {26,28,30,32}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {34, 36,38};


Keypad selectionKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(12, 9, 8, 7,6, 5);



boolean verbose = false;
boolean lverbose = true;
void setup() {
    pinMode(IRSENSOR_PIN,INPUT);
    pinMode(PIRSENSOR_PIN,INPUT);
    pinMode(TEMPERATURE_PIN,INPUT);
    pinMode(HUMIDITY_PIN,INPUT);
    pinMode(VOLTAGE_SENSOR_PIN,INPUT);
    pinMode(SWITCH_PIN,INPUT);
    pinMode(BAROMETRIC_SENSOR_PIN,INPUT);
    pinMode(RAIN_SENSOR_PIN,INPUT);
    Serial.begin(9600);
	  lcd.begin(16,2);
	  lcd.setCursor(3,0);
	  lcd.print("..IoT Based");
	  lcd.print("Sensors..");
	  delay(3000);

}

void loop() {
  openFirstMenu();
  

}

void openFirstMenu()
{
	if(verbose)
	{
	Serial.println("1.IR SENSOR");
	Serial.println("2.PIR SENSOR");
	Serial.println("3.TEMPERATURE SENSOR");
	Serial.println("4.HUMIDITY SENSOR");
	Serial.println("5.BAROMETRIC SENSOR");
	Serial.println("6.SWITCH");
	Serial.println("7.RAIN SENSOR");
	Serial.println("8.VOLTAGE SENSOR");
	}
	
	//Screen 1
	lcd.setCursor(0,0);
	lcd.print("1.IR");
	lcd.setCursor(8,0);
	lcd.print("2.PIR");
	lcd.setCursor(0,1);
	lcd.print("3.TEMP");
	lcd.setCursor(8,1);
	lcd.print("4.HUMID");

  delay(6000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("5.SWITCH");
  lcd.setCursor(0,1);
  lcd.print("6.BAROMETRY");
  lcd.setCursor(8,0);
  lcd.print("7.RAIN");
  lcd.setCursor(12,1);
  lcd.print("8.VOLTS");
  
	char key = selectionKeypad.getKey();

if(key) 

{

switch (key)

{

  case '1':

  Serial.println(key);
  getIR_readings();
  escapeMenu();
  break;

  case '2':

  Serial.println(key);
  getPIR_readings();
  escapeMenu();

  break;

  case '3':

  Serial.println(key);
  getTEMPERATURE_readings();
  escapeMenu();

  break;

  case '4':

  Serial.println(key);
  getHUMIDITY_readings();
  escapeMenu();

  break;

  case '5':

  Serial.println(key);
  getBAROMETRIC_readings();
  escapeMenu();

  break;

  case '6':

  Serial.println(key);
  getSWITCH_readings();
  escapeMenu();

  break;

  case '7':

  Serial.println(key);
  getRAIN_readings();
  escapeMenu();

  break;

  case '8':

  Serial.println(key);
  getVOLTAGE_readings();
  escapeMenu();

  break;

  case '9':

  Serial.println(key);

  break;

  case '0':

  Serial.println(key);
  openFirstMenu();

  break;

  default:

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("INVALID INPUT");
  openFirstMenu();

  }

  }
	
}



void getIR_readings()
{
	int IRSensorValues;
  if( digitalRead(IRSENSOR_PIN)==0)
  {
    
    IRSensorValues = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("IR SENSOR");
    lcd.setCursor(0,1);
    lcd.print(IRSensorValues);
  }
  else
  {
    IRSensorValues = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("IR SENSOR");
    lcd.setCursor(0,1);
    lcd.print(IRSensorValues);
  }
  if(verbose)
  {
  Serial.println("IR :");
  Serial.println(IRSensorValues);
  }

    transmitDigitalDataToNodeMCU("IR : ",IRSensorValues);

}

void getPIR_readings()
{
	int PIRSensorValues;
  if( digitalRead(PIRSENSOR_PIN)==0)
  {
    PIRSensorValues = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PIR SENSOR");
    lcd.setCursor(0,1);
    lcd.print(PIRSensorValues);
  }
  else
  {
    PIRSensorValues = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PIR SENSOR");
    lcd.setCursor(0,1);
    lcd.print(PIRSensorValues);
  }
  if(verbose)
  {
  Serial.println("PIR :");
  Serial.println(PIRSensorValues);
  delay(1000);
  }

   // transmitDigitalDataToNodeMCU(IRSensorValues);
}

void getTEMPERATURE_readings()
{
	float TEMPERATURESensorValues;
	TEMPERATURESensorValues = analogRead(TEMPERATURE_PIN);
	TEMPERATURESensorValues = (TEMPERATURESensorValues * 500)/ 1024;
	
	if(verbose){
	Serial.print("Temperature = ");
	Serial.print(TEMPERATURESensorValues);
	Serial.print("C");
	delay(1000);
	}

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE SENSOR");
    lcd.setCursor(0,1);
    lcd.print(TEMPERATURESensorValues);
    lcd.setCursor(5,1);
    lcd.print("Celsius");

//transmitFloatDataToNodeMCU(TEMPERATURESensorValues);
    

}

void getHUMIDITY_readings()
{


//transmitFloatDataToNodeMCU(TEMPERATURESensorValues);

}

void getBAROMETRIC_readings()
{

  
}

void getSWITCH_readings()
{
	int SWICTHSensorValues;
  if( digitalRead(SWITCH_PIN)==1)
  {
    SWICTHSensorValues = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SWITCH BUTTON");
    lcd.setCursor(0,1);
    lcd.print(SWICTHSensorValues);
  }
  else
  {
    SWICTHSensorValues = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SWITCH BUTTON");
    lcd.setCursor(0,1);
    lcd.print(SWICTHSensorValues);
  }
  if(verbose)
  {
  Serial.println("Switch :");
  Serial.println(SWICTHSensorValues);
  delay(1000);
  }

 //transmitDigitalDataToNodeMCU(SWICTHSensorValues);

}

void getRAIN_readings()
{
	int RAINSensorValues;
  if( digitalRead(RAIN_SENSOR_PIN)==1)
  {
    RAINSensorValues = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RAIN SENSOR");
    lcd.setCursor(0,1);
    lcd.print(RAINSensorValues);
  }
  else
  {
    RAINSensorValues = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RAIN SENSOR");
    lcd.setCursor(0,1);
    lcd.print(RAINSensorValues);
  }
  if(verbose)
  {
  Serial.println("Rain :");
  Serial.println(RAINSensorValues);
  delay(1000);
  }

  // transmitDigitalDataToNodeMCU(SWICTHSensorValues);
}

void getVOLTAGE_readings()
{
	int VOLTAGESensorValues;
	VOLTAGESensorValues = analogRead(VOLTAGE_SENSOR_PIN);
	VOLTAGESensorValues = (VOLTAGESensorValues *5) /1024;
	if(verbose)
	{
	Serial.println("VOLTAGE :");
	Serial.println(VOLTAGESensorValues);
	delay(1000);
	}
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("VOLTAGE SENSOR");
    lcd.setCursor(0,1);
    lcd.print(VOLTAGESensorValues);


  transmitFloatDataToNodeMCU(VOLTAGESensorValues);
}



uint8_t user_input()                //function to get the input from the user
{
  uint8_t num = 0;
  boolean validnum = false; 
  while (1) {
    while (! Serial.available());
    char c = Serial.read();
    if (isdigit(c)) 
    {
       num *= 10;
       num += c - '0';
       validnum = true;
    } 
    else if (validnum) 
    {
      return num;
    }
  }
}

void getkeyStrokes()
{
  char key = selectionKeypad.getKey();

if(key) 

{

switch (key)

{

case '1':

Serial.println(key);

break;

case '2':

Serial.println(key);

break;

case '3':

Serial.println(key);

break;

case '4':

Serial.println(key);

break;

case '5':

Serial.println(key);

break;

case '6':

Serial.println(key);

break;

case '7':

Serial.println(key);

break;

case '8':

Serial.println(key);

break;

case '9':

Serial.println(key);

break;

case '0':

Serial.println(key);

break;

case '*':

Serial.println(key);

break;

case '#':

Serial.println(key);

break;

}

}
}

void escapeMenu()
{
  
while(1){
  //keep checking for pressed key as 1 to exit to main menu
  char key = selectionKeypad.getKey();

if(key) 

{

switch (key)

{

case '1':

lcd.clear();
openFirstMenu();

Serial.println(key);

break;
  
}
}
}
}


void transmitDigitalDataToNodeMCU(String sensor,int int_payload)
{
  //parseInt on the receiver
  String s_int = sensor + (String)int_payload;
  
  Serial.println('&'+s_int+'&');

}
void transmitFloatDataToNodeMCU(float float_payload)
{
  //parseFloat on the receiver
  String s_float = (String)float_payload;
  Serial.println('&'+s_float+'&');
  
}

