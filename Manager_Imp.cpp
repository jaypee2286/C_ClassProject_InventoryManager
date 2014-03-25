// Manager_Imp.cpp -> methods for Manager
#include "stdafx.h"
#include "Employee.h"
#include "Manager.h"
using namespace System;
using namespace OrganizerProjectLibrary;

// default constructor
Manager::Manager()
			: Employee (L"Default", "Manager", 0, 0)
{
	HourlyPay = 20;
}

// constructor
Manager::Manager( String ^Namein, String ^Lastnamein, int hours, int hourly, int idv ) 
			: Employee (Namein, Lastnamein, hours, idv)
{
	HourlyPay = hourly;
}

/*	ToString() Function
	Returns all necessary information of an object of Manager
		including earnings	*/	
String ^Manager::ToString()
{
	return (L"Information on Employee ID #" + ID.ToString() + L"\nFirst Name: " + FirstName + L"\nLast Name: "
		+ LastName + L"\nStatus: Manager" + L"\nHours Worked This Week: " + HoursWorked.ToString() 
		+ L"\nHourly Wage: $20.00/hour" + L"\nEarned This Week: " + (calcSalary()).ToString("C"));
}

/*	calcSalary() Function
	Returns (hourly pay * hours worked) */
double Manager::calcSalary()
{
	return HoursWorked * HourlyPay;
}