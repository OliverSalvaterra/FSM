#pragma config(Sensor, port3,  color,          sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port4,  gyro,           sensorVexIQ_Gyro)
#pragma config(Sensor, port5,  scanner,        sensorVexIQ_Color12Color)
#pragma config(Motor,  motor1,           ,             tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor6,           ,             tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         arm,           tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor11,         claw,          tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//IMPORTANT!!! YOU DON'T NEED TO INTAKE, JUST DRIVE INTO A RING AND IT WILL INTAKE
// YOU DON'T NEED TO SCORE THE RING JUST POSITION THE ARM NEAR THE POST AND IT WILL SCORE
// YOU CAN JUST DRIVE INTO THE BONUS TRAY AND IT WILL KNOW THE SWITCH OVE RNO MATTER WHAT

enum State
{
	turn1,
	moveback1,
	liftBar1,
	turn2,
	moveForward1,
	turn3,
	moveForward2,
	turn4,
	moveForward3,
	liftBar2,
	turn5,
	moveback2,
	lowerBar1,
	moveForward4,
	moveback3,
	raiseBar1,
	turn6,
	moveForward5,
	turn7,
	moveForward6,
	moveback4,
	lowerBar2,
	moveForward7,
	moveback5,
	liftBar3,
	moveForward8,
	moveback6,
	turn8,
	lowerBar3,
	moveForward9,
	moveback7,
	liftBar4,
	turn9,
	moveForward10,
	moveback8,
	turn10,
	moveforward11,
	turn11,
	lowerBar4,
	moveforward12,
	moveback9,
	turn12,
	moveforward13,
	turn13,
	moveforward14,
	end
};

State currentState;
int count = 0;

void moveArm(State nextState, int power, int degrees)
{
	motor[arm] = power;
	if(abs(nMotorEncoder[arm]) >= degrees)
	{
		nMotorEncoder[arm] = 0;
		motor[arm] = 0;
		currentState = nextstate;
	}
}

void moveLine(int lines, int power, State nextState)
{
	motor[motor1] = power;
	motor[motor6] = power;
	if(getColorGrayscale(color) <= 50)
	{
		count++;
	}
	if(count >= lines)
	{
		motor[motor1] = 0;
		motor[motor6] = 0;
		currentState = nextState;
		count = 0;
	}
}

void lowerScore(State nextState)
{
	motor[arm] = 50;
	if(abs(nMotorEncoder[arm]) >= 200)
	{
		motor[arm] = 0;
		nMotorEncoder[arm] = 0;
		currentState = nextState;
	}
}

void upperScore(State nextState)
{
	motor[arm] = 50;
	if(abs(nMotorEncoder[arm]) >= 400)
	{
		currentState = nextState;
		nMotorEncoder[arm] = 0;
	}
}

void degrees(State nextState, int degrees, int powerl, int powerr)
{
	motor[motor1] = powerl;
	motor[motor6] = powerr;
	if(abs(nMotorEncoder[motor1]) >= degrees)
	{
		nMotorEncoder[motor1] = 0;
		motor[motor1] = 0;
		motor[motor6] = 0;
		currentState = nextState;
	}
}

void turn(State nextState, int direction, int power, int turnAngle) // left turn = 0, right turn  = 1
{

	if(direction == 1)
	{
		motor[motor1] = power;
		motor[motor6] = -1*power;
	}
	else
	{
		motor[motor1] = -1*power;
		motor[motor6] = power;
	}
	if(abs(SensorValue[gyro]) >= turnAngle)
	{
		motor[motor1] = 0;
		motor[motor6] = 0;
		currentState = nextState;
		resetGyro(gyro);
		nMotorEncoder[motor1] = 0;
	}
}

