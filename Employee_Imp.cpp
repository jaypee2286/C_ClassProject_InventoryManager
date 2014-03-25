// Employee_Imp.cpp -> methods for Employee
#include "stdafx.h"
#include "Employee.h"
using namespace System;
using namespace OrganizerProjectLibrary;

// default constructor
Employee::Employee()
{
	FirstName = L"Default John";
	LastName = L"Default Doe";
	HoursWorked = 0;
	ID = 0;
}

// constructor
Employee::Employee( String^ Namein, String^ Lastnamein, int hours, int idv )
{
	FirstName = Namein;
	LastName = Lastnamein;
	HoursWorked = hours;
	ID = idv;
}

/*	ToEmpString() Function
	Returns all necessary information for an object of Employee
	Should be changed and used accordingly */
String^ Employee::ToEmpString()
{
	return (L"Information on Employee ID #" + ID.ToString() + L"\nFirst Name: " 
		+ FirstName + L"\nLast Name: " + LastName);
}

/*	calcSalary() Function
	Virtual function defined and used by derived classes */
double Employee::calcSalary()
{
	return 0;
}