# Members 
Vishnu Sivampeta, Andrew Liu

# Parts List
Adafruit Bluefruit LE UART Friend BLE https://www.adafruit.com/product/2479

Sparkfun mpr121 capacitive keypad https://www.sparkfun.com/products/retired/12017

HC-SR04 Ultrasonic Sensor https://www.sparkfun.com/products/15569

Dual TB6612FNG Motor Driver https://www.sparkfun.com/products/14450

DC Barrel Jack Adapter https://www.sparkfun.com/products/10811

2 DC Motors https://www.sparkfun.com/products/13302

2 65mm rubber wheels https://www.sparkfun.com/products/13259

Shadow Chassis https://www.sparkfun.com/products/13301

SparkFun Mono Audio Amp Breakout TPA2005D1 https://www.sparkfun.com/products/11044

PCB Mount speaker https://www.sparkfun.com/products/11089

10K Potentiometer https://www.sparkfun.com/products/9806

1000uF 25V Capacitor https://www.sparkfun.com/products/8982

Battery Holder https://www.sparkfun.com/products/552

# Schematic
| pOUT | TB6612FNG |                          | pOUT | Bluefruit LE UART |            | pOUT | Mono Audio Amp|
| ------------- | ------------- | ---------- | -----------| -------------|  --------- | -----------| -------------|
| 5v  | VM |                | NC |  MOD|     | Speaker (+)| OUT (+) |
| 5v  | VCC|                | GND | CTS|     |Speaker (-) |OUT (-) |
| GND  | GND |              | p27 | TXO|     |GND |PWR (-) |
| Rightmotor (-)  | AO1|    | p28 | RXI|     | 5v|PWR (+) |
| Rightmotor (+)   | AO2|   | 5v |  VIN|     | NC|PWR (s) |
| Lefttmotor (-)   | BO2|   | NC |  RTS|     | p24|IN (+) |
| Leftmotor (+)   | BO1|    | GND | GND|     |GND |IN (-) |
| GND  | GND|               | GND | DFU|     | POT (1)|VOL (1) |
| p22  | PWMA | | | |                        | POT (2)|VOL (2)|    
| p5  | AI2|    |  | |                       | POT (3)|VOL (3)|
| p6  | AI1 |
| 5v  | STBY|
| p7  | BI1 |
| p8  | BI2|
| p21  | PWMB |
| GND  | GND|

# Source Code

# Photos
![](https://drive.google.com/file/d/1lxhzMqgAI-F1FDUB7bZzO3_EMm682L4M/view?usp=sharing)

# Videos

# Presentation