task main()
{
	setColorMode(color, colorTypeGrayscale_Reflected);
	currentState = turn1;
	nMotorEncoder[arm] = 0;
	nMotorEncoder[motor1] = 0;
	while(true)
	{
		switch(currentState)
		{
		case turn1: //intake first ring
			turn(moveback1, 1, 50, 90);
			break;

		case moveback1: //setting up to score
			degrees(liftBar1, 40, 75, 75);
			break;

		case liftBar1:
			lowerScore(turn2);
			break;

		case turn2:
			turn(moveForward1, 0, 50, 45);
			break;

		case moveForward1: //scoring
			degrees(turn3, 250, 70, 70);
			break;

		case turn3: //moving to bonus post
			turn(moveForward2, 0, 50, 90);
			break;

		case moveForward2:
			degrees(turn4, 1250, 75, 75);
			break;

		case turn4:
			turn(moveForward3, 1, 50, 45);
			break;

		case moveForward3:
			degrees(liftBar2, 200, 75, 75);
			break;

		case liftBar2:
			moveArm(turn5, 75, 120);
			break;

		case turn5:
			turn(moveBack2, 0, 50, 90);
			break;

		case moveback2:
			degrees(lowerBar1, 300, -75, -75);
			break;

		case lowerBar1:
			moveArm(moveForward4, -75, 245);
			break;

		case moveForward4: //intake ring from bonus post
			degrees(moveback3, 350, 75, 75);
			break;

		case moveback3: //getting ring off post
			degrees(raiseBar1, 50, -100, -100);
			break;

		case raiseBar1: //setting to score ring
			moveArm(turn6, 75, 100);
			break;

		case turn6:
			turn(moveForward5, 0, 50, 115);
			break;

		case moveForward5:
			degrees(turn7, 725, 75, 75);
			break;

		case turn7:
			turn(moveForward6, 0, 50, 65);
			break;

		case moveForward6: //scoring ring
			degrees(moveBack4, 350, 75, 75);
			break;

		case moveback4: //setting to intake ring
			degrees(lowerBar2, 500, -75, -75);
			break;

		case lowerBar2:
			moveArm(moveForward7, -75, 160);
			break;

		case moveForward7: //intake ring
			degrees(moveback5, 650, 100, 100);
			break;

		case moveback5:
			degrees(liftBar3, 750, -75, -75);
			break;

		case liftBar3:
			moveArm(moveForward8, 75, 380);
			break;

		case moveForward8: //score ring
			degrees(moveback6, 830, 50, 50);
			break;

		case moveback6: //setting to intake second green ring
			degrees(turn8, 250, -70, -70);
			break;

		case turn8:
			turn(lowerBar3, 1, 50, 40);
			break;

		case lowerBar3:
			moveArm(moveForward9, -75, 410);
			break;

		case moveForward9:
			degrees(moveback7, 500, 75, 75);
			break;

		case moveback7:
			degrees(liftBar4, 150, -50, -50);
			break;

		case liftBar4:
			moveArm(turn9, 75, 400);
			break;

		case turn9:
			turn(moveForward10, 0, 50, 75);
			break;

		case moveForward10:
			degrees(moveback8, 75, 50, 50);
			break;

		case moveback8:
			degrees(turn10, 150, -50, -50);
			break;

		case turn10:
			turn(moveforward11, 0, 50, 100);
			break;

		case moveforward11:
			degrees(turn11, 1250, 75, 75);
			break;

		case turn11:
			turn(lowerBar4, 1, 50, 45);
			break;

		case lowerBar4:
			moveArm(moveforward12, -50, 400);
			break;

		case moveforward12:
			degrees(moveback9, 2650, 100, 100);
			break;

		case moveback9:
			degrees(turn12, 100, -50, -50);
			break;

		case turn12:
			turn(moveforward13, 1, 100, 90);
			break;

		case moveforward13:
			degrees(turn13, 1400, 75, 75);
			break;

		case turn13:
			turn(moveforward14, 0, 50, 90);
			break;

		case moveforward14:
			degrees(end, 350, 50, 50);
			break;
		}
	}
}
