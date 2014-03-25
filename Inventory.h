// Inventory.h

#pragma once
#using <mscorlib.dll>
using namespace System;

namespace OrganizerProjectLibrary {

public ref class Inventory
{
	/*
	Base Class: Inventory
	*/
	public: 
		// Constructors
		Inventory();
		Inventory( double, double, int, int );
   
		/* PURPOSE: property for the total income of an inventory item
		   RECEIVES: a call to set or get revenue
		   RETURNS: the revenue of the inventory item	*/
		property double Revenue
		{ 
			double get() {return revenue;}
			void set(double value) {revenue = value;}
		}

		/* PURPOSE: property for the cost of sale of an inventory item
		   RECEIVES: a call to set or get the cost of sale
		   RETURNS: the cost of sale of the inventory item	*/
		property double CostOfSale
		{ 
			double get() {return costOfSale;}
			void set(double value) {costOfSale = value;}
		}

		/* PURPOSE: property for the current stock of an inventory item
		   RECEIVES: a call to set or get the current stock
		   RETURNS: the current stock of the inventory item	*/
		property int CurrentStock
		{ 
			int get() {return currentStock;}
			void set(int value) {currentStock = value;}
		}

		/* PURPOSE: property for the product ID of an inventory item
		   RECEIVES: a call to set or get the product ID
		   RETURNS: the product ID of the inventory item	*/
		property int ID
		{ 
			int get() {return id;}
			void set(int value) {id = value;}
		}

		/*	ToInvString() Function
			Returns all necessary information for an object of Employee
			Can be changed in Inventory_Imp.cpp */
		String^ ToInvString();


		/*	calcProfitMargin() Function
			Virtual function defined used by base classes */
		virtual double calcProfitMargin();

		/*	calcNetRevenue() Function
			Virtual function defined used by base classes */
		virtual double calcNetRevenue();


	private:
		double revenue;		// total income of a product
		double costOfSale;	// cost of sale of a product
		int currentStock;	// current stock of a product
		int id;				// product id
};                     
}
