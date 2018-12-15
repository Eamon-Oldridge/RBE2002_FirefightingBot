// IRCamera.h

#include <ESP32Servo.h>
#include <DFRobotIRPosition.h>

#ifndef SRC_IRCAMERA_H_
#define SRC_IRCAMERA_H_
class IRCamera {
private:

	int calibration = 0;

public:
	DFRobotIRPosition myDFRobotIRPosition;
	int xvals[4];
	int yvals[4];



	void attach(int sclPin, int sdaPin);
	void setCalibration(int acceptableError);
	bool flame();
	void setVals();
	void printResult();

};
#endif
