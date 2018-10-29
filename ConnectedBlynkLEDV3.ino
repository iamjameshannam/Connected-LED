#include <ESP8266WiFi.h>                                // Adds the ESP8266 Core WiFi Library
#include <DNSServer.h>                                  // Local DNS Server used for redirecting all requests to a configuration portal
#include <ESP8266WebServer.h>                           // Local WebServer used to serve the configuration portal
#include <DoubleResetDetector.h>                        // For entering WiFiManager Config mode by pressing reset twice https://github.com/datacute/DoubleResetDetector

#define DRD_TIMEOUT 10                                  // Number of seconds after reset during which a subseqent reset will be considered a double reset.
#define DRD_ADDRESS 0                                   // RTC Memory Address for the DoubleResetDetector to use

DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);      // Settings for DoubleReset, need both of thiese defined

#include <WiFiManager.h>                                // WiFi Configurator - an amazing little library!https://github.com/tzapu/WiFiManager
#include <BlynkSimpleEsp8266.h>                         // Include the Blynk ESP8266 Library
#include <Adafruit_NeoPixel.h>                          // Used to make the LED function
#include "FS.h"                                         // For storing configurations

#define PIN 5                                           // This is actually D1 on your Wemos D1 Mini. The pin and D numbers are often different! (leave this number as it is)
                
bool shouldSaveConfig = false;                          // flag for saving data

BlynkTimer timer;



//-------------------------------------------------
//-----------------EDIT THIS TEXT------------------

char Device [ ] = "BARRY";                                // Name your device here
char Secret [ ] = "PASSWORD";                             // This is the initial password to connect to your device to allow you to set it up!                                                                       
char auth[ ] = "82d4112ee1e749b993a4d8dfd12c13a8";        // Blynk app auth token (get this from your Blynk Project settings)                    
                                                          // add in your authentication code from the Blynk app
//-------------------------------------------------
//-------------------------------------------------



    

//-------------------------------------------------
//--------------------Callbacks--------------------


void saveConfigCallback () {                              // Callback notifying us of the need to save config
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  drd.stop();
}

//----------------End of Callbacks-----------------
//-------------------------------------------------




//-------------------------------------------------
//--------------------LED Setup--------------------

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800); // Sets up the LED as a 'pixel'

//----------------End of LED Setup-----------------
//-------------------------------------------------





//-------------------------------------------------
//-------------------void Setup--------------------


void setup() {                                             // The 'setup' happens when the device starts, it gets everything ready!

  Serial.begin(115200);
  Serial.println();
  Serial.println("DoubleResetDetector Is Running");
  Serial.println("-----------------------------------");
  
  pixels.begin();                                          // This initializes the NeoPixel library
  WiFiManager wifiManager;                                 // This initializes the WiFi Manager
  Serial.println("WiFi Manager is running");
  wifiManager.setAPCallback(configModeCallback);
  Serial.println("Setting AP Call Back");
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  Serial.println("Saving AP Call Back");
  

 if (drd.detectDoubleReset()) {
    Serial.println("Double Reset Detected");
    pixels.setPixelColor(0, pixels.Color(100, 0, 0));       // Sets the LED to a RED color. Yellow/Light Green, means that device is turned on, and waiting to connect to wifi
    pixels.show(); 
    wifiManager.resetSettings(); 

  } else {
    Serial.println("No Double Reset Detected");
    wifiManager.autoConnect(Device, Secret);
    pixels.setPixelColor(0, pixels.Color(0, 100, 0));       // Somewhat GREEN color. Green, means connection to wifi is successful, and is waiting to go
    pixels.show(); 
  }
                                 
   //wifiManager.autoConnect(Device);                     
 
  
  Blynk.config(auth); 
    while (Blynk.connect() == false) {
  }
 }

//----------------End of void Setup----------------
//-------------------------------------------------


//-------------------------------------------------
//-------------------loop Setup--------------------
  
void loop(){                                             // Whilst your device is turned on, the code in this bit will loop forever
  Blynk.run();
  timer.run();
  //drd.loop();                                          // Call the double reset detector loop method every so often, so that it can recognise when 
                                                         // the timeout expires. You can also call drd.stop() when you wish to no longer consider the
                                                         // next reset as a double reset.
}

//----------------End of loop Setup----------------
//-------------------------------------------------


BLYNK_WRITE(V1)                                          // When the virtual button is 'pressed' by IFTTT, the LED will flash blue (you can copy and paste the code to add more flashes...)
{
   pixels.setPixelColor(0, pixels.Color(255, 165, 0));   // Sets the LED to a ORANGE color, from Blynk button press
   pixels.show();                                        // This sends the updated pixel color to the hardware.
   delay(1500);                                          // Wait for 1.5 seconds
   pixels.setPixelColor(0, pixels.Color(0, 0, 0));       // Resets  to OFF/BLACK
   pixels.show();                                        // This sends the updated pixel color to the hardware.
   delay(500);                                           // Wait for a 0.5 second
   pixels.setPixelColor(0, pixels.Color(255, 165, 0));   // Moderately ORGANGE color again, from Blynk button press
   pixels.show();                                        // This sends the updated pixel color to the hardware. The rest is now repeated to make the LED flash...
   delay(1500);
   pixels.setPixelColor(0, pixels.Color(0, 0, 0));                      
   pixels.show();                         
   delay(500);
   pixels.setPixelColor(0, pixels.Color(255, 165, 0)); 
   pixels.show();
   delay(1500);
   pixels.setPixelColor(0, pixels.Color(0, 0, 0));
   pixels.show();
   delay(500);
   pixels.setPixelColor(0, pixels.Color(10, 10, 10));
   pixels.show();
}
