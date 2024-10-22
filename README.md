# simplehubcircuit

Several hubs are connected to an M5 Stack AtomLite, including sensors and a relay for switching an LED

M5 Stack ATOM: Connected to the PaHub via GROVE.
PaHub: Connected to the ENV III sensor  (channel 1), the PbHub (channel 0) and qrcode scanner I2C (channel 2).  
PbHub: Connected to the M5Hall sensor (channel 0) and the Relay Unit. (channel 1).
Relay Unit: Controls the LED. (Connected COM and N0)

Library(Adafruit_SHT31) for ENV III from:
https://github.com/adafruit/Adafruit_SHT31

Libary(QRCode Scanner):
https://github.com/m5stack/M5Unit-QRCode
