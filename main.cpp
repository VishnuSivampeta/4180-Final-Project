/*
------------------------------------------------------------
Final Project for ECE_4180 Embedded Systems at Georgia Tech
Andrew Liu
Vishnu Sivampeta
-------------------------------------------------------------

For our project, we designed a robot that you can control through the Adafruit Bluefruit Connect app that has 2 distinct modes:
1) A mode that lets the user control the car through the Bluefruit controller using arrow keys
2) A second roomba-style mode that makes the car move forward automatically, and when it gets too close to a wall, it will back up, turn, and continue going forward

To enter these modes, we have a passcode system using the mpr121 I2C touchpad from Sparkfun on the robot
Code for manual control mode: 4180
Code for automatic "roomba" mode: 5291

Once in one of these modes, the user cannot use the keypad to enter the other mode until they have "locked" the car using the correct numbered keypad on the Bluefruit App
Lock manual mode: 1
Lock roomba mode: 2

Once locked, the car is now idle and awaits a password

We also added some tones that play when the robot gets an input that goes to a password that also light up the built-in LEDs on the mbed

And maybe some jingles when you enter and exit different modes...
*/

#include "Motor.h"
#include "mbed.h"
#include "PwmOut.h"
#include "rtos.h"
#include <string>
#include <list>
#include "SongPlayer.h"
#include "ultrasonic.h"
#include <mpr121.h>


Serial blue(p28,p27);
Motor m1(p22, p6, p5); // pwm, fwd, rev RIGHT MOTOR
Motor m2(p21, p7, p8); // left motor
Mutex mutex;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// Interrupt Receiver for the mpr121 I2C touchpad
InterruptIn interrupt(p26);

// Setup the Serial to the PC for debugging
Serial pc(USBTX, USBRX);

// Setup the i2c bus on pins 28 and 27
I2C i2c(p9, p10);

// Setup the Mpr121:
Mpr121 mpr121(&i2c, Mpr121::ADD_VSS);

//Use PWM p24 for the speaker
SongPlayer mySpeaker(p24);

//Spongebob tune for when we lock the car (using 1 or 2 on the bluetooth app on your phone)
float lockSound[9]= {1568, 1760, 1975, 1760, 1975, 1568, 0, 1175, 1568};
float lockduration[9]= {0.2,0.2,0.2,0.4,0.15,0.2, 0.2 ,0.2, 0.2};

//tune for when the robot enters manual control mode
float duration[18]= {0.48,0.24,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.0
                    };
float note[18]= {1568.0,1396.9,1244.5,1244.5,1396.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5, 0.0
                };

//tune to play when the robot enters roomba mode
float roombasound[9] = {523.25, 659.26, 783.99, 987.77, 1046.5, 1396.91, 1318.51, 1174.66, 1318.51};
float roombaduration[9] = {0.2, 0.2, 0.2, 0.4, 0.4, 0.2, 0.2, 0.2, 0.4};

//Tone for putting in the manual mode
float thing[1] = {1568};
float thingduration[1] = {0.2};

//Play a lower tone (D) when you push in the code for roomba mode
float t[1] = {1175};

//Global flags to activate modes and store data for keypad
volatile bool locked = 1;
volatile bool roomba = 0;
volatile int mru = 0;

//Interrupt code for keypad behavior 
//This is where we initialize the code combination
void fallInterrupt() {
    int key_code=0;
    int i=0;
    int value=mpr121.read(0x00);
    value +=mpr121.read(0x01)<<8;
    i=0;
    for (i=0; i<12; i++) {
        if (((value>>i)&0x01)==1) key_code=i+1;
        }
    led4=key_code & 0x01;
    led3=(key_code>>1) & 0x01;
    led2=(key_code>>2) & 0x01;
    led1=(key_code>>3) & 0x01;

    //-----------------------------
    //Code to unlock the car: password is 4180
    if (key_code == 5 && !roomba && locked) {
            mru = 5;
            led1 = 1;
           led2 = 1;
           led3 = 1;
           led4 = 1;
           mySpeaker.PlaySong(thing,thingduration);
           
    }
        if (key_code == 2 && mru == 5) {
        mru = 2;
            led1 = 1;
           led2 = 1;
           led3 = 1;
           led4 = 1;
           mySpeaker.PlaySong(thing,thingduration);
    }
        if (key_code == 9 && mru == 2) {
        mru = 9;
            led1 = 1;
           led2 = 1;
           led3 = 1;
           led4 = 1;
           mySpeaker.PlaySong(thing,thingduration);
    }
    if (key_code == 1 && mru == 9) {
            led1 = 1;
           led2 = 1;
           led3 = 1;
           led4 = 1;
            //Unlock the car here
            locked = 0;
            roomba = 0; //turn off roomba mode
            mySpeaker.PlaySong(note,duration);
    }


    //code for roomba mode: 5291
    if (key_code == 6 && locked && !roomba) {
            mru = 6;
            led1 = 1;
           led2 = 0;
           led3 = 0;
           led4 = 1;
            mySpeaker.PlaySong(t,thingduration);
    }
        if (key_code == 3 && mru == 6) {
        mru = 3;
            led1 = 1;
           led2 = 0;
           led3 = 0;
           led4 = 1;
           mySpeaker.PlaySong(t,thingduration);
    }
        if (key_code == 10 && mru == 3) {
        mru = 10;
            led1 = 1;
           led2 = 0;
           led3 = 0;
           led4 = 1;
           mySpeaker.PlaySong(t,thingduration);
    }
    if (key_code == 2 && mru == 10) {
            
            led1 = 1;
           led2 = 0;
           led3 = 0;
           led4 = 1;
           roomba = 1; //set the roomba flag high
           locked = 1; //lock the car so it doesnt enter manual mode
           mySpeaker.PlaySong(roombasound,roombaduration);
    }

}

