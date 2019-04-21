#include <ArduinoJson.h>




#include <Firebase.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include<ArduinoJson.h>
#ifndef STASSID
#define STASSID "hns"
#define STAPSK  "helloworld"
#endif
#define FIREBASE_HOST "iotsensor-530ca.firebaseio.com"		//need to paste the firebase link
#define FIREBASE_AUTH "FhIjQ7a4hOqYALLG3slYWF2Wasi6QVEuSV69UTJ3"		//RSA Auth Key of db



const char* ssid     = STASSID;
const char* password = STAPSK;


/////////////////////////////////////////////////////////////////////

//							Communicate Buffer

/////////////////////////////////////////////////////////////////////
const byte numChars = 32;
char receivedCharsTAG[numChars];
char receivedCharsVALUE[numChars];
boolean newData = false;
int comm = 10;
boolean sensorReadAvailibilty = false;




String testData = "";

void setup()
{
	// put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial Begin");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
	}
    Serial.print("IP Address");
    Serial.println(WiFi.localIP());
	Firebase.begin(FIREBASE_HOST);

}
int n = 0;

void loop()
{
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //                  ORIGINAL DATA

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //Firebase.setString("message", "hello world");

  //delay(2000);

  communicate();

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //                  TEST DATA

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// set value

  /*
Firebase.setFloat("number", 4.0);
// handle error
if (Firebase.failed()) {
Serial.print("setting /number failed:");
Serial.println(Firebase.error());  
return;
}
delay(1000);
// update value
Firebase.setFloat("number", 43.0);
// handle error
if (Firebase.failed()) {
Serial.print("setting /number failed:");
Serial.println(Firebase.error());  
return;
}
delay(1000);
// get value 
Serial.print("number: ");
Serial.println(Firebase.getFloat("number"));
delay(1000);
// remove value
Firebase.remove("number");
delay(1000);
// set string value
Firebase.setString("message", "hello world");
// handle error
if (Firebase.failed()) {
Serial.print("setting /message failed:");
Serial.println(Firebase.error());  
return;
}
delay(1000);
// set bool value
Firebase.setBool("truth", false);
// handle error
if (Firebase.failed()) {
Serial.print("setting /truth failed:");
Serial.println(Firebase.error());  
return;
}
delay(1000);
// append a new value to /logs
String name = Firebase.pushInt("logs", n++);
// handle error
if (Firebase.failed()) {
Serial.print("pushing /logs failed:");
Serial.println(Firebase.error());  
return;
}
Serial.print("pushed: /logs/");
Serial.println(name);
delay(1000);


*/




}








/////////////////////////////////////////////////////////////////////

//								Step 1

/////////////////////////////////////////////////////////////////////
void communicate()
{
      //COIN_COLLECTOR();
	recvWithStartEndMarkers();
    showNewData();
}

/////////////////////////////////////////////////////////////////////

//								Step 2

/////////////////////////////////////////////////////////////////////
void recvWithStartEndMarkers() 
{
      //COIN_COLLECTOR();
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarkerTAG = '&';
    char endMarkerTAG = '&';
    char startMarkerVALUE = '!';
    char endMarkerVALUE = '!'; 
    char rc;
 
    while (Serial.available() > 0 && newData == false)
    {
        rc = Serial.read();

        if (recvInProgress == true) 
        {
            if (rc != endMarkerTAG)
            {
                receivedCharsTAG[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else 
            {
                receivedCharsTAG[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
                sensorReadAvailibilty = true;
            }
            
        }

        else if (rc == startMarkerTAG || rc == startMarkerVALUE) {
            recvInProgress = true;
        }
    }
}


/////////////////////////////////////////////////////////////////////

//								Step 3

/////////////////////////////////////////////////////////////////////
void showNewData() 
{    
  //COIN_COLLECTOR();
    if (newData == true) 
    {
        Serial.print("TAG");
        Serial.println(receivedCharsTAG);
        Serial.print("VALUE");
        Serial.println(receivedCharsVALUE);
        newData = false;
        delay(2000);
    }
    Firebase.setString("data/sensors/IR2",receivedCharsVALUE);
    
}



















