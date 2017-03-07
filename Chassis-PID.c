void pidStraight(bool forward,bool ifLift,bool ifHoldPincher,int target)
{
	float kPL;
	float kPR;
	float kIL;
	float kIR;
	float kDL;
	float kDR;
	float indexR=0.0;
	float indexL=0.0;
	int integralLimit;
	if(target>=1200)
	{
		kPL = 0.3*1.3;
		kPR = 0.3;
		kIL = 0.00005;
		kIR = 0.00005;
		kDL = 1.5;
		kDR = 1.5;
		integralLimit = 80;
	}

	else if(500<= target <1200)
	{
		kPL = 0.5*1.2;
		kPR = 0.5;
		kIL = 0.00005;
		kIR = 0.00004;
		kDL = 3;//was 1
		kDR = 3;//was 1
		integralLimit = 50;
	}
	else
	{
		kPL = 0.4*1.2;
		kPR = 0.4;
		kIL = 0.00006;
		kIR = 0.00006;
		kDL = 1;
		kDR = 1;
		integralLimit = 50;
	}

	int errorL;
	int preErrorL = target;
	int integralL =0;
	int derivativeL;
	int errorR;
	int preErrorR = target;
	int integralR =0;
	int derivativeR;

	char lowSpeedCountL=0;
	char lowSpeedCountR=0;

	resetChassisEncoders();

	while(((abs(SensorValue[encoderR])) < target) || ((abs(SensorValue[encoderL]))< target))
	{
		errorL = target - abs(SensorValue[encoderL]);
		errorR = target - abs(SensorValue[encoderR]);

		integralL += errorL;
		integralR += errorR;

		if(abs(errorL) < integralLimit)
		{
			integralL = 0;
		}

		if(abs(errorR) < integralLimit)
		{
			integralR = 0;
		}

		derivativeL = errorL - preErrorL;
		derivativeR = errorR - preErrorR;

		preErrorL = errorL;
		preErrorR = errorR;


		indexL = kPL*errorL + kIL*integralL + kDL*derivativeL;
		indexR = kPR*errorR + kIR*integralR + kDR*derivativeR;

		if(errorR < 150 && abs(derivativeR)< 2)
		{
			lowSpeedCountR++;
		}

		if(errorL < 150 && abs(derivativeL)< 2)
		{
			lowSpeedCountL++;
		}

		if(lowSpeedCountL>5 || lowSpeedCountR>5)
			break;

		if(indexR > 125)//prevent overshot the motor
		{
			indexR = 125;
		}
		else
		{
			indexR = indexR;
		}

		if(indexL > 125)
		{
			indexL = 125;
		}
		else
		{
			indexL = indexL;
		}

		if(forward)
		{
				motor[chassisR]=indexR;
				motor[chassisL]=indexL;
		}
		else
		{
				motor[chassisR]=-indexR;
				motor[chassisL]=-indexL;
		}

		if(ifLift && errorR <180)
		{
			armDrive(125);
		}

		if(ifHoldPincher && errorR>100)
		{
			pincherDrive(20);
		}
		wait1Msec(25);
	}
	motor[chassisR]=0;
	motor[chassisL]=0;
}
