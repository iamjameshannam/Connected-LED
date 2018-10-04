#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to a configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

BlynkTimer timer;

#define PIN 5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library
  WiFiManager wifiManager;
  //reset saved settings
  //wifiManager.resetSettings();

   pixels.setPixelColor(0, pixels.Color(100, 0, 0)); // Moderately RED color. Yellow, menas that device is turned on, and waiting to connect to wifi
   pixels.show(); // This sends the updated pixel color to the hardware.

   //Parameter is name of access point
   wifiManager.autoConnect("THIS IS YOUR DEVICE"); //Name your device here!

   pixels.setPixelColor(0, pixels.Color(0, 100, 0)); // Moderately GREEN color. Green, means connection to wifi is successful
   pixels.show(); // This sends the updated pixel color to the hardware.

  //Blynk app auth token
  char auth[] = "f31bdc72f2294e9c8d1b4314842adbbe"; // add in your authentication code from the Blynk app

  Serial.begin(9600);
  Blynk.config(auth); 
    while (Blynk.connect() == false) {
    // Wait until connected
  }
 }
  
void loop(){
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1)//Red
{
   pixels.setPixelColor(0, pixels.Color(50, 0, 255)); // Moderately LIGHT BLUE color, from Blynk button press
   pixels.show(); // This sends the updated pixel color to the hardware.
   delay(1500);
   pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Resets  to OFF/BLACK
   pixels.show(); // This sends the updated pixel color to the hardware.
   delay(500);
   pixels.setPixelColor(0, pixels.Color(50, 0, 255)); // Moderately LIGHT BLUE color, from Blynk button press
   pixels.show(); // This sends the updated pixel color to the hardware.
   delay(1500);
   pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Resets back to OFF/BLACK
   pixels.show(); // This sends the updated pixel color to the hardware.
   delay(500);
   pixels.setPixelColor(0, pixels.Color(50, 0, 255)); // Moderately LIGHT BLUE color, from Blynk button press
   pixels.show(); // This sends the updated pixel color to the hardware.
   delay(1500);
   pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Resets back to OFF/BLACK
   pixels.show(); // This sends the updated pixel color to the hardware.
   delay(500);
   pixels.setPixelColor(0, pixels.Color(0, 1, 0)); // Resets back to GREEN
   pixels.show(); // This sends the updated pixel color to the hardware.
}
