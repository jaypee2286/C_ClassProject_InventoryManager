// ConsoleGames_Imp.cpp -> methods for ConsoleGames
#include "stdafx.h"
#include "ConsoleGames.h"
using namespace System;
using namespace OrganizerProjectLibrary;

// default constructor
ConsoleGames::ConsoleGames():Inventory (0, 0, 0, 0)
{
	Name = "Default Name";
	Platform = "Default Platform";
}

// constructor
ConsoleGames::ConsoleGames( String^ iname, String^ iplatform, double revenue, double sprice, int cstock, int idv )
			: Inventory (revenue, sprice, cstock, idv)
{
	Name = iname;
	Platform = iplatform;
}

/*	ToString() Function
	Returns all necessary information of an object of Console Games
		including profit margin	*/	
String^ ConsoleGames::ToString()
{
	return (L"Information on Product ID #" + ID.ToString() + L"\nName: " + Name + L"\nPlatform: " + Platform + 
		L"\nRetail Price: " + CostOfSale.ToString("C") + 
		L"\nCurrent Stock: " + CurrentStock.ToString() + 
		L"\nNet Revenue: " + calcNetRevenue().ToString("C") +
		L"\nProfit Margin: " + calcProfitMargin().ToString("F") + L"\n");
}

/*	calcProfitMargin() Function
	Returns the profit margin of a console game	*/
double ConsoleGames::calcProfitMargin()
{
	return ( Revenue / ( Revenue - CostOfSale ) );
}

/*	calcNetRevenue() Function
	Returns the net revenue of a console game (income - costs)	*/
double ConsoleGames::calcNetRevenue()
{
	return Revenue - CostOfSale;
}