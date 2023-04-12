/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "T3mplate1D"                      /*Insert your template ID here */
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"                 /*Insert your template name here */
#define BLYNK_AUTH_TOKEN            "auTH-t0k3n"  /*Insert your auth token here */

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "MyWifiNetworkName";
char pass[] = "MyWifiP@$$w0rd";

int sensor = 12;  //GPIO Pin number on which door sensor is connected
const int door_relay = 14; //GPIO pin number for relay


BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(v1)
{
  // Set incoming value from pin v1 to a variable
  // 123 is OPEN signal
  // 456 is CLOSE signal
  int incOpenClose = param.asInt();

  // Update state
  if(incOpenClose == 123){
    if(digitalRead(sensor) == 0){
      digitalWrite(door_relay, HIGH);
      delay(250);
      digitalWrite(door_relay, LOW);
    }
      
  }
  
  if(incOpenClose == 456){
    if(digitalRead(sensor) == 1){
      digitalWrite(door_relay, HIGH);
      delay(250);
      digitalWrite(door_relay, LOW);
    }
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{

}

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);

  if(digitalRead(sensor) == 0){
    Blynk.virtualWrite(V3, "CLOSED");
    //Serial.println("CLOSED");  
  }

  if(digitalRead(sensor) == 1){
    Blynk.virtualWrite(V3, "OPEN");
    //Serial.println("OPEN");
  }

}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  pinMode(sensor, INPUT_PULLUP);
  pinMode(door_relay, OUTPUT);


  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
