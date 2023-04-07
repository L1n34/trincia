#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino_FreeRTOS.h>

#define MOWER_LEFT_PISTON_HEIGHT_PIN 40     //piston height cut
#define MOWER_RIGHT_PISTON_HEIGHT_PIN 41    //piston height cut
#define TRACK_LEFT_UNLOCK_PIN 42            //piston lock
#define TRACK_RIGHT_UNLOCK_PIN 43           //piston lock
#define SAFETY_STOP_PIN 44                  //safety stop

//servos
Servo throttle;
Servo brakes;
Servo shifter_selector;
Servo shifter_clutch;
Servo track_right_mode;
Servo track_left_mode;
Servo mower_engage;
Servo mower_brakes;

//rf24
RF24 radio(7, 8); //CE, CSN
const byte address[6] = "00001";

//struct for data receiver
struct Data_Pack {
int throttle;
int shifter_gear;
bool shifter_clutch;
int track_right_mode;
int track_left_mode;
bool mower_engage;
};


void setup() {

    //servo initialization
    throttle.attach(22);            //var 0 180                   potentiometer
    brakes.attach(24);              //0 180                       by software -> on when shifter on 0 otherwise off
    shifter_selector.attach(28);    //var 0 180  r 0 1 2 3        receive r 0 1 2 3
    shifter_clutch.attach(30);      //0 180                       by software & receive
    track_right_mode.attach(32);    //var 0 180 3 pos             receive 3 values pos 1 pos 2 pos 3
    track_left_mode.attach(34);     //var 0 180  3 pos            receive 3 values pos 1 pos 2 pos 3
    mower_engage.attach(36);        //0 180                       receive a boolean valor 0 = disengage 1 = engage
    mower_brakes.attach(38);        //optional                    by software -> on when mower_engage on 0 otherwise off

    //electric pistons initialization
    pinMode(MOWER_LEFT_PISTON_HEIGHT_PIN, OUTPUT);
    pinMode(MOWER_RIGHT_PISTON_HEIGHT_PIN, OUTPUT);
    pinMode(TRACK_LEFT_UNLOCK_PIN, OUTPUT);
    pinMode(TRACK_RIGHT_UNLOCK_PIN, OUTPUT);
    pinMode(SAFETY_STOP_PIN, OUTPUT);

    //rf24 connection initialization
    radio.begin();
    radio.setChannel(125);
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();

    //struct initialize
    struct Data_Pack initial_values{50, 0, LOW, 3, 3, LOW}; //pls remember Franz to insert correct value for servo control

    //send data pack value for debug
    Serial.begin(9600);
    Serial.println(initial_values.throttle);
    Serial.println(initial_values.shifter_gear);
    Serial.println(initial_values.shifter_clutch);
    Serial.println(initial_values.track_right_mode);
    Serial.println(initial_values.track_left_mode);
    Serial.println(initial_values.mower_engage);
    Serial.end();
}


void loop() {


}