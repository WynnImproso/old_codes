/**
VISSER Code Library Definition
Created for VISSER September 5, 2014 
Version 1.0
*/

#include "Arduino.h"
#include "VISSER.h"

#define DEFAULT_BLINK_TIME 500
#define DEFAULT_DELAY 1000

/**
VISSER_Test class constructor
Allows the developer to instantiate a VISSER_Test class
@param pin pin specified by the user to be used as output pin
*/
VISSER_Test::VISSER_Test(int pin)
{
    pinMode(pin, OUTPUT);
    _testPin = pin;
}

/**
VISSER_Test class method blink()
Allows the developer to make a blink action on the output pin
*/
void VISSER_Test::blink()
{
    digitalWrite(_testPin, HIGH);
    delay(DEFAULT_BLINK_TIME);
    digitalWrite(_testPin, LOW);
    delay(DEFAULT_BLINK_TIME);
}

/**
VISSER_Test class method blink() <overloaded function>
Allows the developer to make a blink action on the output pin
@param millis time 
*/
void VISSER_Test::blink(int millis)
{
    digitalWrite(_testPin, HIGH);
    delay(millis);
    digitalWrite(_testPin, LOW);
    delay(DEFAULT_BLINK_TIME);
}

/**
========== VISSER Temperature ===========
*/
#define AVERAGE_MULTIPLIER 0.09765625
#define MAX_ITERATION 10
/*
Constructor for VISSER_Temperature class

Initialize the analog ports to be used.

@param int sensor1 user defined port of 1st sensor (Analog input)
@param int sensor2 user defined port of 2nd sensor (Analog input)
@param int sensor3 user defined port of 3rd sensor (Analog input)
@param int sensor4 user defined port of 4th sensor (Analog input)
@param bool internalReference whether analogReference is INTERNAL or not (EXTERNAL)
*/
VISSER_Temperature::VISSER_Temperature(bool internalReference)
{
    _internalReference = internalReference;
}

// VISSER_Temperature::VISSER_Temperature(int sensor1, bool internalReference)
// {
//     _sensor1 = sensor1;
//     _sensor2 = NULL;
//     _sensor3 = NULL;
//     _sensor4 = NULL;
//     _internalReference = internalReference;
// }

// VISSER_Temperature::VISSER_Temperature(int sensor1, int sensor2, bool internalReference)
// {
//     _sensor1 = sensor1;
//     _sensor2 = sensor2;
//     _sensor3 = NULL;
//     _sensor4 = NULL;
//     _internalReference = internalReference;
// }

// VISSER_Temperature::VISSER_Temperature(int sensor1, int sensor2, int sensor3, bool internalReference)
// {
//     _sensor1 = sensor1;
//     _sensor2 = sensor2;
//     _sensor3 = sensor3;
//     _sensor4 = NULL;
//     _internalReference = internalReference;
// }

// VISSER_Temperature::VISSER_Temperature(int sensor1, int sensor2, int sensor3, int sensor4, bool internalReference)
// {
//     _sensor1 = sensor1;
//     _sensor2 = sensor2;
//     _sensor3 = sensor3;
//     _sensor4 = sensor4;
//     _internalReference = internalReference;
// }

/**
Getter function for port of 1st sensor
@return port of 1st sensor
*/
// int VISSER_Temperature::getSensor1()
// {
//     return _sensor1;
// }

/**
Getter function for port of 2nd sensor
@return port of 2nd sensor
*/
// int VISSER_Temperature::getSensor2()
// {
//     return _sensor2;
// }

/**
Getter function for port of 3rd sensor
@return port of 3rd sensor
*/
// int VISSER_Temperature::getSensor3()
// {
//     return _sensor3;
// }

/**
Method used to get the temperature reading for the specified sensor
@param int sensor port where to get the reading. 
           Use getSensorX() method if you are unsure of the ports used.
*/
float VISSER_Temperature::getReading(int sensor)
{
    int iteration, reading = 0;

    for(iteration = 0; iteration < MAX_ITERATION; iteration++)
    {
        reading += analogRead(sensor);
    }

    if(_internalReference)
        return (reading / MAX_ITERATION) * AVERAGE_MULTIPLIER;
    else
        return ((reading / MAX_ITERATION)*100*5)/1024;
}


/**
========== VISSER high Temperature ===========
*/
/**
Constructor method for VISSER_HighTemperature
currently, nothing needs to be initialized  
*/
VISSER_HighTemperature::VISSER_HighTemperature()
{
    // do something
}

/**
Method used to get the high temperature reading for a specified sensor pin
@param int sensor the sensor pin where to get the reading from
@return float the averaged readings from the specified sensor pin
*/
float VISSER_HighTemperature::getReading(int sensor)
{
    int iteration, reading = 0;
    for(iteration = 0; iteration < MAX_ITERATION; iteration++)  
    {
        reading += analogRead(sensor);
    }

    return (((((reading / MAX_ITERATION) * 5)/1024)-0.881)*100)-0.6;
}

/**
============ VISSER Conductivity ============ 
*/
/**
Constructor method fro VISSER_Conductivity
currently, nothing needs to be initialized  
*/
VISSER_Conductivity::VISSER_Conductivity()
{
    // do something
}

