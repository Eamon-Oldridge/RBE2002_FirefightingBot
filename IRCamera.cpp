#include "IRCamera.h"
#include <DFRobotIRPosition.h>

void IRCamera::setCalibration(int acceptableError){
	calibration = acceptableError;
}

void IRCamera::setVals(){
	if (myDFRobotIRPosition.available()) {
		for (int i=0; i<4; i++) {
		  xvals[i]=myDFRobotIRPosition.readX(i);
		  yvals[i]=myDFRobotIRPosition.readY(i);
		}
	}
	else{
		Serial.println("not available");
	}
}

void IRCamera::printResult()
{
  for (int i=0; i<4; i++) {
    Serial.print(xvals[i]);
    Serial.print(",");

    Serial.print(yvals[i]);
    Serial.print(";");
  }
  Serial.println();
}

void IRCamera::attach(int sclPin, int sdaPin){
	pinMode(sdaPin, OUTPUT);
	pinMode(sclPin, OUTPUT);
}

bool IRCamera::flame(){
	for(int i=0; i<4; i++){
		if(xvals[i] < 1023-calibration || yvals[i] < 1023-calibration) return true;
	}
	return false;
}
