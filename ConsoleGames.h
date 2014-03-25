// ConsoleGames.h

#pragma once
#using <mscorlib.dll>
#include "Inventory.h"
using namespace System;

namespace OrganizerProjectLibrary {

// for constant int SIZE
#define CHAR_ARRAY_LENGTH 30
#define SIZE_OF_CHAR sizeof ( Char )
#define SIZE_OF_INT32 sizeof( Int32 )
#define SIZE_OF_DOUBLE sizeof( Double )

public ref class ConsoleGames : public Inventory
{
	/*
	Class: ConsoleGames
	Derived from Base Class: Inventory
	*/
	public: 
		// Filestream size definition for an object of ConsoleGames
		static const int SIZE = ( 2 * SIZE_OF_INT32 + 2 * (SIZE_OF_CHAR * CHAR_ARRAY_LENGTH)
			+ 2 * SIZE_OF_DOUBLE );

		// Constructors
		ConsoleGames();
		ConsoleGames( String^, String^, double, double, int, int );

		/* PURPOSE: property for the name of a console game
					compares an inputted string and resizes of necessary
		   RECEIVES: a call to set or get a name
		   RETURNS: the name of the console game	*/
		property String^ Name 
		{ 
			String^ get() {return gcnew String( name );}
			void set(String^ value) 
			{
				int stringSize = value->Length;
				String ^nameString = value;
				if (stringSize <= CHAR_ARRAY_LENGTH )
				{
					nameString = String::Concat( value, gcnew String( ' ', 
						CHAR_ARRAY_LENGTH - stringSize ) );
				}
				else
				{
					nameString = value->Substring( 0, CHAR_ARRAY_LENGTH );
				}

				name = nameString->ToCharArray();
			}
		}   

		/* PURPOSE: property for the platform of a console game
					compares an inputted string and resizes of necessary
		   RECEIVES: a call to set or get a platform
		   RETURNS: the platform of a console game	*/
		property String^ Platform 
		{ 
			String^ get() {return gcnew String( platform );}
			void set(String^ value) 
			{
				int stringSize = value->Length;
				String ^platformString = value;
				if (stringSize <= CHAR_ARRAY_LENGTH )
				{
					platformString = String::Concat( value, gcnew String( ' ', 
						CHAR_ARRAY_LENGTH - stringSize ) );
				}
				else
				{
					platformString = value->Substring( 0, CHAR_ARRAY_LENGTH );
				}

				platform = platformString->ToCharArray();
			}
		}

		/*	ToString() Function
			Returns all necessary information for an object of ConsoleGames	*/
		virtual String ^ToString() override;

		/*	calcProfitMargin() Function
			Returns the profit margin of a console game	*/
		virtual double calcProfitMargin() override;		
		
		/*	calcNetRevenue() Function
			Returns the net revenue of a console game (income - costs)	*/
		virtual double calcNetRevenue() override;

	private:
		array<wchar_t> ^name;		// product name
		array<wchar_t> ^platform;	// product platform
};                       
}