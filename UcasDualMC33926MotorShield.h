#pragma once

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega328PB__) || defined (__AVR_ATmega32U4__)
#define UCASDUALMC33926MOTORSHIELD_TIMER1_AVAILABLE
#endif

#include <Arduino.h>

class UcasDualMC33926MotorShield
{
public:
    // CONSTRUCTORS
    // Default pin selection.
    UcasDualMC33926MotorShield();
    // User-defined pin selection.
    UcasDualMC33926MotorShield(unsigned char M1DIR,
                           unsigned char M1PWM,
                           unsigned char M1FB,
                           unsigned char M2DIR,
                           unsigned char M2PWM,
                           unsigned char M2FB,
                           unsigned char nD1,
                           unsigned char nSF,
                           unsigned char M3DIR,
                           unsigned char M3PWM,
                           unsigned char M3FB,
                           unsigned char M4DIR,
                           unsigned char M4PWM,
                           unsigned char M4FB,
                           unsigned char nD2,
                           unsigned char nSF2);

    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ.
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
    void setM3Speed(int speed);
    void setM4Speed(int speed);
    void setSpeeds(int m1Speed, int m2Speed,int m3Speed,int m4Speed); // Set speed for both M1 and M2.
    unsigned int getM1CurrentMilliamps(); // Get current reading for M1.
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
    unsigned int getM3CurrentMilliamps(); // Get current reading for M3.
    unsigned int getM4CurrentMilliamps(); // Get current reading for M4.
    unsigned char getFaultD1(); // Get fault reading.
    unsigned char getFaultD2(); // Get fault reading.
    unsigned char getFault(); // Get fault reading.
    unsigned char getnd();
private:
    unsigned char _nD1;
    unsigned char _M1DIR;
    unsigned char _M2DIR;
    unsigned char _M1PWM;
    static const unsigned char _M1PWM_TIMER1_PIN = 9;
    unsigned char _M2PWM;
    static const unsigned char _M2PWM_TIMER1_PIN = 10;
    unsigned char _nSF1;
    unsigned char _M1FB;
    unsigned char _M2FB;

    unsigned char _nD2;
    unsigned char _M3DIR;
    unsigned char _M4DIR;
    unsigned char _M3PWM;
    static const unsigned char _M3PWM_TIMER1_PIN = 29;
    unsigned char _M4PWM;
    static const unsigned char _M4PWM_TIMER1_PIN = 30;
    unsigned char _nSF2;
    unsigned char _M3FB;
    unsigned char _M4FB;
};
