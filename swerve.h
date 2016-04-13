//variable declaration

int DEADZONE = 15; //limit that makes joystick input less sensitive
float pivotAngle = 0; //angle for the pivot angle to turn to
float currentAngle = 0; //the current angle of the pivot motor
float swerveSpeed = 0; //hypotenuse of x and y coordinate for swerve axis
//float turnValue = 0;
//float forwardValue = 0;

//functions
/*
void setForwardSpeed(int speed)
{
	if(speed > DEADZONE || -speed < DEADZONE)
	{
		///forwardValue = speed;

		//is this needed?
		motor[frontRightMotor] = speed; //don't forget to invert :)
		motor[frontLeftMotor] = speed;
		motor[backRightMotor] = speed;
		motor[backLeftMotor] = speed;
	}
	else
	{
		//forwardValue = 0;
	}
}
*/

/*
void setTurnValue(int speed)
{
	if(speed > DEADZONE || -speed < DEADZONE)
	{
		turnValue = speed;
	}
	else
	{
		turnValue = 0;
	}
}
*/

void setCurrentAngle() //Current angle is equal to avergae encoder value - conversion is not necessary - full roation is 360 tick
{
	currentAngle = ((nMotorEncoder[frontRightPivot]%360) + (nMotorEncoder[frontLeftPivot]%360) + (nMotorEncoder[backRightPivot]%360) + (nMotorEncoder[backLeftPivot]%360))/4;
} //need to somehow accomodate err from individual encoder...

void getAngle(int x, int y) //gets angle from the joystick input
{
	float joyX = x/127; //conversion of joystick (127 to 1)
	float joyY = y/127;
	swerveSpeed = sqrt(x^2+y^2); //hypotenuse of x and y input from joystick - helps us to find angle :)

	if((x == 0) && (y == 0)) //0,0 will give err if I ma using trig function
	{
		pivotAngle = 0;
	}
	else if(((joyX) < 1) && ((joyX) > 0.2)) //Decreasing sensitivity - adjust second value to increase sensitivity
	{
		pivotAngle = radiansToDegrees(asin(x/swerveSpeed)); //finding anlge - arcsin of x/hyp and converting to degree

		if(y < 0)
		{
			pivotAngle+=180; //if y is negative add 180 to the value calculated - sin and cos will only calculate up to 180
		}
	}
	else if(((joyX) > -1) && ((joyX) < -0.2))
	{
		pivotAngle = radiansToDegrees(asin(x/swerveSpeed));

		if(y < 0)
		{
			pivotAngle+=180;
		}
	}
	else if(((joyY) < 1) && ((joyY) > 0.2))
	{
		pivotAngle = radiansToDegrees(acos(y/swerveSpeed)); //arc sin and arc cos function returns radius, so you need to convet if necessary

		if(y < 0)
		{
			pivotAngle+=180;
		}
	}
	else if(((joyY) > -1) && ((joyY) < -0.2))
	{
		pivotAngle = radiansToDegrees(acos(y/swerveSpeed));

		if(y < 0)
		{
			pivotAngle+=180;
		}
	}
}

void swerve(int x, int y) //moves pivot angle and gives speed based on hypotenuse of joystick
{
	setCurrentAngle();
	getAngle(x,y);
	if(currentAngle < pivotAngle)//when current pivot angle is less then intended angle from input, move the pivot angle
	{
			motor[frontRightPivot] = 50; //double check max motor value :)(-127 to 127)
		  motor[frontLeftPivot] = 50;
		  motor[backRightPivot] = 50;
		  motor[backLeftPivot] = 50;
	}
	else
	{
			motor[frontRightPivot] = 0;
		  motor[frontLeftPivot] = 0;
		  motor[backRightPivot] = 0;
		  motor[backLeftPivot] = 0;
	}
	motor[frontRightMotor] = swerveSpeed; //don't forget to invert :) - manually or through initial setting -
	motor[frontLeftMotor] = swerveSpeed;
	motor[backRightMotor] = swerveSpeed;
	motor[backLeftMotor] = swerveSpeed;
}

void turn(int speed) //turns fast or slower based on joystick input
{
	float fREncVal = nMotorEncoder[frontRightPivot]%360; // rematinder from (360/EncVal). Will always return 0-360.
	float fLEncVal = nMotorEncoder[frontLeftPivot]%360;
	float bREncVal = nMotorEncoder[backRightPivot]%360;
	float bLEncVal = nMotorEncoder[backLeftPivot]%360;

	if(DEADZONE < speed || -DEADZONE > speed) //when joystick is move out of DEADZONE, the turn activates
	{
		  if(fREncVal > 44.5 && fREncVal <45 ) // sets pivot angle to certain angel that makes rotation possible - need to find out way to optimize this
		  {
		  	motor[frontRightPivot] = 50;
		  }

		  if(fLEncVal > 134.5 && fLEncVal <135 )
		  {
		  	motor[frontLeftPivot] = 50;
		  }

		  if(bREncVal > 224.5 && bREncVal < 225 )
		  {
		  	motor[backRightPivot] = 50;
		  }

		  if(bLEncVal > 314.5 && bLEncVal <315 )
		  {
		  	motor[backLeftPivot] = 50;
		  }
	}
	else
	{
			motor[frontRightPivot] = 0;
		  motor[frontLeftPivot] = 0;
		  motor[backRightPivot] = 0;
		  motor[backLeftPivot] = 0;
	}
	motor[frontRightMotor] = speed; //left side has to be negative in order to turn - vetor diagram will help you understand why
	motor[frontLeftMotor] = -speed; //don't forget to invert :)
	motor[backRightMotor] = speed;
	motor[backLeftMotor] = -speed;
}

void drive()
{
	swerve(vexRT[Ch3],vexRT[Ch4]); //changes anlge according to angle of
	//setForwardSpeed(vexRT[Ch2]); //figure out how to turn and swerve at the same time
	turn(vexRT[Ch1]); //sets up pivot angle to certain position so that it can rotate at given value
}
