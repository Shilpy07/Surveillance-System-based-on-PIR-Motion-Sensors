// Servor motor
#include <Servo.h>
Servo camServo; 
int currentPIRposition = 0;

// LED status lights
int LEDpin[] = {9,10,11,12,13};
int currentLEDpin = 9;

// PIR sensors
int PIRpin[] = {2,3,4,5,6};
int currentPIRpin = 2;
int PIRprevState[] = {1,1,1,1,1};
int PIRposition[] = {160,120,80,40,0};
boolean PIRstatus;

// SETUP //
void setup() {
  
  Serial.begin(9600);
  camServo.attach(7);
  
  for (int p = 0; p < 5; p++) {
  pinMode(PIRpin[p], INPUT);
    }
    
  for (int l = 0; l < 5; l++) { 
  pinMode(LEDpin[l], OUTPUT);
    } // end 'l' for
  
// CALIBRATE PIR SENSORS //
  Serial.print("Calibrating PIR Sensors ");
    for(int c = 0; c < 15; c++){ 
      Serial.print(".");
      delay(1000); 
      }
    Serial.println("PIR Sensors Ready");
  
  camServo.write(78.5); 
  
  }
// MAIN LOOP //
void loop() {
  
  for (int PIR = 0; PIR < 5; PIR++) { 
    currentPIRpin = PIRpin[PIR]; 
    currentLEDpin=LEDpin[PIR]; 
    PIRstatus = digitalRead(currentPIRpin);
    
    if (PIRstatus == HIGH) { 
      digitalWrite(currentLEDpin, HIGH);
      if(PIRprevState[PIR] == 0) { 
        if (currentPIRposition != currentPIRpin && PIRprevState[PIR] == 0) {
          camServo.write(PIRposition[PIR]);
          Serial.print("Current angle : ");
          Serial.println(PIRposition[PIR]);
          delay(50);
          currentPIRposition = currentPIRpin;
          PIRprevState[PIR] = 1;
          }
        PIRprevState[PIR] = 1;
        }   
      } 
    
    else {
      digitalWrite(currentLEDpin, LOW); 
      PIRprevState[PIR] = 0; 
      } 
      
    } 
  } 
