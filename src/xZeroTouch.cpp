/*
	This is a library for the CW01/CW02 
	ZeroTouch
*/

#include <xZeroTouch.h>

xZeroTouch::xZeroTouch(void)
{
    /*nothing to construct*/
}
       
       
xZeroTouch::~xZeroTouch(void)
{
    /*nothing to destruct*/
}

bool xZeroTouch::begin(void)
{
    begin("", "");
}

bool xZeroTouch::begin(char * SSID, char * PSK)
{
    uint8_t tick_WiFi = 0;
    #ifndef DEBUG
    Serial.println("Checking for previously stored configs.");
    #endif

    WiFi.mode(WIFI_STA);
    WiFi.begin();
    
    while ((WiFi.status() != WL_CONNECTED) && (tick_WiFi < 10))
    {
        delay(250);
        if (tick_WiFi++ >= 9) 
        {
            #ifndef DEBUG
            Serial.println("Connection Unsuccessful");
            #endif
        }
        else if(WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Connection Successful");
            return ConnectWiFi();
        }
    }
    tick_WiFi = 0;

    if(checkConfig(SSID) && checkConfig(PSK))
    {
    #ifndef DEBUG
        Serial.println("Attemping to use xFlasher Paramters");
    #endif   

        WiFi.begin(SSID, PSK);

        while ((WiFi.status() != WL_CONNECTED) && (tick_WiFi < 10))
        {
            delay(250);
            if (tick_WiFi++ >= 9) 
            {
                #ifndef DEBUG
                Serial.println("Connection Unsuccessful");
                #endif
            }
            else if(WiFi.status() == WL_CONNECTED)
            {
                Serial.println("Connection Successful");
                return ConnectWiFi();
            }
        }
    }

    if(WiFi.status() != WL_CONNECTED)
    {
        StartSmartConfig();
    }

    return ConnectWiFi();
}

void xZeroTouch::StartSmartConfig(void)
{
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BUILTIN, LOW);

    #ifndef DEBUG
    Serial.println("Awaiting Zero Touch Provisioning");
    #endif

    WiFi.beginSmartConfig();

    while(!WiFi.smartConfigDone())
    {
        delay(1000);
    }

    digitalWrite(LED_RED, LOW); 
    digitalWrite(LED_GREEN, LOW); 
    digitalWrite(LED_BUILTIN, HIGH);

    #ifndef DEBUG
    Serial.println("Zero Touch Provisioning Successful");
    #endif
}

bool xZeroTouch::ConnectWiFi(void)
{
    if(WiFi.status() == WL_CONNECTED) 
    {
        #ifndef DEBUG
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());
        Serial.print("Pre-shared key: ");
        Serial.println(WiFi.psk());
        #endif
    }
    return WiFi.status();
}

bool xZeroTouch::checkConfig(char * buffer) 
{
    if(strncmp(buffer, "$!$", 3) == 0)
    {
        return false;
    } 
    else 
    {
        return true;
    }
}