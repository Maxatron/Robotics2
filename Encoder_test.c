#pragma config(Sensor, dgtl1,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  ,               sensorQuadEncoder)
#pragma config(Motor,  port1,           motorleft,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port10,          motorright,    tmotorVex393_HBridge, openLoop, reversed, encoderPort, dgtl3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	int lnum = 0;
	int rnum = 0; // acting as Boolean values, idk how to do them in Robotc or C++
	int rspeed = 127;
	int lspeed = 127;

	int rotations = 3;

	int rotationangle = rotations*360; //the angle through which the encoders should record the wheels turning
	SensorValue[dgtl1] = 0; // clearing any previous readings
	SensorValue[dgtl3] = 0;

	while(1 == 1){
		if (SensorValue[dgtl1] > -1*rotationangle){
			motor(motorleft) = lspeed;
		}
		else if(SensorValue[dgtl1] < -1*rotationangle){
			lspeed = 0;
			while (lnum == 0){
				while (lspeed >= - 20){
					lspeed = lspeed - 10;
					rspeed = rspeed - 10;
					motor(motorleft) = lspeed;
					motor(motorright) = rspeed;//unfortunately, have not found a way to kill both engines independantly and accurately, so both are turned off at the same time.
					wait1Msec(50);
					lnum += 1;
					rnum+=1;
				}
			}
			motor(motorleft) = 0;
			motor(motorright) = 0;

		}
		if (SensorValue[dgtl3] < rotationangle){
			motor(motorright) = rspeed;
		}
		else if(SensorValue[dgtl3] > rotationangle){
			rspeed = 0;
			while (rnum == 0){
				while (rspeed >= - 20){
					rspeed = rspeed - 10;
					lspeed = lspeed - 10;
					motor(motorright) = rspeed;
					motor(motorleft) = lspeed;
					wait1Msec(50);
					rnum+=1;
					lnum+=1;
				}
			}
			motor(motorright) = 0;
			motor(motorleft) = 0;
		}
	}
}
