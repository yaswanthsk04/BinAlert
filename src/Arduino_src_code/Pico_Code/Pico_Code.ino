/*
 * Title: Activity detection using Raspberry Pico & MPU6050
 * Date: 28/07/2023
 * Author: Smart Garbage Can team
 * Brief: Code for getting Mpu6050 acceleration data and detect garbage can empty operation using tiny_ML model. 
 * Pins used: Gpio 15 - MPU6050 interrupt pin, Gpio 0 - SDA (MPU6050), Gpio 1 - SCL (MPU6050), Gpio 26 - NODEMCU Interrupt
 */

#include <pico/stdlib.h>                // Pico Standard Library
#include <pico/sleep.h>                 // Pico Sleep Library
#include <hardware/rosc.h>              // Pico Ring Oscillator Library
#include <Adafruit_MPU6050.h>           // Adafruit MPU6050 Library
#include <Adafruit_Sensor.h>            // Adafruit Sensor Library
#include <Wire.h>                       // Arduino I2c Library            
#include <Final_inferencing_motion.h>   // TinyML Library from Edge impulse
//#include <Final_inferencing.h>  


bool awake = false;                    // Flag to check Sleep Status
static bool debug_nn = false;
#define interrupt_pin 15               // Interrupt from Sensor
#define nodemcu 26                     // Interrupt from Sensor      

Adafruit_MPU6050 mpu;                  // Create a Sensor Instance

void setup(void) {
  // Try to initialize!
  if (!mpu.begin()) {                                     // Initializing MPU6050
    //Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  //Serial.println("MPU6050 Found!");
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);           // MPU6050 register write Range - 8G 
  mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);             // MPU6050 register write Filter Bandwidth  - 44 Hz
  mpu.setSampleRateDivisor(9);                            // MPU6050 register write Sample frequency - 1Mhz/9

    // Setup motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);        // MPU6050 register write High Pass Filter - 63 HZ 
  mpu.setMotionDetectionThreshold(3);                     // MPU6050 register write Motion Detection Threshold - 3 mg 
  mpu.setMotionDetectionDuration(30);                     // MPU6050 register write Motion Detection Threshold - 30 ms 
  mpu.setInterruptPinLatch(false);                        // MPU6050 register write Interrupt Singal to Latched mode
  mpu.setInterruptPinPolarity(true);                      // MPU6050 register write Interrupt Singal to active LOW
  mpu.setMotionInterrupt(true);                           // MPU6050 register write Enable Significant Motion Interrupt Singal

    // Initialize Pins 
  pinMode(LED_BUILTIN,OUTPUT);                            // Initialize PICO Built in LED as Output
  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(2000);
  pinMode(interrupt_pin, INPUT);                          // Initialize Sensor to Pico interrupt pin as Output
  pinMode(nodemcu, OUTPUT);                               // Initialize PICO to Nodemcu interrupt pin as Output
}

void loop() 
{

  if (!awake){
    //Serial.println("in sleep");
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN,LOW);
    delay(2000);
    sleep_run_from_xosc();                                        // Put PICO to sleep until Interrupt
    sleep_goto_dormant_until_pin(interrupt_pin, false, false);    // Wake PICO from sleep if there is a Falling Edge in the Interrupt Pin
    awake = true;                                                 // Set the awake falg to TRUE
  }
  else if (awake){
    digitalWrite(LED_BUILTIN,HIGH);
    uint8_t buf1[64]="traj";
    uint8_t buf2[64]="still";

    float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };                                     // Allocate a buffer here for the values we'll read from the IMU

    for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 3) {
          uint64_t next_tick = micros() + (EI_CLASSIFIER_INTERVAL_MS * 10000);                    // Determine the next tick (and then sleep later)
          sensors_event_t a, g, temp;                                                             
          mpu.getEvent(&a, &g, &temp);                                                            // Get the data from the sensor using sensor_event
          buffer[ix] = a.acceleration.x;                                                          // Store the data in Buffer
          buffer[ix+1] = a.acceleration.y;
          buffer[ix+2] = a.acceleration.z;
          delay(40);
    }

    signal_t signal;
    int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);     // Turn the raw buffer into a signal which we can the classify
    if (err != 0) {
        ei_printf("Failed to create signal from buffer (%d)\n", err);
        return;
    }

    ei_impulse_result_t result = { 0 };                                                           // Run the classifier

    err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", err);
        return;
    }

    
    ei_printf("Predictions ");                                                                    // Print the predictions
    ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
    result.timing.dsp, result.timing.classification, result.timing.anomaly);
    ei_printf(": \n");
    
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    }
    
    #if EI_CLASSIFIER_HAS_ANOMALY == 1
        ei_printf("    anomaly score: %.3f\n", result.anomaly);
    #endif

    if (result.classification[0].value > 0.6){
      delay(500);      
    }

   if (result.classification[1].value > 0.6){
      delay(500);      
   }

   if (result.classification[2].value > 0.6){
      delay(500);      
    }

   if (result.classification[3].value > 0.6){
      delay(500);      
   }
  
   if (result.classification[4].value > 0.72){                                                  // Flicker the LED if trajactory is detected
      
          digitalWrite(nodemcu,HIGH);                                                           // Generate the Interrupt to NodeMCU
          digitalWrite(LED_BUILTIN,HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN,LOW);
          delay(500);
          digitalWrite(LED_BUILTIN,HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN,LOW);
          delay(500);
          digitalWrite(LED_BUILTIN,HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN,LOW);
          delay(500);
          digitalWrite(LED_BUILTIN,HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN,LOW);
          delay(500);
          digitalWrite(LED_BUILTIN,HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN,LOW);
          delay(500);
          digitalWrite(nodemcu,LOW);                                                            
   }

   if (result.classification[5].value > 0.6){
      delay(500);      
   }
   
    awake = false;                                                                              // Set the awake flag to FALSE
    digitalWrite(LED_BUILTIN,LOW);
  
  }
}
