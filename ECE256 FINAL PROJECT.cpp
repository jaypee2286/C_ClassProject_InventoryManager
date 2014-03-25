// PROJECT GUI TEMPLATE.cpp : main project file.

#include "stdafx.h"
#include "MainProject.h"
#include "ChildUI.h"

using namespace PROJECTGUITEMPLATE;
using namespace OrganizerProjectLibrary;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew MainProject());
	return 0;
}
