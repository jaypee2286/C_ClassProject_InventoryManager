// Finances.h

#pragma once
#using <mscorlib.dll>
using namespace System;

namespace OrganizerProjectLibrary {

public ref class Finances
{
	/*
	Base Class: Finances
	*/
	public: 
		// Constructors
		Finances();
		Finances( double );
  
		/* PURPOSE: property for the current current balance
		   RECEIVES: a call to set or get current balance
		   RETURNS: the current balance	*/
		property double Balance
		{
			double get() {return balance;}
			void set(double value) {balance = value;}
		}

		/*	ToFinancesString() Function
			Returns all necessary information for an object of Finances
			Can be changed in Finances_Imp.cpp */
		String^ ToFinancesString();

	private:
		double balance;		// current balance
};          
}
