# Lock-Bot Auto
**Vishnu Sivampeta & Andrew Liu**

**ECE 4180 Section A @GeorgiaTech** 

**Spring 2024**

![186F52DC-6AFE-4A01-8C7E-AC273A648D97](https://github.com/VishnuSivampeta/4180-Final-Project/assets/125213976/1948e6db-4b2b-4572-962d-6981b8344654)

# Video Demonstration

#

# Parts List
Adafruit Bluefruit LE UART Friend BLE https://www.adafruit.com/product/2479

Sparkfun mpr121 capacitive keypad https://www.sparkfun.com/products/retired/10250

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
| pOUT | TB6612FNG |                          | pOUT | Bluefruit LE UART |            | pOUT | Mono Audio Amp|    |  pOUT    |    HC-SR04 |       
| ------------- | ------------- | ---------- | -----------| -------------|  --------- | -----------| ---------|---| ---------| -----------|
| 5v  | VM |                | NC |  MOD|     | Speaker (+)| OUT (+) |                                         |    5V    |  VCC      |
| 5v  | VCC|                | GND | CTS|     |Speaker (-) |OUT (-) |                                             |     p12   |  Trig      | 
| GND  | GND |              | p27 | TXO|     |GND |PWR (-) |                                                     |     p13   |   Echo     |
| Rightmotor (-)  | AO1|    | p28 | RXI|     | 5v|PWR (+) |                                                      |   GND     |   GND     |
| Rightmotor (+)   | AO2|   | 5v |  VIN|     | NC|PWR (s) |
| Lefttmotor (-)   | BO2|   | NC |  RTS|     | p24|IN (+) |
| Leftmotor (+)   | BO1|    | GND | GND|     |GND |IN (-) |
| GND  | GND|               | GND | DFU|     | 10K POT (1)|VOL (1) |
| p22  | PWMA | | | |                        | 10K POT (2)|VOL (2)|    
| p5  | AI2|    |  | |                       | 10K POT (3)|VOL (3)|
| p6  | AI1 |
| 5v  | STBY|
| p7  | BI1 |
| p8  | BI2|
| p21  | PWMB |
| GND  | GND|

| pOUT  |  mpr121 |                 | mBed |  DC IN| | BreadBoard | Capacitor 1000uF|
| ------------- | ------------- |---| ---| ---| ----|-----|-----|
| GND  | GND  |                 |  VIN | 5v | | 5v| Cap|
|  p9 (5k res pu to 3.3v)| SDA  |   |GND | GND| | GND| Cap|
|  p10 (5k res pu to 3.3v) | SCL  | |
| p26  | IRQ  |
| 3.3v  | VCC  |

# Photos
![FA958D7E-4D2F-452D-A3B6-127E796B08D6](https://github.com/VishnuSivampeta/4180-Final-Project/assets/125213976/56838a48-c950-45b2-b441-311d8c78341a)
![21E0D1F8-6361-413B-AA73-432D1AD1CF92](https://github.com/VishnuSivampeta/4180-Final-Project/assets/125213976/57a660da-c50a-4cd9-a4a4-0331b6ca0543)
![DB581641-4A01-4D00-8AA4-E0C3A1700049](https://github.com/VishnuSivampeta/4180-Final-Project/assets/125213976/767075b0-a777-4901-b3dc-fdc542208eea)

# Presentation

[Lock_Bot_Auto.pdf](https://github.com/VishnuSivampeta/4180-Final-Project/files/15044427/Lock_Bot_Auto.pdf)