//code for the bluetooth controller, which always runs in a thread
//locks the robot with keys 1 and 2 for manual and roomba modes respectively
void drive()
{ 
   
    char bnum=0;
    char bhit=0;
    while(1) {
        if (!locked) { //change the LEDs to indicate manual mode
            led1 = 1;
            led2 = 1;
            led3 = 1;
            led4 = 1;  
        } else {
            led1 = 0;
            led2 = 0;
            led3 = 0;
            led4 = 0;
        }
        if (blue.getc()=='!') {
            if (blue.getc()=='B') { //button data packet
                bnum = blue.getc(); //button number
                bhit = blue.getc(); //1=hit, 0=release
                if (blue.getc()==char(~('!' + 'B' + bnum + bhit))) { //checksum OK?
                    //myled = bnum - '0'; //current button number will appear on LEDs
                    switch (bnum) {
                        mutex.lock();
                        case '1': //number button 1
                            if (!roomba && bhit=='1') {
                                //LOCK the car from manual mode
                                locked = 1;
                                led1 = 0;
                                led2 = 0;
                                led3 = 0;
                                led4 = 0;
                                mySpeaker.PlaySong(lockSound,lockduration);
                            } else {
                                //add release code here
                            }
                            break;
                        case '2': //number button 2 
                            if (roomba && bhit=='1') {
                                //LOCK the car from roomba mode
                                mySpeaker.PlaySong(lockSound, lockduration);
                                roomba = 0;
                                
                            } else {
                                //add release code here
                            }
                            break;
                        case '3': //number button 3
                            if (bhit=='1') {
                                //add hit code here
                            } else {
                                //add release code here
                            }
                            break;
                        case '4': //number button 4
                            if (bhit=='1') {
                                //add hit code here
                            } else {
                                //add release code here
                            }
                            break;
                        case '5': //button 5 up arrow
                            if (!locked && bhit=='1') {
                                
                                m1.speed(1.0);
                                m2.speed(1.0);
                                 
                                
                            } else {
                                //add release code here
                                
                                m1.speed(0.0);
                                m2.speed(0.0);
                                
                            }
                            break;
                        case '6': //button 6 down arrow
                            if (!locked && bhit=='1') {
                                //add hit code here
                                led1 = 1;
                                m1.speed(-1.0);
                                m2.speed(-1.0);
                                
                                
                            } else {
                                //add release code here
                                led1 = 0;
                                m1.speed(0.0);
                                m2.speed(0.0);
                                
                            }
                            break;
                        case '7': //button 7 left arrow
                            if (!locked && bhit=='1') {
                                //add hit code here
                                led2 = 1;
                                m1.speed(1.0);
                                m2.speed(-1.0); 
                                
                            } else {
                                led2 = 0;
                                //add release code here
                                m1.speed(0.0);
                                m2.speed(0.0);
                                
                            }
                            break;
                        case '8': //button 8 right arrow
                            if (!locked && bhit=='1') {
                                //add hit code here
                                m1.speed(-1.0);
                                m2.speed(1.0);
                                
                            } else {
                                //add release code here
                                m1.speed(0.0);
                                m2.speed(0.0);
                                
                            }
                            break;
                        default:
                            break;
                            mutex.unlock();
                    }
                }
            }
        }
        Thread::wait(1.0);
    }

    
}

//dist method to read values on the ultrasonic sensor whenever they change
 void dist(int distance)
{
    //when we get too close to a wall, we turn the car
    if (distance < 120) { 
        mutex.lock();
        m1.speed(-0.5); //back up first
        m2.speed(-0.5);
        wait(1); 
        m1.speed(-0.5); //turn
        m2.speed(0.5);
        wait(0.4);
        m1.speed(0.5); //keep going
        m2.speed(0.5);
        mutex.unlock(); 
    }

}

//Distance sensor
ultrasonic mu(p12, p13, .1, 1, &dist);

int main() {

    interrupt.fall(&fallInterrupt);
    interrupt.mode(PullUp);
    Thread t2(drive);
    mu.startUpdates();//start measuring the distance

    while (1) {
        if (roomba) { //code for when in roomba mode

            mu.checkDistance();     //call checkDistance() as much as possible, as this is where
            mutex.lock();
            m1.speed(0.5); //keep the car moving forward when in roomba mode
            m2.speed(0.5);
            mutex.unlock();
            
        } else if (!roomba && locked) {
            mutex.lock();
            m1.speed(0.0); //stop the car otherwise
            m2.speed(0.0);
            mutex.unlock(); 
        }
        Thread::wait(1.0);
    }
    

}