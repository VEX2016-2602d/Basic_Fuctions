void autoOpenPincher()
{
	while(SensorValue[pincherDegreeL] > pincherLOpen  || SensorValue[pincherDegreeR] > pincherROpen)
	{
		int openIndexL = pCalc(pincherLOpen, pincherDegreeL, 0.9);
		int openIndexR = pCalc(pincherROpen, pincherDegreeR,0.9);

		if(openIndexL < 20 || openIndexR <20)
		{
			break;
		}

		if(SensorValue[pincherDegreeL] > pincherLOpen)
		{
			motor[pincherL] = -openIndexL;
		}

		if(SensorValue[pincherDegreeR] > pincherROpen)
		{
			motor[pincherR] = -openIndexR;
		}
	}
	pincherDrive(0);
}

void autoClosePincher()
{
	int preReadL = 1000;
	int preReadR = 1000;
	int speedL;
	int speedR;
	int currentReadL;
	int currentReadR;
	char achievedCountL =0;
	char achievedCountR =0;
	pincherDrive(125);
	wait1Msec(200);
	clearTimer(T4);
	while(time1[T4]<650 &&(SensorValue[pincherDegreeL] < pincherLClose || SensorValue[pincherDegreeR] < pincherRClose))
	{
		currentReadL = SensorValue[pincherDegreeL];
		currentReadR = SensorValue[pincherDegreeR];

		speedL = abs(currentReadL - preReadL);
		speedR = abs(currentReadR - preReadR);

		if(SensorValue[pincherDegreeL] < pincherLClose)
		{
			if(speedL>5)
			{
				motor[pincherL] =125;
			}
			else
			{
				achievedCountL++;
				motor[pincherL] = 0;
			}
		}
		else
		{
			motor[pincherL] = 0;
		}

		if(SensorValue[pincherDegreeR] < pincherRClose)
		{
			if(speedR>5)
			{
				motor[pincherR] =125;
			}
			else
			{
				achievedCountR++;
				motor[pincherR] = 0;
			}
		}
		else
		{
			motor[pincherR] = 0;
		}

		if(achievedCountL >2 && achievedCountR >2)
		{
			break;
		}
		preReadL = currentReadL;
		preReadR = currentReadR;
		wait1Msec(25);
	}
	pincherDrive(0);
}

void midPincher()
{
	int indexR;
	int indexL;
	clearTimer(T2);
	while((time1(T2)<700) && (((pincherLMid-5)<SensorValue[pincherDegreeL] <(pincherLMid+5))  || ((pincherRMid-5)<SensorValue[pincherDegreeR] <(pincherRMid+5))))
	{
    if(SensorValue[pincherDegreeR]<(pincherRMid-5))
    {
    	indexR = pCalc(pincherRMid, pincherDegreeR,0.1);
      motor[pincherR] = indexR;
    }
    else if(SensorValue[pincherDegreeR] > (pincherRMid+5))
    {
    	indexR = pCalc(pincherRMid, pincherDegreeR,0.1);
      motor[pincherR] = - indexR;
    }
   	else
   		motor[pincherR] =0;

    if(SensorValue[pincherDegreeL]< (pincherLMid-5))
    {
    	indexL = pCalc(pincherLMid, pincherDegreeL, 0.1);
      motor[pincherL] = indexL;
    }
    else if(SensorValue[pincherDegreeL] > (pincherLMid+5))
    {
    	indexL = pCalc(pincherLMid, pincherDegreeL, 0.1);
      motor[pincherL] = - indexL;
    }
    else
    	motor[pincherL] = 0;
	}
  pincherDrive(0);
}

void releasePincher()//6 each side
{
	clearTimer(T3);
	while(time1[T3]<150)
	{
  pincherDrive(-125);
	}
	pincherDrive(0);
}
