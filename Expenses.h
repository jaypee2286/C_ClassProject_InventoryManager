// Expenses.h

#pragma once
#include "Finances.h"
#using <mscorlib.dll>
using namespace System;

namespace OrganizerProjectLibrary {

// for constant int SIZE
#define SIZE_OF_DOUBLE sizeof( Double )

public ref class Expenses : public Finances
{
	/*
	Class: Expenses
	Derived from Base Class: Finances
	*/
	public: 
		// Filestream size definition for an object of Expenses
		static const int SIZE = ( 3 * SIZE_OF_DOUBLE );

		// Constructors
		Expenses();
		Expenses( double, double, double );
  
		/* PURPOSE: property for the total product expense
		   RECEIVES: a call to set or get the total product expense
		   RETURNS: stockExpense	*/
		property double StockExpense
		{
			double get() {return stockExpense;}
			void set(double value) {stockExpense = value;}
		}
		
		/* PURPOSE: property for the total employee expense
		   RECEIVES: a call to set or get the total employee expense
		   RETURNS: employeeExpense	*/
		property double EmployeeExpense
		{
			double get() {return employeeExpense;}
			void set(double value) {employeeExpense = value;}
		}
		
		/* PURPOSE: property for the total other expense
		   RECEIVES: a call to set or get the total other expense
		   RETURNS: otherExpense	*/
		property double OtherExpense
		{
			double get() {return otherExpense;}
			void set(double value) {otherExpense = value;}
		}

		/*	ToString() Function
			Returns all necessary information for an object of Expenses	*/
		virtual String^ ToString()override;

		/*	TotalExpense() Function
			Returns the total expense (stockExpense + employeeExpense + otherExpense) */
		double TotalExpense();

	private:
		double stockExpense;		// total product expenses
		double employeeExpense;		// total employee expenses
		double otherExpense;		// total other expenses
};                       
}