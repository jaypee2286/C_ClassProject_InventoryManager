// Finances_Imp.cpp -> methods for Finances
#include "stdafx.h"
#include "Finances.h"
#include "Gains.h"
#include "Expenses.h"
using namespace System;
using namespace OrganizerProjectLibrary;


// Default Constructor
Finances::Finances()
{
	Balance = 0;
}

// Constructor
Finances::Finances( double balanceValue )
{
	Balance = balanceValue;
}

/*	ToFinancesString() Function
	Returns all necessary information for an object of Finances
	Should be changed and used accordingly */
String^ Finances::ToFinancesString()
{
	return (L"Name: ");
}