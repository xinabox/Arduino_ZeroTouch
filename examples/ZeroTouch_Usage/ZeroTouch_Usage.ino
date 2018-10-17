#include <xZeroTouch.h>

xZeroTouch ZeroTouch;

struct userData {
  char  var1[32] = "$!$SSID!0000000000000000000000!";
  char  var2[32] = "$!$PSK1!0000000000000000000000!";
};

struct userData user;

void setup() {
  Serial.begin(BAUDSPEED);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  if (ZeroTouch.begin(user.var1, user.var2))
  {
    #ifdef DEBUG
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    #endif
    digitalWrite(LED_RED, LOW); 
    digitalWrite(LED_GREEN, HIGH); 
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void loop() {

}
