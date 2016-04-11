//variable declaration

int DEADZONE = 15;
float avgEncVal = 0; //average encoder value of the pivot
float pivotAngle = 0; //angle for the pivot angle to turn to
float turnValue = 0;
float forwardValue = 0;
float currentAngle = 0;

void setForwardValue(int driveY)
{
	if(driveY > DEADZONE || driveY < -DEADZONE)
	{
		forwardValue = driveY;
	}
	else
	{
		forwardValue = 0;
	}
}

void setTurnValue(int driveX)
{
	if(driveX > DEADZONE || driveX < -DEADZONE)
	{
		turnValue = driveX;
	}
	else
	{
		turnValue = 0;
	}
}

void getAvgEncVal()
{
	avgEncVal = (nMotorEncoder[frontRightPivot] + nMotorEncoder[frontLeftPivot] = 0 + nMotorEncoder[backRightPivot] +nMotorEncoder[backLeftPivot])/4;
}

void setCurrentAngle()
{
	getAvgEncVal();
	currentAngle = ((360*avgEncVal)/1023);
}

void getAngle(int x, int y) //if y is negative add 180 to the value calculated
{
	if((x == 0) && (y == 0))
	{
		pivotAngle = 0;
	}
	else if(((x/127) < 1) && ((x/127) > 0.95))
	{
		pivotAnlge = radiansToDegrees(asin(x/sqrt(x^2+y^2)));

		if(y < 0)
		{
			pivotAnlge+=180;
		}
	}
	else if(((x/127) > -1) && ((x/127) < -0.95))
	{
		pivotAnlge = radiansToDegrees(asin(x/sqrt(x^2+y^2)));

		if(y < 0)
		{
			pivotAnlge+=180;
		}
	}
	else if(((y/127) < 1) && ((y/127) > 0.95))
	{
		pivotAnlge = radiansToDegrees(acos(y/sqrt(x^2+y^2)));

		if(y < 0)
		{
			pivotAnlge+=180;
		}
	}
	else if(((y/127) > -1) && ((y/127) < -0.95))
	{
		pivotAnlge = radiansToDegrees(acos(y/sqrt(x^2+y^2)));

		if(y < 0)
		{
			pivotAnlge+=180;
		}
	}
}

void swerve(int x, int y, int speed) //speed = third axis
{
	getAngle(x,y);
	if(currentAngle < pivotAngle)
	{
			motor[frontRightPivot] = 50;
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

		motor[frontRightPivot] = speed;
		motor[frontLeftPivot] = speed;
		motor[backRightPivot] = speed;
		motor[backLeftPivot] = speed;
}

void turn() //need to work on this when using fourth axis, turn angle to cetian degree, and change speed based on input
{
	if(button)
	{
		  nMotorEncoder[frontRightPivot] = 0;
		  nMotorEncoder[frontLeftPivot] = 0;
		  nMotorEncoder[backRightPivot] = 0;
		  nMotorEncoder[backLeftPivot] = 0;
	}
}

void drive()
{
	swerve();
	turn(vexRT[Ch2]);
}
