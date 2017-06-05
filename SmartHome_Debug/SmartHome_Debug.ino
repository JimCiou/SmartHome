#include <SoftwareSerial.h>
SoftwareSerial debug(4, 5);

void setup() {
  // Open serial communications and wait for port to open:
  // Wait for serial port (9600) to connect. Needed for native USB port only
  Serial.begin(9600);
  while (!Serial) {;}
  Serial.println("Started");

  // Set the baud rate for the SoftwareSerial port (esp8266)
  // If you don't know the exact value, try a few times until get a reply "OK" (9600...115200?)
  debug.begin(9600);
  debug.write("AT\r\n");
}

void loop() {
  if (debug.available()) {
    Serial.write(debug.read());
  }
  if (Serial.available()) {
    debug.write(Serial.read());
  }
}
