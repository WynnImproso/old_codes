/**
VISSER Code Library Header file
Created for VISSER September 5, 2014 
Version 1.0
*/
#ifndef VISSER_h
#define VISSER_h

#include "Arduino.h"

class VISSER_Test
{
    public: 
        VISSER_Test(int pin);
        void blink();
        void blink(int millis);
    private:
        int _testPin;
};

class VISSER_Temperature
{
    public:
        VISSER_Temperature(bool internalReference);
        // VISSER_Temperature(int sensor, bool internalReference);
        // VISSER_Temperature(int sensor1, int sensor2, bool internalReference);
        // VISSER_Temperature(int sensor1, int sensor2, int sensor3, bool internalReference);
        // VISSER_Temperature(int sensor1, int sensor2, int sensor3, int sensor4, bool internalReference);
        // int getSensor1();
        // int getSensor2();
        // int getSensor3();
        float getReading(int sensor);
    private:
        // char * floatToString(char * output, double value, byte precision, byte width);
        // int _sensor1;
        // int _sensor2;
        // int _sensor3;
        // int _sensor4;
        bool _internalReference;
};

class VISSER_HighTemperature
{
    public:
        VISSER_HighTemperature();
        float getReading(int sensor);
};

class VISSER_Conductivity
{
    public:
        VISSER_Conductivity();
        float getReading(int sensor);
};

class VISSER_Pulse
{
    public: 
        VISSER_Pulse();
        float getFrequency(int sensor);
        int getPulse(float frequency);
};

class VISSER_CO2Sensor
{
    public: 
        VISSER_CO2Sensor();
        float getVoltage(int sensor);
        float getReading(float voltage);
};

class VISSER_DistanceSensor 
{
    public: 
        VISSER_DistanceSensor(int outPin, int triggerPin, int echoPin);
        double getDuration();
        double getReadingInches(double duration);
        double getReadingCentimeters(double duration);
    private:
        int _outPin;
        int _triggerPin;
        int _echoPin;
};

class VISSER_HallSensor
{
    public:
        VISSER_HallSensor(int _LEDPin);
        float getReadingVolts(int sensor);
        float getReadingTesla(float volts);
        void blinkLED(float volt1, float volt2);
    private:
        int _LEDPin;

};

#endif