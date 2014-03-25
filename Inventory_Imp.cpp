// Inventory_Imp.cpp -> methods for Inventory
#include "stdafx.h"
#include "Inventory.h"
using namespace System;
using namespace OrganizerProjectLibrary;

// default constructor
Inventory::Inventory()
{
	Revenue = 0;
	CostOfSale = 0;
	CurrentStock = 0;
	ID = 0;
}

// constructor
Inventory::Inventory( double revenue, double sprice, int cstock, int idv )
{
	Revenue = revenue;
	CostOfSale = sprice;
	CurrentStock = cstock;
	ID = idv;
}

/*	ToInvString() Function
	Returns all necessary information for an object of Inventory
	Should be changed and used accordingly */
String^ Inventory::ToInvString()
{
	return (L"Name: ");
}

/*	calcProfitMargin() Function
	Virtual function defined used by base classes */
double Inventory::calcProfitMargin()
{
	return 0;
}
/*	calcNetRevenue() Function
	Virtual function defined used by base classes */
double Inventory::calcNetRevenue()
{
	return 0;
}