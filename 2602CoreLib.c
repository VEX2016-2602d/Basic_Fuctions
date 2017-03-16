#ifndef _2602CORELIB_;
#define _2602CORELIB_;

typedef struct
{
  tMotor motorPort;
  tSensors sensorPort;
  float kP;
  float kI;
  float kD;
  int integralLimit;
}chassisData;

typedef struct
{
  tMotor motorPort;
  tSensors sensorPort;
  int open;
  int mid;
  int close;
}clawData;

typedef struct
{
  tMotor motorPortR;
  tMotor motorPortL;
  tSensors sensorPort;
  int full;
  int holdNull;
  int holdStar;
  int hold3Stars;
  int holdCube;
}armData;

static armData arm;
static clawData pincherR;
static clawData pincherL;
static chassisData chassisR;
static chassisData chassisL;

void setArm(tMotor motorR, tMotor motorL, tSensors port,int full,int none,int star,int stars,int cube)
{
  arm.motorPortR = motorR;
  arm.motorPortL = motorL;
  arm.sensorPort=port;
  arm.full=full;
  arm.holdNull=none;
  arm.holdStar=star;
  arm.hold3Stars=stars;
  arm.holdCube=cube;
}

void setChassis(char side,tMotor motorport, tSensors sensorport, float kp, float ki, float kd, float integrallimit)
{
  if(side=="R")
  {
    chassisR.motorPort=motorport;
    chassisR.sensorPort=sensorport;
    chassisR.kP=kp;
    chassisR.kI=ki;
    chassisR.kD=kd;
    chassisR.integralLimit=integrallimit;
  }
  else if(side=="L")
  {
    chassisL.motorPort=motorport;
    chassisL.sensorPort=sensorport;
    chassisL.kP=kp;
    chassisL.kI=ki;
    chassisL.kD=kd;
    chassisL.integralLimit=integrallimit;
  }
  else {}
}

void setPincher(char side,tMotor motorport, tSensors sensorport,int openMV,int midMV,int closeMV)
{
  if(side=="R")
  {
    pincherR.motorPort=motorport;
    pincherR.sensorPort=sensorport;
    pincherR.open=openMV;
    pincherR.mid=midmV;
    pincherR.clsoe=closeMV;
  }
  else if(side=="L")
  {
    pincherL.motorPort=motorport;
    pincherL.sensorPort=sensorport;
    pincherL.open=openMV;
    pincherL.mid=midmV;
    pincherL.clsoe=closeMV;
  }
  else {}
}



#endif
