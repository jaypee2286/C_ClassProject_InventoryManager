// Gains.h

#pragma once
#using <mscorlib.dll>
using namespace System;

namespace OrganizerProjectLibrary {

// for constant int SIZE
#define SIZE_OF_DOUBLE sizeof( Double )

public ref class Gains : public Finances
{
	/*
	Class: Gains
	Derived from Base Class: Finances
	*/
	public: 
		// Filestream size definition for an object of Gains
		static const int SIZE = ( 2 * SIZE_OF_DOUBLE );

		// Constructors
		Gains();
		Gains( double, double );
  
		/* PURPOSE: property for the total product income
		   RECEIVES: a call to set or get the total product income
		   RETURNS: storeGains	*/
		property double StoreGains
		{
			double get() {return storeGains;}
			void set(double value) {storeGains = value;}
		}
		
		/* PURPOSE: property for other income
		   RECEIVES: a call to set or get other income
		   RETURNS: otherGains	*/
		property double OtherGains
		{
			double get() {return otherGains;}
			void set(double value) {otherGains = value;}
		}

		/*	ToString() Function
			Returns all necessary information for an object of Gains	*/
		virtual String^ ToString() override;

		/*	TotalGains() Function
			Returns the total income (storeGains + otherGains) */
		double TotalGains();

	private:
		double storeGains;	// product income
		double otherGains;	// other income
};                       
}