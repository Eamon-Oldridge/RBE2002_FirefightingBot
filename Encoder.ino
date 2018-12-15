#include <Arduino.h>
#include <ESP32Encoder.h>
#include "HBridgeEncoderPIDMotor.h"
#include "IRCamera.h"
#include <DFRobotIRPosition.h>

ESP32Encoder encoder;
ESP32Encoder encoder2;

DFRobotIRPosition myDFRobotIRPosition;

HBridgeEncoderPIDMotor motor1;  // PID controlled motor object
HBridgeEncoderPIDMotor motor2; // PID controlled motor object

HBridgeEncoderPIDMotor * left;
HBridgeEncoderPIDMotor * right;

Servo * myTurret;
Servo turret;

IRCamera cam1;
IRCamera * myIR;

bool fan = true;

int fanPin = 12; //36

int encPinAL = 13;
int encPinBL = 25;
int encPinAR = 26;
int encPinBR = 27;
int pwmPinL = 18; // left motor pwm
int pwmPinR = 17; // right motor pwm
int dirPinL = 14; // left hbridge dir pin
	// ^^ should be 14
int dirPinR = 33; // right hbridge dir pin
//int rangePinRight = x;

int turretPin = 32;

void setup(){
	Serial.begin(115200);

		// ATTACH IMU

	pinMode(pwmPinL, OUTPUT);
	pinMode(pwmPinR, OUTPUT);
	pinMode(encPinAR, INPUT);
	pinMode(encPinBR, INPUT);
	pinMode(encPinAL, INPUT);
	pinMode(encPinBL, INPUT);
	pinMode(fanPin, OUTPUT);
	pinMode(turretPin, OUTPUT);
//	pinMode(rangePinRight, INPUT);

	left = new HBridgeEncoderPIDMotor();
	right = new HBridgeEncoderPIDMotor();
	myIR = new IRCamera();
	myTurret = new Servo();

	Serial.println("testing print");
	left->attach(pwmPinL, dirPinL, encPinAL, encPinBL);
	right->attach(pwmPinR, dirPinR, encPinAR, encPinBR);
	myIR->attach(22, 21);
	myIR->setCalibration(500);
	myTurret->attach(turretPin);

	myDFRobotIRPosition.begin();

	delay(5000);
}

//void printResult()
//{
//  for (int i=0; i<4; i++) {
//    Serial.print(positionX[i]);
//    Serial.print(",");
//
//    Serial.print(positionY[i]);
//    Serial.print(";");
//  }
//  Serial.println();
//}

void driveStraight(){
	right->setOutput(right->getOutputMax());
	left->setOutput(left->getOutputMin());
}

bool inRange;

void loop(){
//	digitalWrite(fanPin, LOW);
//	Serial.println("Fan H");
//	delay(1000);
//    digitalWrite(fanPin, HIGH);
//	Serial.println("Fan L");
//    delay(1000);
//    myTurret->write(50);
//    Serial.println("servo 50");
//    delay(1000);
//    myTurret->write(130);
//    Serial.println("servo 130");
//    delay(1000);




	Serial.println("loop begin");
//	Serial.println((int)right->getOutputMax());
//	Serial.println((int)right->getOutputMin());

//	inRange = (digitalRead(rangePinRight) < 500);
//
//	if(!inRange){
//		driveStraight();
//	}
//	else{
//	}
//	Serial.println(fan);

		myIR->myDFRobotIRPosition.requestPosition();

		myIR->setVals();

//	    myIR->printResult();

//	    Serial.println(myIR->flame());


	Serial.println("driving straight");
//	driveStraight();
	right->setOutput(right->getOutputMin());
	left->setOutput(left->getOutputMax());

//	myIR->setVals();
	if(myIR->flame()){
		delay(2500);
		left->setOutput(0);
		right->setOutput(0);
		Serial.println("flame detected!");
		digitalWrite(fanPin, LOW);
		delay(4000);
		digitalWrite(fanPin, HIGH);
		while(1);
	}
	else{
		Serial.println("no flame :)");
		digitalWrite(fanPin, HIGH);
	}


	Serial.println("test no 3");
//	digitalWrite(fanPin, LOW);
//	delay(1000);





}


