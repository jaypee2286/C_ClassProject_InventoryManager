// StorageWorker.h

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

public ref class StorageWorker : public Employee
{
	/*
	Class: StorageWorker
	Derived from Base Class: Employee
	*/

	public: 
		// Filestream size definition for an object of Storage Worker
		static const int SIZE = ( 3 * SIZE_OF_INT32 + 2 * (SIZE_OF_CHAR * CHAR_ARRAY_LENGTH_NAME) );

		// Constructors
		StorageWorker();
		StorageWorker( String^, String^, int, int, int );
   
		/* PURPOSE: property for the hourly pay of the storage worker
		   RECEIVES: a call to set or get int hourlyPay
		   RETURNS: hourlyPay	*/
		property int HourlyPay
		{ 
			int get() {return hourlyPay;}
			void set(int value) {hourlyPay = value;}
		}

		/*	ToString() Function
			Returns all necessary information for an object of StorageWorker	*/
		virtual String ^ToString() override;

		/*	calcSalary() Function
			Returns (hourly pay * hours worked) */
		virtual double calcSalary() override;

	private:
		static int hourlyPay = 10;	// hourly pay of a storage worker (in dollars)
};                       
}