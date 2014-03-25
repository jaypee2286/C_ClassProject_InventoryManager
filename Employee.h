// Employee.h

#pragma once
#using <mscorlib.dll>
using namespace System;

namespace OrganizerProjectLibrary {

// for constant int SIZE
#define CHAR_ARRAY_LENGTH_NAME 15
#define SIZE_OF_CHAR sizeof ( Char )
#define SIZE_OF_INT32 sizeof( Int32 )
#define SIZE_OF_DOUBLE sizeof( Double )

public ref class Employee
{
	/*
	Base Class: Employee
	*/
	public: 
		// Filestream size definition for an object of Employee
		static const int SIZE = ( 3 * SIZE_OF_INT32 + 2 * (SIZE_OF_CHAR * CHAR_ARRAY_LENGTH_NAME) );

		// Constructors
		Employee();
		Employee( String^, String^, int, int );
   
		/* PURPOSE: property for the first name of an employee
					compares an inputted string and resizes of necessary
		   RECEIVES: a call to set or get firstName
		   RETURNS: the first name of the employee	*/
		property String^ FirstName 
		{ 
			String^ get() {return gcnew String( firstName );}
			void set(String^ value) 
			{
				int stringSize = value->Length;
				String ^firstNameString = value;
				if (stringSize <= CHAR_ARRAY_LENGTH_NAME )
				{
					firstNameString = String::Concat( value, gcnew String( ' ', 
						CHAR_ARRAY_LENGTH_NAME - stringSize ) );
				}
				else
				{
					firstNameString = value->Substring( 0, CHAR_ARRAY_LENGTH_NAME );
				}

				firstName = firstNameString->ToCharArray();
			}
		}   

		/* PURPOSE: property for the last name of an employee
					compares an inputted string and resizes of necessary
		   RECEIVES: a call to set or get firstName
		   RETURNS: the last name of the employee	*/
		property String^ LastName 
		{ 
			String^ get() {return gcnew String( lastName );}
			void set(String^ value) 
			{
				int stringSize = value->Length;
				String ^lastNameString = value;
				if (stringSize <= CHAR_ARRAY_LENGTH_NAME )
				{
					lastNameString = String::Concat( value, gcnew String( ' ', 
						CHAR_ARRAY_LENGTH_NAME - stringSize ) );
				}
				else
				{
					lastNameString = value->Substring( 0, CHAR_ARRAY_LENGTH_NAME );
				}

				lastName = lastNameString->ToCharArray();
			}
		}

		/* PURPOSE: property for the number of hours worked by an employee
		   RECEIVES: a call to set or get hours worked 
		   RETURNS: the number of hours worked by the employee	*/
		property int HoursWorked
		{
			int get() {return hoursWorked;}
			void set(int value) {hoursWorked = value;}
		}

		/* PURPOSE: property for the ID number of an employee
		   RECEIVES: a call to set or get id 
		   RETURNS: the ID number of the employee	*/
		property int ID
		{ 
			int get() {return id;}
			void set(int value) {id = value;}
		}

		/* PURPOSE: property for the type of employee (0,1: Manager, StorageWorker)
					used for GUI purposes
		   RECEIVES: a call to set or get employee type
		   RETURNS: the type of employee	*/
		property int Type
		{ 
			int get() {return type;}
			void set(int value) {type = value;}
		}

		/*	ToEmpString() Function
			Returns all necessary information for an object of Employee
			Can be changed in Employee_Imp.cpp */
		String^ ToEmpString();

		/*	calcSalary() Function
			Virtual function defined used by base classes */
		virtual double calcSalary();

	private:
		array<wchar_t> ^firstName;	// first name of an employee
		array<wchar_t> ^lastName;	// last name of an employee
		int hoursWorked;			// number of hours worked by employee
		int id;						// id number of an employee
		int type;					// type of employee
};                       
}