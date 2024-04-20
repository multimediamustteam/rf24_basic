#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(9,8);

uint8_t address[6][5] = {
  { 0xCC, 0xCE, 0xCC, 0xCE, 0xCC },
  { 0xD1, 0xC6, 0xB5, 0xE9, 0xA3 },
  { 0xD2, 0xC6, 0xB5, 0xE9, 0xA3 },
  { 0xD3, 0xC6, 0xB5, 0xE9, 0xA3 },
  { 0xD4, 0xC6, 0xB5, 0xE9, 0xA3 },
  { 0xD5, 0xC6, 0xB5, 0xE9, 0xA3 },
  };

struct PayloadStruct{
  short humid;
  short temperature;
};

PayloadStruct payload;



void setup() {

  Serial.begin(115200);
  while (!Serial){
    //some boards need to wait to ensure access to serial over usb
  }
  Serial.println("");
  Serial.println("Hello World, Serial is working");
  Serial.println("Size of payload is " + String(sizeof(payload)) + " bytes");
  if (!radio.begin()){
    Serial.println(F("Radio hardware is not responding!"));
    while (1){}
  }

  radio.setChannel(100);
  radio.setDataRate(RF24_250KBPS);

  radio.openReadingPipe (0, address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.openReadingPipe(2, address[2]);
  radio.openReadingPipe(3, address[3]);
  radio.openReadingPipe(4, address[4]);
  radio.openReadingPipe(5, address[5]);
  radio.startListening();
  radio.setPayloadSize(sizeof(payload));

  printf_begin();
  radio.printPrettyDetails();

}

void loop() {

  //radio.printPrettyDetails();

  uint8_t pipe;
  if(radio.available(&pipe)){
      //uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
      radio.read(&payload, sizeof(payload));             // fetch payload from FIFO
      Serial.print(F("Received "));
      Serial.print(sizeof(payload));  // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);  // print the pipe number
      Serial.print(F(": "));
      Serial.println("");
      Serial.print("Received from Master: ");
      Serial.print("Humidity:");
      Serial.print(payload.humid);
      Serial.print(" Temperature:");
      Serial.print(payload.temperature);
      Serial.println("");

  }


}
