#include "UcasDualMC33926MotorShield.h"

// Constructors ////////////////////////////////////////////////////////////////

UcasDualMC33926MotorShield::UcasDualMC33926MotorShield()
{
  //Pin map
  _nD1 = 4;     /// enable or disable the driver
                /// LOW = the driver works, HIGH = the driver is stopped
  _M1DIR = 7;
  _M1PWM = 9;
  _M2DIR = 8;
  _M2PWM = 10;
  /// Fault pin, when there is a fault nsF is LOW
  _nSF1 = 12;    //
  _M1FB = A0;   /// provides the output voltage
  _M2FB = A1;   /// same

  //additional variables --UCAS
  _nD2 = 24; // 4
  _M3DIR = 27; // 7
  _M3PWM = 2;// 9 PWM
  _M4DIR = 28;// 8
  _M4PWM = 3;// 10 PWM
  _nSF2 = 32;// 12
  _M3FB = A3;// A0
  _M4FB = A4;// A1

}

UcasDualMC33926MotorShield::UcasDualMC33926MotorShield(unsigned char M1DIR,
                                               unsigned char M1PWM,
                                               unsigned char M1FB,
                                               unsigned char M2DIR,
                                               unsigned char M2PWM,
                                               unsigned char M2FB,
                                               unsigned char nD1,
                                               unsigned char nSF1,
                                               //second driver
                                               unsigned char M3DIR,
                                               unsigned char M3PWM,
                                               unsigned char M3FB,
                                               unsigned char M4DIR,
                                               unsigned char M4PWM,
                                               unsigned char M4FB,
                                               unsigned char nD2,
                                               unsigned char nSF2
                                               )
{
  _nD1 = nD1;
  _M1DIR = M1DIR;
  _M1PWM = M1PWM;
  _M2DIR = M2DIR;
  _M2PWM = M2PWM;
  _nSF1 = nSF1;
  _M1FB = M1FB;
  _M2FB = M2FB;


  //second driver
  _nD2 = nD2;
  _M3DIR = M3DIR;
  _M3PWM = M3PWM;
  _M4DIR = M4DIR;
  _M4PWM = M4PWM;
  _nSF2 = nSF2;
  _M3FB = M3FB;
  _M4FB = M4FB;





}

// Public Methods //////////////////////////////////////////////////////////////
void UcasDualMC33926MotorShield::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_M1DIR,OUTPUT);
  pinMode(_M1PWM,OUTPUT);
  pinMode(_M1FB,INPUT);
  pinMode(_M2DIR,OUTPUT);
  pinMode(_M2PWM,OUTPUT);
  pinMode(_M2FB,INPUT);
  pinMode(_nD1,OUTPUT);
  digitalWrite(_nD1,HIGH); // default to on
  pinMode(_nSF1,INPUT);

  //second driver
  pinMode(_M3DIR,OUTPUT);
  pinMode(_M3PWM,OUTPUT);
  pinMode(_M3FB,INPUT);
  pinMode(_M4DIR,OUTPUT);
  pinMode(_M4PWM,OUTPUT);
  pinMode(_M4FB,INPUT);
  pinMode(_nD2,OUTPUT);
  digitalWrite(_nD2,HIGH); // default to on
  pinMode(_nSF2,INPUT);

  //TODO complete ghere
  #ifdef UCASDUALMC33926MOTORSHIELD_TIMER1_AVAILABLE
    if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
    {
      // Timer 1 configuration
      // prescaler: clockI/O / 1
      // outputs enabled
      // phase-correct PWM
      // top of 400
      //
      // PWM frequency calculation
      // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
      TCCR1A = 0b10100000;
      TCCR1B = 0b00010001;
      ICR1 = 400;
    }
  #endif
}



