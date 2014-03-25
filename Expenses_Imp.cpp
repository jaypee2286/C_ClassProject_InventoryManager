// Expenses_Imp.cpp -> methods for Expenses
#include "stdafx.h"
#include "Finances.h"
#include "Expenses.h"
using namespace System;
using namespace OrganizerProjectLibrary;

// default constructor
Expenses::Expenses()
{
	StockExpense = 0;
	EmployeeExpense = 0;
	OtherExpense = 0;
}

// constructor
Expenses::Expenses( double stexpenseValue, double eexpenseValue, double oexpenseValue )
{
	StockExpense = stexpenseValue;
	EmployeeExpense = eexpenseValue;
	OtherExpense = oexpenseValue;
}

/*	ToString() Function
	Returns all necessary information for an object of Expenses
		including total expense	*/
String^ Expenses::ToString()
{
	return (L"Stock Expenses: " + StockExpense.ToString("C") + L"\nEmployee Expenses: " +
		EmployeeExpense.ToString("C") + L"\nOther Expenses: " + OtherExpense.ToString("C")
		+ L"\nTotal Expenses: " +TotalExpense().ToString("C") + L"\n------------\n");
}

/*	TotalExpense() Function
	Returns the total expense (stockExpense + employeeExpense + otherExpense) */
double Expenses::TotalExpense()
{
	return StockExpense + EmployeeExpense + OtherExpense;
}