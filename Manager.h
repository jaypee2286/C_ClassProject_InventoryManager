// Manager.h

#pragma once
#using <mscorlib.dll>
#include "Employee.h"
using namespace System;

namespace OrganizerProjectLibrary {

// for constant int SIZE
#define CHAR_ARRAY_LENGTH_NAME 15
#define SIZE_OF_CHAR sizeof ( Char )
#define SIZE_OF_INT32 sizeof( Int32 )
#define SIZE_OF_DOUBLE sizeof( Double )

public ref class Manager : public Employee
{
	/*
	Class: Manager
	Derived from Base Class: Employee
	*/
	public: 
		// Filestream size definition for an object of Manager
		static const int SIZE = ( 3 * SIZE_OF_INT32 + 2 * (SIZE_OF_CHAR * CHAR_ARRAY_LENGTH_NAME) );

		// Constructors
		Manager();
		Manager( String^, String^, int, int, int );
   
		/* PURPOSE: property for the hourly pay of the manager
		   RECEIVES: a call to set or get int hourlyPay
		   RETURNS: hourlyPay	*/
		property int HourlyPay 
		{ 
			int get() {return hourlyPay;}
			void set(int value) {hourlyPay = value;}
		}

		/*	ToString() Function
			Returns all necessary information for an object of Manager	*/
		virtual String ^ToString() override;

		/*	calcSalary() Function
			Returns (hourly pay * hours worked) */
		virtual double calcSalary() override;

	private:
		static int hourlyPay = 20;	// hourly pay of a manager (in dollars)
};                       
}