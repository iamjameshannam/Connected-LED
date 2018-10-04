#include <ESP8266WiFi.h>          // Adds the ESP8266 Core WiFi Library
#include <DNSServer.h>            // Local DNS Server used for redirecting all requests to a configuration portal
#include <ESP8266WebServer.h>     // Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          // WiFi Configurator - an amazing little library!
#include <BlynkSimpleEsp8266.h>   // Include the Blynk ESP8266 Library
#include <Adafruit_NeoPixel.h>    // Used to make the LED function

BlynkTimer timer;

#define PIN 5                                                               // This is actually D1 on your Wemos D1 Mini. The pin and D numbers are often different! (leave this number as it is)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800); // Sets up the LED as a 'pixel'

void setup() {                                                              // The 'setup' happens when the device starts, it gets everything ready!
  
  pixels.begin();                                                           // This initializes the NeoPixel library
  WiFiManager wifiManager;
  //wifiManager.resetSettings();                                            // Remove the two '//' from before the wifiManager.resetsettings to allow the device to wipe and reset the wifi settings (allows you to connect to another wifi point)

   pixels.setPixelColor(0, pixels.Color(100, 0, 0));                        // Sets the LED to a RED color. Yellow/Light Green, means that device is turned on, and waiting to connect to wifi
   pixels.show();                                                           // This sends the updated pixel color to the hardware.
   
   wifiManager.autoConnect("XYZ LED");                                      // Name your device here, this will be the name you look for in your wifi settings when you setup your Connected LED device 

   pixels.setPixelColor(0, pixels.Color(0, 100, 0));                        // Somewhat GREEN color. Green, means connection to wifi is successful
   pixels.show();                                                           // This sends the updated pixel color to the hardware.

                                                                            //Blynk app auth token (get this from your Blynk Project settings)
  char auth[] = "REPLACE THIS TEXT WITH YOUR APP AUTH CODE";                // add in your authentication code from the Blynk app

  Serial.begin(9600);
  Blynk.config(auth); 
    while (Blynk.connect() == false) {
  }
 }
  
void loop(){                                                                // Whilst your device is turned on, the code in this bit will loop forever
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1)                                                            // When the virtual button is 'pressed' by IFTTT, the LED will flash blue (you can copy and paste the code to add more flashes...)
{
   pixels.setPixelColor(0, pixels.Color(50, 0, 255));                      // Sets the LED to a LIGHT BLUE color, from Blynk button press
   pixels.show();                                                          // This sends the updated pixel color to the hardware.
   delay(1500);                                                            // Wait for 1.5 seconds
   pixels.setPixelColor(0, pixels.Color(0, 0, 0));                         // Resets  to OFF/BLACK
   pixels.show();                                                          // This sends the updated pixel color to the hardware.
   delay(500);                                                             // Wait for a 0.5 second
   pixels.setPixelColor(0, pixels.Color(50, 0, 255));                      // Moderately LIGHT BLUE color again, from Blynk button press
   pixels.show();                                                          // This sends the updated pixel color to the hardware. The rest is now repeated to make the LED flash...
   delay(1500);
   pixels.setPixelColor(0, pixels.Color(0, 0, 0));                      
   pixels.show();                         
   delay(500);
   pixels.setPixelColor(0, pixels.Color(50, 0, 255)); 
   pixels.show();
   delay(1500);
   pixels.setPixelColor(0, pixels.Color(0, 0, 0));
   pixels.show();
   delay(500);
   pixels.setPixelColor(0, pixels.Color(0, 1, 0));
   pixels.show();
}
