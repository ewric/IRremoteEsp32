#include <IRRemote.h>

int IRCode::pulseWidthVectorBuffer[PULSE_WIDTH_VECTOR_SIZE] = {0};
int IRCode::incrementorBuffer = 0;
long IRCode::interruptTimer = 0;


void IRCode::begin(){
    pinMode(IR_TRANSMITTER_PIN, OUTPUT);
    incrementorBuffer = 0;
    interruptTimer = 0;
    //Begin of pwm for transmission.
    ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(IR_TRANSMITTER_PIN, PWM_CHANNEL);
}

void IRCode::IRrecStart(){
    attachInterrupt(IR_RECEIVER_PIN, variationDetect, CHANGE);
}

void IRCode::IRrecStop(){
    detachInterrupt(IR_RECEIVER_PIN);
    vectorCopy(pulseWidthVector, pulseWidthVectorBuffer, PULSE_WIDTH_VECTOR_SIZE);
    //vectorPrint(pulseWidthVector, PULSE_WIDTH_VECTOR_SIZE);
    resetBuffer();
}

void IRCode::printPulseWidthVector(){
    vectorPrint(pulseWidthVector, PULSE_WIDTH_VECTOR_SIZE);
}

void IRCode::printPulseWidthVectorinBinary(){
    Serial.println("\nReceived binary data:  "); 
    for(int i = 0 ; i < PULSE_WIDTH_VECTOR_SIZE ; i = i + 2 ) {
        int bit = checkBit(pulseWidthVector[i], pulseWidthVector[i+1]);
        if(bit == 0 || bit == 1){
            Serial.print(bit);
        }
        else if(bit == 2){
            Serial.print("(");
            Serial.print(pulseWidthVector[i]);
            Serial.print(",");
            Serial.print(pulseWidthVector[i+1]);
            Serial.print(")");
        }
    }
}

void IRCode::IRsendRaw(){
    long sendingTimer;
    for (int i = 0 ; i < PULSE_WIDTH_VECTOR_SIZE ; i++){
        long interval = abs(pulseWidthVector[i]);
        sendingTimer = micros();
        if(pulseWidthVector[i] < 0){
            ledcWrite(0, 128);
        } else {
            ledcWrite(0, 0);
        }
        while(micros() - sendingTimer < interval){
            if(micros() - sendingTimer > 1000000)
                break;
        }
    }
    ledcWrite(0, 0);
}


void IRCode::variationDetect(){
  int variation = (micros() - interruptTimer) * (digitalRead(IR_RECEIVER_PIN)==1?-1:1);
  //Notice a change has occur. So, the signal we want is the last one, not the actual.

  // avoid collecting big time variations or corrupting memory.
  if(variation < MAXIMUM_GAP && incrementorBuffer < PULSE_WIDTH_VECTOR_SIZE){   
    pulseWidthVectorBuffer[incrementorBuffer] = variation;
    incrementorBuffer++;
  }
  interruptTimer = micros();
}

template <typename T>
void IRCode::vectorPrint(T vector[], int size){
    Serial.println("\n Printing vector:  ");
  for(int i = 0 ; i < size ; i++){
    if(vector[i] != 0)
        Serial.print(vector[i]);
    if(vector[i+1] != 0)
        Serial.print(";");
  }
  Serial.println(".");
}

template <typename T>
void IRCode::vectorCopy(T vectorCopy[], T vectorOrigin[], int size){
    for (int i = 0 ; i < size ; i++){
        vectorCopy[i] = vectorOrigin[i];
    }
}

int IRCode::checkBit(int timeLow, int timeHigh){
    if(timeLow == 0 && timeHigh == 0)
        return -1;
    if(abs(timeLow) > 350 && abs(timeLow) < 800 && timeHigh > 350 && timeHigh < 800)
        return 0;
    if(abs(timeLow) > 350 && abs(timeLow) < 800 && timeHigh > 1350 && timeHigh < 1800)
        return 1;
    return 2;
}

void IRCode::resetBuffer(){
    incrementorBuffer = 0;
    resetVector(pulseWidthVectorBuffer, PULSE_WIDTH_VECTOR_SIZE);
}

void IRCode::resetVector(int vector[], int size) {
    for (int i = 0 ; i < size ; i ++){
        vector[i] = 0;
    }
}