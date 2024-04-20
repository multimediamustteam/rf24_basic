import sys
import argparse
import time
import struct
from RF24 import RF24, RF24_PA_LOW, RF24_250KBPS

radio = RF24(22,0)

address =  [ 
    b"\xcc\xce\xcc\xce\xcc",
    b"\xD1\xC6\xB5\xE9\xA3",
    b"\xD2\xC6\xB5\xE9\xA3",
    b"\xD3\xC6\xB5\xE9\xA3",
    b"\xD4\xC6\xB5\xE9\xA3",
    b"\xD5\xC6\xB5\xE9\xA3",    
    ]

if not radio.begin():
    raise RuntimeError("radio hardware is not responding")

radio.setDataRate(RF24_250KBPS)
radio.setChannel(100)
radio.openWritingPipe(address[0])
radio.payloadSize= 4


while True:
    radio.printPrettyDetails()
    radio.stopListening()
    temperature = 88
    humid = 77
    payload = struct.pack("<hh", humid, temperature)
    print(payload)
    start_timer = time.monotonic_ns()  # start timer
    result = radio.write(payload)
    end_timer = time.monotonic_ns()  # end timer
    if not result:
        print("Transmission failed or timed out")
    else:
        print(
            "Transmission successful! Time to Transmit:",
            f"{(end_timer - start_timer) / 1000} us. Sent: {payload}",
        )
    time.sleep(0.1)
