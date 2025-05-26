# IRremoteEsp32
IR remote pulse width light lib. Receive and send raw data.

*THIS LIBRARY USES PWM CHANNEL 0 OF ESP32.

Receive and send raw pulse width data for TV and AC IR remote control. May work with others IR too.

0 - CHANGE DEFINITIONS ON IRRemote.h
  #define IR_RECEIVER_PIN 5 
  //Pin of IC receiver signal. 
  #define IR_TRANSMITTER_PIN 4
  //Pin of IR led transmitter.
  #define PULSE_WIDTH_VECTOR_SIZE 500
  //Size of vector that store code.
  #define MAXIMUM_GAP 50000
  //Many AC codes has big time gaps on it.

  //Other configurations to send the code on 38 khz modulation.
  #define PWM_CHANNEL 0    
  #define PWM_FREQ 38000     
  #define PWM_RESOLUTION 8 

1 - CREATE OBJECT.
  IRCode IRcode;

2 - PREPARE THE PROGRAM.
  void setup(){
    ...
    IRcode.begin();
    ...
  }

1 - RECEIVE CODE EASILY.
  IRcode.IRrecStart();
  Serial.print("Waiting code:");
  for(int i = 0 ; i < 10 ; i++){
    Serial.print(".");
    delay(500);
  }
  IRcode.IRrecStop();
  Serial.println("Aquisition end.");

3 - PRINT EASILY (don't forget Serial.begin(115200) on setup)
    IRcode.printPulseWidthVector();
    IRcode.printPulseWidthVectorinBinary();

4 - SEND
  IRcode.IRsendRaw();

5 - DATA 
  data is saved as int in IRcode.pulseWidthVector[];
  
