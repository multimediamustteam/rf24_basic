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

struct payload_struct{
  int data;
};

payload_struct payload;


void setup() {

  Serial.begin(115200);
  while (!Serial){
    //some boards need to wait to ensure access to serial over usb
  }
  Serial.println("Hello World, Serial is working");

  Serial.println(sizeof(payload));
  if (!radio.begin()){
    Serial.println(F("Radio hardware is not responding!"));
    while (1){}
  }

  radio.setChannel(100);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);


  radio.setPayloadSize(sizeof(payload));
  radio.stopListening();
  radio.openWritingPipe(address[0]);
  
  
  Serial.println("Hello");
  
  printf_begin();
  radio.printPrettyDetails();


}


void loop() {

  // radio.printPrettyDetails();

  payload.data=23;//send the number 23
   
  bool report = radio.write(&payload, sizeof(int));
  
  if (report){
    // Serial.println("Transmission Successful");
  }else{
    // Serial.println("Transmission Failed");
  }

}