/**
Method used to het the conductivity reading on a specified sensor.
@param int sensor the sensor pin where to get the reading from
@return float the averaged readings from the specified sensor pin
*/
float VISSER_Conductivity::getReading(int sensor)
{
    double reading = 0.0;
    int iteration;

    for(iteration = 0; iteration < MAX_ITERATION; iteration++)
    {
        reading += (analogRead(sensor)*5)/1024;
        delay(DEFAULT_DELAY);
    }

    return 39.715*(exp(1.859*(reading / MAX_ITERATION)));
}

/**
============ VISSER Pulse ============
*/
/**
Constructor method fro VISSER_Pulse
currently, nothing needs to be initialized  
*/
VISSER_Pulse::VISSER_Pulse()
{
    // do something
}

/**
Method for getting the frequency <of something>
@param int sensor pin where the pulses will be read from to determine the frequency
@return the frequency <of something>
*/
float VISSER_Pulse::getFrequency(int sensor)
{
    float average, timeDifference;
    int time1, time2;
    while(analogRead(sensor) >= 201);
    while(analogRead(sensor) <= 201);
    time1 = millis();
    while(analogRead(sensor) >= 201);
    while(analogRead(sensor) <= 201);
    time2 = millis();
    timeDifference = (time2 - time1) / 1000;
    return 1 / timeDifference;
}

/**
Method for getting the pulse rate based on the given frequency
@param float the frequency of the pulse
@return int the pulse in beats per minute
*/
int VISSER_Pulse::getPulse(float frequency)
{
    return 60 * frequency;
}

/*
============ VISSER CO2 Sensor ============
*/
/**
Constructor method fro VISSER_CO2Sensor
currently, nothing needs to be initialized  
*/
VISSER_CO2Sensor::VISSER_CO2Sensor()
{
    // do something
}

/**
Method used to get the voltage reading to be used when getting the CO2 reading
@param int sensor the sensor where the reading will be read
@return float the voltage reading on the specified sensor
*/
float VISSER_CO2Sensor::getVoltage(int sensor)
{
    return (analogRead(sensor) * 5) / 1023;
}

/**
Method used to get the reading of the CO2 sensor depending on the specified voltage reading
@param float voltage the specified voltage reading 
@return float the reading of the CO2 sensor
*/
float VISSER_CO2Sensor::getReading(float voltage)
{
    return (voltage * 2000) / 4;
}

/*
============ VISSER Dsitance Sensor ============
*/
/**
Constructor class for VISSER_DistanceSensor
@param int outPin the specified output pin
@param int triggerPin the specified trigger pin
@param int echoPin the specified echo pin
*/
VISSER_DistanceSensor::VISSER_DistanceSensor(int outPin, int triggerPin, int echoPin)
{
    pinMode(outPin, OUTPUT);
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    _outPin = outPin;
    _triggerPin = triggerPin;
    _echoPin = echoPin;
}

/**
Method that gets the duration of pulse from the trigger pin
@return double the duration of pulse
*/
double VISSER_DistanceSensor::getDuration()
{
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, LOW);
    return pulseIn(_echoPin, HIGH);
}

/**
Method that gets the reading in inches based on the given duration
@param double duration the duration of pulse
@return double the reading of distance in inches
*/
double VISSER_DistanceSensor::getReadingInches(double duration)
{
    return duration / 74 / 2;
}

/**
Method that gets the reading in centimeters based on the given duration
@param double duration the duration of pulse
@return double the reading of distance in centimeters
*/
double VISSER_DistanceSensor::getReadingCentimeters(double duration)
{
    return duration / 29.1 / 2;
}

/* 
============ VISSER Hall Sensor ============ 
*/
/**
Constructor class for VISSER_HallSensor
@param int inputPin the specified input
@param int outPin the specified output pin
@param int triggerPin the specified trigger pin
@param int echoPin the specified echo pin
*/
#define HALL_MAX_ITERATION 50
#define HALL_SLOPE_VALUE   12.706
#define HALL_INTERCEPT_VALUE 31.366 
#define HALL_DIFF_THREAsHOLD 0.01

VISSER_HallSensor::VISSER_HallSensor(int LEDPin)
{
    pinMode(LEDPin, OUTPUT);
    _LEDPin = LEDPin;
    Serial.begin(9600);
}

float VISSER_HallSensor::getReadingVolts(int analogPin)
{
    int iteration;
    float sensorReading;
    for(iteration = 0; iteration < HALL_MAX_ITERATION; iteration++)
    {
        sensorReading += analogRead(analogPin);
    }

    return (sensorReading * 5.0) / (HALL_MAX_ITERATION * 1023.0); 
}

float VISSER_HallSensor::getReadingTesla(float volts)
{
    return HALL_SLOPE_VALUE * volts + HALL_INTERCEPT_VALUE;
}

void VISSER_HallSensor::blinkLED(float volt1, float volt2)
{
    if(abs(volt2 - volt1) <= HALL_DIFF_THREAsHOLD)
    {
        digitalWrite(_LEDPin, HIGH);
        delay(100); // magic number
        digitalWrite(_LEDPin, LOW);
    }
}
