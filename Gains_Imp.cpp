// Gains_Imp.cpp -> methods for Gains
#include "stdafx.h"
#include "Finances.h"
#include "Gains.h"
using namespace System;
using namespace OrganizerProjectLibrary;

// default constructor
Gains::Gains()
{
	StoreGains = 0;
	OtherGains = 0;
}

// constructor
Gains::Gains( double sgainsValue, double ogainsValue ) 
{
	StoreGains = sgainsValue;
	OtherGains = ogainsValue;
}

/*	ToString() Function
	Returns all necessary information for an object of Gains
		including total income	*/
String^ Gains::ToString()
{
	return (L"Store Gains: " + StoreGains.ToString("C") + L"\nOther Gains: " +
		OtherGains.ToString("C") + L"\nTotal Gains: " + TotalGains().ToString("C") + L"\n------------");
}

/*	TotalGains() Function
	Returns the total income (storeGains + otherGains) */
double Gains::TotalGains()
{
	return StoreGains + OtherGains;
}