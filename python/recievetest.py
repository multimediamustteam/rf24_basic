import sys
import argparse
import time
import struct
from RF24 import RF24, RF24_PA_LOW, RF24_250KBPS

radio = RF24(22,0)
#address= b"\x78\x78\x78\x78\x78"
#address = [b"1Node", b"2Node"]

#These three are equivalent, letters are not case sensitive
#address = bytearray([0xCC, 0xCE, 0xCC, 0xCE, 0xCC])
#address = b"\xcc\xce\xcc\xce\xcc"
address =  [ 
    b"\xcc\xce\xcc\xce\xcc",
    b"\xD1\xC6\xB5\xE9\xA3",
    b"\xD2\xC6\xB5\xE9\xA3",
    b"\xD3\xC6\xB5\xE9\xA3",
    b"\xD4\xC6\xB5\xE9\xA3",
    b"\xD5\xC6\xB5\xE9\xA3",    
    ]

payload = [0.0]


if not radio.begin():
    raise RuntimeError("radio hardware is not responding")

radio.setDataRate(RF24_250KBPS)
radio.setChannel(100)

radio.openReadingPipe(0,address[0])
radio.openReadingPipe(1,address[1])
radio.openReadingPipe(2,address[2])
radio.openReadingPipe(3,address[3])
radio.openReadingPipe(4,address[4])
radio.openReadingPipe(5,address[5])
radio.payloadSize= 2
radio.startListening()
radio.printPrettyDetails()


while True:
    radio.startListening()
    start_timer = time.monotonic()
    while (time.monotonic()- start_timer)< 5:
        has_payload, pipe_number= radio.available_pipe()
        if has_payload:
            temperature = struct.unpack(
                "<h", radio.read(radio.payloadSize)
            )
            print(f"Recieved {radio.payloadSize} bytes")   
            print(temperature)
            start_timer = time.monotonic()
            radio.stopListening
    print("Nothing received")
    radio.stopListening()