#pragma config(Sensor, dgtl1,  decodeleft,     sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  decoderight,    sensorQuadEncoder)
#pragma config(Motor,  port1,           motorleft,     tmotorVex393_HBridge, openLoop, encoderPort, dgtl1)
#pragma config(Motor,  port10,          motorright,    tmotorVex393_HBridge, openLoop, reversed, encoderPort, dgtl3)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	float goaldist = 37; //in inches


	clearDebugStream();
	SensorType[in8] = sensorNone;
	wait1Msec(1000);
	SensorType[in8] = sensorGyro;
	wait1Msec(3000);

	int mspeed = 100; //default speed

	//int cycles = 100;  //Maximum number of times that the robot can adjust its speed

	int leftspeed = mspeed;
	int rightspeed = mspeed;
	float goalrotate = goaldist / 10.45;
	float goalrotateAngle = goalrotate *360;

	float newrotatel = 0;
	float newrotater = 0;

	float distl = 0;
	float distr = 0;
	float avgdist = 0;
	float avgrotate = 0;

	int newangle = 0;
	int oldangle = 0;
	int n = 0;

	//goaldist -= 8;

	while(n<1) {
		motor(motorright) = rightspeed;
		motor(motorleft) = leftspeed;
		oldangle = newangle;
		newangle = SensorValue[in8];


		newrotatel = SensorValue[dgtl1];
		newrotater = SensorValue[dgtl3];

		avgrotate = newrotatel +newrotater;
		avgrotate /= 2;

		distl = (newrotatel / 360) * 10.45;
		distr = (newrotater / 360) * 10.45;

		avgdist = distr - distl;
		avgdist = avgdist / 2;


		if (avgrotate >= goalrotateAngle || avgdist >= goaldist){
			//mspeed = 50;
			motor(motorleft) = mspeed;
			motor(motorright) = mspeed;
			n += 1;
			if(avgdist >= goaldist){
				mspeed = 0;

				while (mspeed >= - 20){
					mspeed = mspeed - 10;
					motor(motorleft) = mspeed;
					motor(motorright) = mspeed;
					wait1Msec(50);
				}
			}
			motor(motorleft) = 0;
			motor(motorright) = 0;
		}

		wait1Msec(50);

		if (SensorValue[in8] < 0) {
			if (newangle <= oldangle) {
				rightspeed = rightspeed + 2;
				leftspeed = leftspeed - 2;
			}

		}

		else if (SensorValue[in8] > 0){
			if (newangle >= oldangle) {
				rightspeed = rightspeed - 2;
				leftspeed = leftspeed + 2;
			}

		}
		else {
			leftspeed = mspeed;
			rightspeed = mspeed;

		}
	}

}
