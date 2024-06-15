
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TEMPLATE ID"
#define BLYNK_TEMPLATE_NAME "TEMPLATE NAME"
#define BLYNK_AUTH_TOKEN "AUTH TOKEN"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
unsigned int receivedValue = 0;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASS";

BLYNK_WRITE(V0) {
  int value = param.asInt();
  Serial.print("Received Data - ");
  Serial.println(value);
  digitalWrite(2, value);
}

void setup() {
  // Debug console
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(2, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  if (Serial2.available()) {
    // Read the incoming bytes
    byte highByte = Serial2.read();
    byte lowByte = Serial2.read();

    // Combine the two bytes into a single 16-bit value
    receivedValue = (highByte << 8) | lowByte;

    // Print the received value in HEX format
    Serial.print("Received HEX value: 0x");
    Serial.println(receivedValue, HEX);
  }

  if (receivedValue == 0xAA11)  // Check if the value is A2 in HEX
  {
    digitalWrite(2, HIGH);  // Turn the built-in LED on
    Blynk.virtualWrite(V0, 1);
  } else if(receivedValue == 0xAA00) {
    digitalWrite(2, LOW);  // Turn the built-in LED off
    Blynk.virtualWrite(V0, 0);
  }
  else
  delay(10);
  receivedValue = 0;
}
