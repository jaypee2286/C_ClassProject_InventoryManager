// StorageWorker_Imp.cpp -> methods for StorageWorker
#include "stdafx.h"
#include "Employee.h"
#include "StorageWorker.h"
using namespace System;
using namespace OrganizerProjectLibrary;

// default constructor
StorageWorker::StorageWorker()
			: Employee (L"Default", "Storage Worker", 0, 0)
{
	HourlyPay = 10;
}

// constructor
StorageWorker::StorageWorker(String ^Namein, String ^Lastnamein, int hours, int hourly, int idv)
: Employee(Namein, Lastnamein, hours, idv)
{
	HourlyPay = hourly;
}

/*	ToString() Function
	Returns all necessary information for an object of StorageWorker
		including earnings	*/
String ^StorageWorker::ToString()
{
	return (L"Information on Employee ID #" + ID.ToString() + L"\nFirst Name: " + FirstName + L"\nLast Name: "
		+ LastName + L"\nStatus: Storage Worker" + L"\nHours Worked This Week: " + HoursWorked.ToString() 
		+ L"\nHourly Wage: $10.00/hour" + L"\nEarned This Week: " + (calcSalary()).ToString("C"));
}

/*	calcSalary() Function
	Returns (hourly pay * hours worked) */
double StorageWorker::calcSalary()
{
	return HoursWorked * HourlyPay;
}