#pragma once
#include "stdafx.h"

#define MAP_BOUNDS_LEFT -20037508.3427892
#define MAP_BOUNDS_BOTTOM -20037508.3427892
#define MAP_BOUNDS_RIGHT 20037508.3427892
#define MAP_BOUNDS_TOP 20037508.3427892
#define PI	3.1415926
#define PNGSIZE 256

typedef struct _VIEWBOUNDS{
	double dleft;
	double dtop;
	double dright;
	double dbottom;
}VIEWBOUNDS, *pVIEWBOUNDS;


typedef struct _GPSPOSITION{
	double dLatitude;
	double dLongitude;
	double dHeight;
	CString strLongitude;
	CString strLatitude;
	CString strHeight;

	int nflagLati; // 1 or -1 
	UINT nLatiHour;
	UINT nLatiMin;
	double dLatiSec; //Ãë

	int nflagLongi;
	UINT nLongiHour;
	UINT nLongiMin;
	double dLongiSec; // Ãë

	_GPSPOSITION()
	{
		dLatitude = 0.f;
		dLongitude = 0.f;
		dHeight = 0.f;

		nflagLati = 1;
		nLatiHour = 0;
		nLatiMin = 0;
		dLatiSec = 0.f;

		nflagLongi = 1;
		nLongiHour = 0;
		nLongiMin = 0;
		dLongiSec = 0.f;
	}

	_GPSPOSITION(double dLa, double dLong, double dHt){
		dLatitude = dLa;
		dLongitude = dLong;
		dHeight = dHt;
		CalculatePos();
	}

	void CalculatePos()
	{
		strLatitude.Format(_T("%.5f"), dLatitude);
		strLongitude.Format(_T("%.5f"), dLongitude);
		strHeight.Format(_T("%.2f"), dHeight);

		if (dLatitude > 0.f)
		{
			nflagLati = 1;
			nLatiHour = (int)(dLatitude);
			nLatiMin = (int)((dLatitude - nLatiHour)*60);
			dLatiSec = ((dLatitude - nLatiHour)*60 - nLatiMin) * 60;
		}
		else if (dLatitude < 0.f)
		{
			nflagLati = -1;
			nLatiHour = (int)(-dLatitude);
			nLatiMin = (int)((-dLatitude - nLatiHour)*60);
			dLatiSec = ((-dLatitude - nLatiHour)*60 - nLatiMin) * 60;
		}
		else
		{
			nflagLati = 1;
			nLatiHour = 0;
			nLatiMin = 0;
			dLatiSec = 0.f;
		}

		if (dLongitude > 0.f)
		{
			nflagLongi = 1;
			nLongiHour = (int)(dLongitude);
			nLongiMin = (int)((dLongitude - nLongiHour)*60);
			dLongiSec = ((dLongitude - nLongiHour)*60 - nLongiMin) * 60;
		}
		else if (dLongitude < 0.f)
		{
			nflagLongi = -1;
			nLongiHour = (int)(-dLongitude);
			nLongiMin = (int)((-dLongitude - nLongiHour)*60);
			dLongiSec = ((-dLongitude - nLongiHour)*60 - nLongiMin) * 60;
		}
		else
		{
			nflagLongi = 1;
			nLongiHour = 0;
			nLongiMin = 0;
			dLongiSec = 0.f;
		}
	}
}GPSPOSITION, *pGPSPOSITION;

