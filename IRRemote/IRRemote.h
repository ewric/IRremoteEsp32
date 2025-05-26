/*
*THIS LIBRARY USES PWM CHANNEL 0 OF ESP32.
*
*
*


*/





#ifndef IRREMOTE_H
#define IRREMOTE_H



#include <Arduino.h>

//#################PINS DEFINITIONS#####################################
#define IR_RECEIVER_PIN 5
#define IR_TRANSMITTER_PIN 4

//#################OTHERS DEFINITIONS###################################
#define PULSE_WIDTH_VECTOR_SIZE 500
#define MAXIMUM_GAP 50000

#define PWM_CHANNEL 0    
#define PWM_FREQ 38000     
#define PWM_RESOLUTION 8  


class IRCode {
public:
    int pulseWidthVector[PULSE_WIDTH_VECTOR_SIZE];
    /*Initializes necessary inputs, output pins and variables.*/
    void begin();
    /*Activate interrupt pin to start detecting.*/
    void IRrecStart();
    /*Deactivate interrupt pin to stop detecting.*/
    void IRrecStop();
    /*Serial print pulse width vector in pulse width distances.*/
    void printPulseWidthVector();
    /*Serial print pulse width vector in binary.*/
    void printPulseWidthVectorinBinary();
    /*Send raw code.*/
    void IRsendRaw();

private:
    static int pulseWidthVectorBuffer[PULSE_WIDTH_VECTOR_SIZE];
    static int incrementorBuffer;
    static long interruptTimer;

    /*Calculates time between interrupts and saves it in PulseWidthVector.*/
    static void variationDetect();

    /*Print vector, with commas.*/
    template <typename T>
    void vectorPrint(T vector[], int size);

    /*Update vector 1 from vector 2.*/
    template <typename T>
    void vectorCopy(T vectorCopy[], T vectorOrigin[], int size);

    /*Returns 1 -> bit 1 (-600,1600) width time.
              0 -> bit 0 (-600, 600).
              2 -> gap, not 1 or 0, (>1800 || > 1800).
             -1 -> no code, pulse widths are 0.*/
    int checkBit(int timeLow, int timeHigh);

    /*Resets buffer and its incrementor back to 0. Need to be done every time a new code is saved.*/
    void resetBuffer();

    /*Resets an int vector back to 0s.*/
    void resetVector(int vector[], int size);

};


#endif