// Set speed for motor 1, speed is a number betwenn -400 and 400
void UcasDualMC33926MotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

  #ifdef UCASDUALMC33926MOTORSHIELD_TIMER1_AVAILABLE
    if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
    {
      OCR1A = speed;
    }
    else
    {
      analogWrite(_M1PWM,speed * 51 / 80); // map 400 to 255
    }
  #else
    analogWrite(_M1PWM,speed * 51 / 80); // map 400 to 255
  #endif

  if (reverse)
    digitalWrite(_M1DIR,HIGH);
  else
    digitalWrite(_M1DIR,LOW);
}

// Set speed for motor 2, speed is a number betwenn -400 and 400
void UcasDualMC33926MotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

  #ifdef UCASDUALMC33926MOTORSHIELD_TIMER1_AVAILABLE
    if (_M1PWM == _M1PWM_TIMER1_PIN && _M2PWM == _M2PWM_TIMER1_PIN)
    {
      OCR1B = speed;
    }
    else
    {
      analogWrite(_M2PWM,speed * 51 / 80); // map 400 to 255
    }
  #else
    analogWrite(_M2PWM,speed * 51 / 80); // map 400 to 255
  #endif

  if (reverse)
    digitalWrite(_M2DIR,HIGH);
  else
    digitalWrite(_M2DIR,LOW);
}


void UcasDualMC33926MotorShield::setM3Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

  #ifdef UCASDUALMC33926MOTORSHIELD_TIMER1_AVAILABLE
    if (_M3PWM == _M3PWM_TIMER1_PIN && _M4PWM == _M4PWM_TIMER1_PIN)
    {
      OCR1A = speed;
    }
    else
    {
      analogWrite(_M2PWM,speed * 51 / 80); // map 400 to 255
    }
  #else
    analogWrite(_M3PWM,speed * 51 / 80); // map 400 to 255
  #endif

  if (reverse)
    digitalWrite(_M2DIR,HIGH);
  else
    digitalWrite(_M3DIR,LOW);
}

void UcasDualMC33926MotorShield::setM4Speed(int speed)
{
    unsigned char reverse = 0;

    if (speed < 0)
    {
        speed = -speed;  // Make speed a positive quantity
        reverse = 1;  // Preserve the direction
    }
    if (speed > 400)  // Max PWM dutycycle
        speed = 400;

#ifdef UCASDUALMC33926MOTORSHIELD_TIMER1_AVAILABLE
    if (_M3PWM == _M3PWM_TIMER1_PIN && _M4PWM == _M4PWM_TIMER1_PIN)
    {
      OCR1A = speed;
    }
    else
    {
      analogWrite(_M4PWM,speed * 51 / 80); // map 400 to 255
    }
#else
    analogWrite(_M4PWM,speed * 51 / 80); // map 400 to 255
#endif

    if (reverse)
        digitalWrite(_M4DIR,HIGH);
    else
        digitalWrite(_M4DIR,LOW);
}










//todo add other motors
// Set speed for motor 1 and 2
void UcasDualMC33926MotorShield::setSpeeds(int m1Speed, int m2Speed, int m3Speed, int m4Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
  setM3Speed(m3Speed);
  setM4Speed(m4Speed);
}

// Return motor 1 current value in milliamps.
unsigned int UcasDualMC33926MotorShield::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M1FB) * 9;
}

// Return motor 2 current value in milliamps.
unsigned int UcasDualMC33926MotorShield::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M2FB) * 9;
}

unsigned int UcasDualMC33926MotorShield::getM3CurrentMilliamps()
{
    // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
    return analogRead(_M3FB) * 9;
}

unsigned int UcasDualMC33926MotorShield::getM4CurrentMilliamps()
{
    // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
    return analogRead(_M4FB) * 9;
}




// Return error status
unsigned char UcasDualMC33926MotorShield::getFaultD1()
{
  return !digitalRead(_nSF1);
}
unsigned char UcasDualMC33926MotorShield::getFaultD2()
{
    return !digitalRead(_nSF2);
}

unsigned char UcasDualMC33926MotorShield::getFault()
{
    if(getFaultD1() || getFaultD2())
        return 1;
    else
        return 0;
}
unsigned char UcasDualMC33926MotorShield::getnd()
{
    return !digitalRead(_nD1);
}
