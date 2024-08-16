/*
 * Title: NodeMCU to IOT Dashboard Update
 * Date: 28/07/2023
 * Author: Smart Garbage Can team
 * Brief: Code for sending the data to IOT Dashboard after interrupt is received. 
 * Pins used: GPIO D6 - Interrupt from PICO
 */
 
#include "arduino_secrets.h"               
#include "thingProperties.h"

#define INTERRUPT 14

void setup() {
  Serial.begin(9600);                                           // Initialize serial and wait for port to open
  delay(1500);                                                  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  pinMode(INTERRUPT, INPUT);                                    // Initialize Interrupt pin as INPUT
  initProperties();                                             // Defined in thingProperties.h

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);            // Connect to Arduino IoT Cloud
  setDebugMessageLevel(2);                                      // Check for errors in Connections
  ArduinoCloud.printDebugInfo();                                // Print the error in Connections
}

void loop() {
  ArduinoCloud.update();                                        // Update the Variables the Arduino Cloud

  if (digitalRead(INTERRUPT) == HIGH)                           // Check for Interrupt
  {
      status = true;                                            // Set Status to True
      message = "Garbage Collected from Can 1 | Seepark";       // Set Message to "Garbage Collected from Can 1 | Seepark"
      location = Location(48.0081,7.8215);                      // Set Location to Seepark
      ArduinoCloud.update();                                    // Update the Variables the Arduino Cloud
      delay(5000);
  }
  status= false;                                                // Reset Status to False
  message = "Resetted";                                         // Reset Message to "Reseted"
}
