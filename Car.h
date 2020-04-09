#pragma once
#include "stdafx.h"
class Car
{
	private:
		CString Cnum;
		int Pnum;
		CString Itime;
		CString Otime;
		int Itime1;
		int Otime1;
		double Cost;
		int Exit;
	public:
		void setCnum(CString cnum);
		void setPnum(int pnum);
		void setItime(CString itime);
		void setOtime(CString otime);
		void setItime1(int itime);
		void setOtime1(int otime);
		void setCost(double cost);
		void setExit(int Exit);
		CString getCnum();
		int getPnum();
		CString getItime();
		CString getOtime();
		int getItime1();
		int getOtime1();
		double getCost();
		int getExit();
};

