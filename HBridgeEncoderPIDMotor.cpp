/*
 * HBridgeEncoderPIDMotor.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: hephaestus
 */

#include "HBridgeEncoderPIDMotor.h"
#define HBRIDGE_DEADBAND 138
#define HBRIDGE_MAX 255
HBridgeEncoderPIDMotor::HBridgeEncoderPIDMotor() {
	// TODO Auto-generated constructor stub
	this->directionPin=-1;
}

HBridgeEncoderPIDMotor::~HBridgeEncoderPIDMotor() {
	// TODO Auto-generated destructor stub
}

void HBridgeEncoderPIDMotor::attach(int pwmPin,int directionPin,int encoderA, int encoderB){
	encoder.attachHalfQuad(encoderA, encoderB);
	this->directionPin=directionPin;
	motor.attachPin(pwmPin, 5000, 8);
	pidinit();
	pinMode(directionPin, OUTPUT);
	setOutput(0);
}
int64_t HBridgeEncoderPIDMotor::getPosition(){
	return encoder.getCount();
}
int64_t HBridgeEncoderPIDMotor::getOutputMin(){
	return -HBRIDGE_MAX;
}
int64_t HBridgeEncoderPIDMotor::getOutputMax(){
	return HBRIDGE_MAX;
}
void HBridgeEncoderPIDMotor::setOutput(int64_t out){
	if(out>0){
		  digitalWrite(directionPin, HIGH);   // turn the LED on (HIGH is the voltage level)
	}else{
		 digitalWrite(directionPin, LOW);
	}
	int myOut =abs(out);
	if (myOut<HBRIDGE_DEADBAND &&  out!=0)
		myOut=HBRIDGE_DEADBAND;
	if(out>getOutputMax())
		out=getOutputMax();
	motor.write(myOut);
}
void HBridgeEncoderPIDMotor::overrideCurrentPositionHardware(int64_t val){
	encoder.setCount(val);
}
double HBridgeEncoderPIDMotor::calcDistanceTraveled(){
//current positions
  double curPos=getPosition();
  //time change in ms from last call
  timeInterval=curTime-prevTime;
  //encoder ticks since last call
  movement=curPos-prevPos;
  //encoder ticks to degrees
  movement= movement *ticksToDeg;

  // (pi)d * degrees/360 = distance traveled by wheels
  movement = 3.1415*2*movement/360;
  return movement;
}
//This function should analogRead the current sense from the motor driver
//and convert the value to current in milliamps
double HBridgeEncoderPIDMotor::calcCur(void)
{
  //read analog value
  //convert to volts
  //converts to current in milliamps
	return 0;
}
