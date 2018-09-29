/*
	This is a library for the CW01/CW02 
	ZeroTouch
*/

#ifndef xZeroTouch_h
#define xZeroTouch_h

#pragma once

#include <Arduino.h>

#ifdef  ARDUINO_ARCH_ESP32
#include "WiFi.h"
#define LED_RED 25
#define LED_GREEN 26
#define LED_BUILTIN 27
#define BAUDSPEED 115200
#elif   ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#define LED_RED 12
#define LED_GREEN 13
#define LED_BUILTIN 5
#define BAUDSPEED 74880
#else 
#error This Library only provides support for the CW01 and CW02, please select the correct board from the Menu.
#endif

class xZeroTouch 
{
    public:
        xZeroTouch();
        ~xZeroTouch();

        bool begin(void);
        bool begin(char * SSID, char * PSK);

        void StartSmartConfig(void);

        bool ConnectWiFi(void);

        bool checkConfig(char * buffer);

    private:

};
#endif
