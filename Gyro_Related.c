void gyroSetup()
{
  SensorType[in8] = sensorNone;
  wait1Msec(1000);
  SensorType[in8] = sensorGyro;
  wait1Msec(2000);
  SensorScale[in8] = 140;//#1 Gyro
  /*SensorType[in5] = sensorNone;
  wait1Msec(1000);
  SensorType[in5] = sensorGyro;
  wait1Msec(2000);
  SensorScale[in5] = 131;*/
}

task gyroFilter()
{
  int     gyro_Read;
  int     gyro_Error = 0;
  int     lastDriftGyro = gyroAngle;

  int     angle;
  long    nSysTimeOffset;

  nSysTimeOffset = nSysTime;

  while(true)
  {
  	gyro_Read=SensorValue[in8];
    //if the angle speed smaller than 20/s than consider as a drift
    if( (nSysTime - nSysTimeOffset) > 250 )
      {
        if( abs( gyro_Read - lastDriftGyro ) < 3
        	)
        {
          gyro_Error += (lastDriftGyro - gyro_Read);
        }
        lastDriftGyro = gyro_Read;
        nSysTimeOffset = nSysTime;
      }
      angle = (gyro_Read + gyro_Error)/10;

      //fit the runover
      if(angle< -360)
      {
        angle += 360;
      }
      else if(angle >360)
      {
        angle -= 360;
      }
      else
      {
        angle = angle;
  		}
      gyroAngle = angle; //store the result to global variable;
      wait1Msec(15);
  }
}

void gyroTurn(int nDegree,int timeLimit)
{
	int error;
  float index;
	int preError = gyroAngle - nDegree;
	int derivative;
  clearTimer(T2);
  while(time1[T2]<timeLimit)
  {
    error = gyroAngle - nDegree;
    derivative = error-preError;
    preError = error;
    index = 2*error+5.8*derivative;

  	if(index > 120)//prevent overshot the motor
		{
		index = 120;
		}
		else if(index<-120)
		{
			index = -120;
		}
		else
		{
		index = index;
		}
    motor[chassisL] = index;
    motor[chassisR] = -index;
    wait1Msec(25);
  }
  motor[chassisL] = 0;
  motor[chassisR] = 0;
}

void gyroAdjustment(int nDegree)//counterclockwise is postive
{
  int error;
  float index;
  int intergrate=0;
  clearTimer(T1);
  while(time1[T1]<500)
  {
    error = abs(gyroAngle - nDegree);
    intergrate +=error;
    index = 16*error + 0.1*intergrate;
    if(index>30)
    	index = 30;
   	else
   		index = index;
   if(gyroAngle>nDegree)
   {
    motor[chassisL] = index;
    motor[chassisR] = -index;
 		}
 		else if(gyroAngle<nDegree)
 		{
 		motor[chassisL] = -index;
    motor[chassisR] = index;
 		}
 		else
 		{
 		motor[chassisL] = 0;
    motor[chassisR] = 0;
  	}
    wait1Msec(25);
  }
  motor[chassisL] = 0;
  motor[chassisR] = 0;
}
