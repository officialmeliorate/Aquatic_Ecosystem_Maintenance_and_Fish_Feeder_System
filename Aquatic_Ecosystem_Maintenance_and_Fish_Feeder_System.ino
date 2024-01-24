#define BLYNK_TEMPLATE_ID "xxxxxxxxxx"//Provide template id
#define BLYNK_DEVICE_NAME "xxxxxxxxxx"//Provide blynk device name
//#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxxxxxxxxxx"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#define BLYNK_PRINT Serial

//char auth[] = BLYNK_AUTH_TOKEN;

char auth[] = "xxxxxxxxxxxxxxxxxxxx"; //Provide authentication token
char ssid[] = "xxxxxxxxx"; //Provide SSID 
char pass[] = "xxxxxxxxx"; //Provide Password

#define NTU A0 
int relaypin = D5;
SimpleTimer timer;

void checkPhysicalButton();
int relay1State = LOW;
int pushButton1State = HIGH;
#define RELAY_PIN_1       D3
#define PUSH_BUTTON_1     D7
#define VPIN_BUTTON_1    V12 

#define ONE_WIRE_BUS 2 // DS18B20 on arduino pin2 corresponds to D4 on physical board "D4 pin on the nodemcu module"
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float temp;
float Fahrenheit=0;
Servo servo;
BLYNK_WRITE(V0) {
servo.write(param.asInt());
}

void setup() {
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
servo.attach(15); // 15 means D8 pin of ESP8266
DS18B20.begin();
timer.setInterval(1000L, getSendData);
pinMode(relaypin,OUTPUT);

pinMode(RELAY_PIN_1, OUTPUT);
digitalWrite(RELAY_PIN_1, LOW);
pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
digitalWrite(RELAY_PIN_1, relay1State);

}

void loop()
{
Blynk.run(); 
timer.run();
}

void getSendData()
{
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0); // Celsius
   Fahrenheit = DS18B20.toFahrenheit(temp); // Fahrenheit
  Serial.println(temp);
  Serial.println(Fahrenheit);
  Blynk.virtualWrite(V3, temp); //virtual pin V3
  Blynk.virtualWrite(V4, Fahrenheit); //virtual pin V4
}

void Turbidity
() {
 int sensorValue = analogRead(NTU);
 sensorValue = sensorValue * (5.0 / 1024.0);
 sensorValue = (-1120.4* sq(sensorValue)+5742.3*sensorValue-3352.9)-3900;
if(NTU < 0){
NTU == 0;
}

  Blynk.virtualWrite(V5, sensorValue);
  
}


BLYNK_CONNECTED() {
  Blynk.syncVirtual(VPIN_BUTTON_1);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
}
