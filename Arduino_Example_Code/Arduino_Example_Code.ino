

#include <Servo.h>
unsigned int receivedValue = 0;
Servo myservo;  // create servo object to control a servo


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  //while (!Serial); // wait for serial port to connect. Needed for native USB port only, this port is for displaying data Grove Sensor sends

  // Serial.println("USB Serial Port connection Established!");

  // Set the data rate for the SoftwareSerial port - Grove Offline Voice Recognition Module runs at 9600 baud rate
}

void loop() {

  if (Serial.available()) {
    Serial.println("Data From VC-02");
    // Read the incoming bytes
    byte highByte = Serial.read();
    byte lowByte = Serial.read();

    // Combine the two bytes into a single 16-bit value
    receivedValue = (highByte << 8) | lowByte;

    // Print the received value in HEX format
    Serial.print("Received HEX value: 0x");
    Serial.println(receivedValue, HEX);
  }

  if (receivedValue == 0xA190)  // Check if the value is A2 in HEX
  {
    myservo.write(90);  // sets the servo position according to the scaled value
    delay(15);
  } else if (receivedValue == 0xA145) {
    myservo.write(45);  // sets the servo position according to the scaled value
    delay(15);
  } else {
  }
  delay(10);
  receivedValue = 0;
}
