#include "stdafx.h"
#include "Car.h"
void Car::setCnum(CString cnum)
{
	Cnum = cnum;
}
void Car::setPnum(int pnum)
{
	Pnum = pnum;
}
void Car::setItime(CString itime)
{
	Itime = itime;
}
void Car::setOtime(CString otime)
{
	Otime = otime;
}
void Car::setItime1(int itime)
{
	Itime1 = itime;
}
void Car::setOtime1(int otime)
{
	Otime1 = otime;
}
void Car::setCost(double cost)
{
	Cost = cost;
}
void Car::setExit(int exit) 
{ 
	Exit = exit;
}
CString Car::getCnum()
{
	return Cnum;
}
int Car::getPnum()
{
	return Pnum;
}
CString Car::getItime()
{
	return Itime;
}
CString Car::getOtime()
{
	return Otime;
}
int Car::getItime1()
{
	return Itime1;
}
int Car::getOtime1()
{
	return Otime1;
}
double Car::getCost()
{
	return Cost;
}
int Car::getExit()
{
	return Exit;
}