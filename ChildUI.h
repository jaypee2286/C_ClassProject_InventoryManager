// ChildUI.h
// Child form used for files

#pragma once
#include "NEWHEADER.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace OrganizerProjectLibrary;

// DEFINITIONS FOR ARRAY SIZES
#define NUM_OF_YEARS 3
#define NUM_OF_MONTHS ( 12 * NUM_OF_YEARS )
#define NUM_OF_PRODUCTS 11
#define NUM_OF_STORAGEWORKERS 4
#define NUM_OF_MANAGERS 2
#define NUM_OF_EMPLOYEES 11
#define NUM_OF_GAINS (NUM_OF_MONTHS)
#define NUM_OF_EXPENSES (NUM_OF_MONTHS)
#define INV_ARRAY_SIZE (NUM_OF_PRODUCTS)
#define EMP_ARRAY_SIZE (NUM_OF_EMPLOYEES)
#define GAINS_ARRAY_SIZE (NUM_OF_MONTHS * 2)
#define EXPENSES_ARRAY_SIZE (NUM_OF_MONTHS * 3)
#define FINANCES_ARRAY_SIZE (NUM_OF_MONTHS * (GAINS_ARRAY_SIZE + EXPENSES_ARRAY_SIZE))

namespace PROJECTGUITEMPLATE {

	public ref class ChildUI : public System::Windows::Forms::Form
	{
	public:
		//NEW ITEM CONSTRUCTOR
		ChildUI( String ^fileName )
		{
			Text = fileName;

			//ALLOCATE INVENTORY ARRAY
			for (int i = 0; i < NUM_OF_PRODUCTS; i++)
				{	
					Inv[i] = gcnew ConsoleGames();			
				}

			//ALLOCATE EMPLOYEES ARRAY
			for ( int j = 0; j < NUM_OF_EMPLOYEES; j++)
			{
					Emp[j] = gcnew Employee();
			}

			//ALLOCATE FINANCE ITEMS
			for ( int k = 0; k < 12; k++ )
			{
				for ( int l = 0; l < NUM_OF_YEARS; l++ )
				{
					Gain[k, l] = gcnew Gains();
					Expense[k, l] = gcnew Expenses();
				}
			}

			InitializeComponent();
		}

		//OPEN ITEM CONSTRUCTOR
		ChildUI ( String ^fileName, int openswitch )
		{
			try
			{
				//OPEN FILESTREAMS
				fileInput = gcnew FileStream( fileName, FileMode::Open, FileAccess::Read );
				binaryInput = gcnew BinaryReader( fileInput );

				for (int i = 0; i < NUM_OF_PRODUCTS; i++)
				{					
					fileInput->Seek( i * ConsoleGames::SIZE, SeekOrigin::Begin );

					Inv[i] = gcnew ConsoleGames();
					Inv[i]->ID = binaryInput->ReadInt32();
					Inv[i]->Name = binaryInput->ReadString();
					Inv[i]->Platform = binaryInput->ReadString();
					Inv[i]->Revenue = binaryInput->ReadDouble();
					Inv[i]->CostOfSale = binaryInput->ReadDouble();
					Inv[i]->CurrentStock = binaryInput->ReadInt32();
				}

				//READ EMPLOYEE ITEMS
				for ( int j = 0; j < NUM_OF_EMPLOYEES; j++)
				{
					fileInput->Seek((NUM_OF_PRODUCTS) * ConsoleGames::SIZE + j * Employee::SIZE,
						SeekOrigin::Begin);

					Emp[j] = gcnew StorageWorker();
					Emp[j]->ID = binaryInput->ReadInt32();
					Emp[j]->FirstName = binaryInput->ReadString();
					Emp[j]->LastName = binaryInput->ReadString();
					Emp[j]->HoursWorked = binaryInput->ReadInt32();
				}

				//READ FINANCE ITEMS
				for ( int k = 0; k < 12; k++ )
				{
					fileInput->Seek((NUM_OF_PRODUCTS) * ConsoleGames::SIZE + (NUM_OF_EMPLOYEES) * Employee::SIZE
						+ k * (Gains::SIZE + Expenses::SIZE), SeekOrigin::Begin);

					for ( int l = 0; l < NUM_OF_YEARS; l++ )
					{
						Gain[k, l] = gcnew Gains();
						Expense[k, l] = gcnew Expenses();							
						Gain[k, l]->StoreGains = binaryInput->ReadDouble();
						Gain[k, l]->OtherGains = binaryInput->ReadDouble();
						Expense[k, l]->StockExpense = binaryInput->ReadDouble();
						Expense[k, l]->EmployeeExpense = binaryInput->ReadDouble();
						Expense[k, l]->OtherExpense = binaryInput->ReadDouble();
					}
				}
				
				Text = fileName;
				InitializeComponent();
			}

			//RETURNS ERROR IF FILE CANNOT BE READ CORRECTLY
			catch (IOException ^ )
			{
				MessageBox::Show( L"Invalid File", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );
			}
			
			// CLOSE FILESTREAMS
			fileInput->Close();
			binaryInput->Close();
		}

	protected:
		~ChildUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  TabControl;
	protected: 
	private: System::Windows::Forms::TabPage^  InventoryPage;
	private: System::Windows::Forms::TabPage^  EmployeesPage;
	private: System::Windows::Forms::TabPage^  FinancesPage;


	private: System::Windows::Forms::GroupBox^  InvGroupBox1;
	private: System::Windows::Forms::Label^  InvIdLabel;
	private: System::Windows::Forms::Label^  InvNameLabel;
	private: System::Windows::Forms::Label^  InvPlatformLabel;
	private: System::Windows::Forms::Label^  InvRevenueLabel;
	private: System::Windows::Forms::Label^  InvCostOfSaleLabel;
	private: System::Windows::Forms::Label^  CurrentStockLabel;
	private: System::Windows::Forms::Label^  InvProductIDLabel;
	private: System::Windows::Forms::TextBox^  InvIdBox;
	private: System::Windows::Forms::TextBox^  InvNameBox;
	private: System::Windows::Forms::TextBox^  InvPlatformBox;
	private: System::Windows::Forms::TextBox^  InvRevenueBox;
	private: System::Windows::Forms::TextBox^  InvCostOfSaleBox;
	private: System::Windows::Forms::TextBox^  InvCstockBox;
	private: System::Windows::Forms::ToolStrip^  InvToolStrip1;
	private: System::Windows::Forms::ToolStrip^  InvToolStrip2;
	private: System::Windows::Forms::ToolStripButton^  InvAddButton;
	private: System::Windows::Forms::ToolStripButton^  InvClearFormButton;
	private: System::Windows::Forms::ToolStripButton^  InvViewEntryButton;
	private: System::Windows::Forms::ToolStripButton^  InvClearEntryButton;
	private: System::Windows::Forms::ListBox^  InvListBox;


	private: System::Windows::Forms::GroupBox^  EmpGroupBox1;
	private: System::Windows::Forms::Label^  EmpLabel1;
	private: System::Windows::Forms::Label^  EmpIdLabel;
	private: System::Windows::Forms::Label^  EmpFirstNameLabel;
	private: System::Windows::Forms::Label^  EmpLastNameLabel;
	private: System::Windows::Forms::Label^  EmpHoursWorkedLabel;
	private: System::Windows::Forms::TextBox^  EmpIdBox;
	private: System::Windows::Forms::TextBox^  EmpFirstNameBox;
	private: System::Windows::Forms::TextBox^  EmpLastNameBox;
	private: System::Windows::Forms::TextBox^  EmpHoursWorkedBox;
	private: System::Windows::Forms::ToolStrip^  EmpToolStrip1;
	private: System::Windows::Forms::ToolStrip^  EmpToolStrip2;
	private: System::Windows::Forms::ToolStripButton^  EmpAddButton;
	private: System::Windows::Forms::ToolStripButton^  EmpClearFormButton;
	private: System::Windows::Forms::ToolStripButton^  EmpClearEntryButton;
	private: System::Windows::Forms::ToolStripButton^  EmpViewEntryButton;
	private: System::Windows::Forms::ListBox^  EmpListBox;


	private: System::Windows::Forms::GroupBox^  FinancesGroupBox1;
	private: System::Windows::Forms::Label^  FinOtherGainsLabel;
	private: System::Windows::Forms::Label^  FinStoreGainsLabel;
	private: System::Windows::Forms::Label^  FinStockExpensesLabel;
	private: System::Windows::Forms::Label^  FinEmployeeExpensesLabel;
	private: System::Windows::Forms::Label^  FinOtherExpensesLabel;
	private: System::Windows::Forms::Label^  EmpStatusLabel;
	private: System::Windows::Forms::Label^  FinancesYearLabel;
	private: System::Windows::Forms::Label^  FinancesMonthLabel;
	private: System::Windows::Forms::TextBox^  FinStoreGainsBox;
	private: System::Windows::Forms::TextBox^  FinOtherGainsBox;
	private: System::Windows::Forms::TextBox^  FinStockExpensesBox;
	private: System::Windows::Forms::TextBox^  FinEmployeeExpensesBox;
	private: System::Windows::Forms::TextBox^  FinOtherExpensesBox;
	private: System::Windows::Forms::ComboBox^  EmpStatusBox;
	private: System::Windows::Forms::ComboBox^  FinancesYearBox;
	private: System::Windows::Forms::ComboBox^  FinancesMonthBox;

	private: System::Windows::Forms::ToolStrip^  FinToolStrip1;
	private: System::Windows::Forms::ToolStrip^  FinToolStrip2;
	private: System::Windows::Forms::ToolStripButton^  FinancesAddButton;
	private: System::Windows::Forms::ToolStripButton^  FinancesClearButton;
	private: System::Windows::Forms::ToolStripButton^  FinancesClearEntryButton;
	private: System::Windows::Forms::ToolStripButton^  FinancesViewEntryButton;
	private: System::Windows::Forms::ToolStripButton^  FinancesCalculationsButton;


	private: System::Windows::Forms::GroupBox^  SystemLogGroupBox;
	private: System::Windows::Forms::RichTextBox^  SystemLogLabel;

//////////////////////////////////////////////////////////////////////////
///// DECLARING ALL GLOBAL VARIABLES /////////////////////////////////////
///// INCLUDING OBJECT ARRAYS AND FILESTREAMS ////////////////////////////
//////////////////////////////////////////////////////////////////////////
	//create Inv array for Inventory
	public: static array<ConsoleGames^>^ Inv = gcnew array<ConsoleGames^>(NUM_OF_PRODUCTS);	
	//create Emp array for Employees
	public: static array<Employee^>^ Emp = gcnew array<Employee^>(NUM_OF_EMPLOYEES);
	//create EmpM array for Managers
	public: static array<Manager^>^ EmpM = gcnew array<Manager^>(NUM_OF_EMPLOYEES);	
	//create EmpS array for Storage Workers
	public: static array<StorageWorker^>^ EmpS = gcnew array<StorageWorker^>(NUM_OF_EMPLOYEES);	
	//create Gain array for Finances
	public: static array<Gains^, 2>^ Gain = gcnew array<Gains^, 2>(NUM_OF_MONTHS, NUM_OF_YEARS);
	//create Expense array for Finances
	public: static array<Expenses^, 2>^ Expense = gcnew array<Expenses^, 2>(NUM_OF_MONTHS, NUM_OF_YEARS);	
	private: static FileStream ^fileInput;			
	private: static FileStream ^fileOutput;
	private: static BinaryWriter ^binaryOutput;
	private: static BinaryReader ^binaryInput;
	private: static String ^fileName;
	public: static String ^Directory;	//using this data member for images directory
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	protected: 

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->TabControl = (gcnew System::Windows::Forms::TabControl());
			this->InventoryPage = (gcnew System::Windows::Forms::TabPage());
			this->InvGroupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->InvProductIDLabel = (gcnew System::Windows::Forms::Label());
			this->InvIdLabel = (gcnew System::Windows::Forms::Label());
			this->InvToolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->InvClearEntryButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->InvViewEntryButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->InvToolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->InvAddButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->InvClearFormButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->InvListBox = (gcnew System::Windows::Forms::ListBox());
			this->InvNameBox = (gcnew System::Windows::Forms::TextBox());
			this->InvNameLabel = (gcnew System::Windows::Forms::Label());
			this->InvPlatformBox = (gcnew System::Windows::Forms::TextBox());
			this->InvPlatformLabel = (gcnew System::Windows::Forms::Label());
			this->InvRevenueBox = (gcnew System::Windows::Forms::TextBox());
			this->InvRevenueLabel = (gcnew System::Windows::Forms::Label());
			this->InvCostOfSaleBox = (gcnew System::Windows::Forms::TextBox());
			this->InvCostOfSaleLabel = (gcnew System::Windows::Forms::Label());
			this->InvCstockBox = (gcnew System::Windows::Forms::TextBox());
			this->CurrentStockLabel = (gcnew System::Windows::Forms::Label());
			this->InvIdBox = (gcnew System::Windows::Forms::TextBox());
			this->EmployeesPage = (gcnew System::Windows::Forms::TabPage());
			this->EmpGroupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->EmpToolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->EmpAddButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->EmpClearFormButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->EmpToolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->EmpClearEntryButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->EmpViewEntryButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->EmpStatusBox = (gcnew System::Windows::Forms::ComboBox());
			this->EmpLabel1 = (gcnew System::Windows::Forms::Label());
			this->EmpListBox = (gcnew System::Windows::Forms::ListBox());
			this->EmpFirstNameBox = (gcnew System::Windows::Forms::TextBox());
			this->EmpFirstNameLabel = (gcnew System::Windows::Forms::Label());
			this->EmpLastNameBox = (gcnew System::Windows::Forms::TextBox());
			this->EmpLastNameLabel = (gcnew System::Windows::Forms::Label());
			this->EmpHoursWorkedBox = (gcnew System::Windows::Forms::TextBox());
			this->EmpHoursWorkedLabel = (gcnew System::Windows::Forms::Label());
			this->EmpStatusLabel = (gcnew System::Windows::Forms::Label());
			this->EmpIdBox = (gcnew System::Windows::Forms::TextBox());
			this->EmpIdLabel = (gcnew System::Windows::Forms::Label());
			this->FinancesPage = (gcnew System::Windows::Forms::TabPage());
			this->FinancesGroupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->FinToolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->FinancesClearEntryButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->FinancesViewEntryButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->FinancesCalculationsButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->FinancesYearLabel = (gcnew System::Windows::Forms::Label());
			this->FinancesYearBox = (gcnew System::Windows::Forms::ComboBox());
			this->FinancesMonthLabel = (gcnew System::Windows::Forms::Label());
			this->FinancesMonthBox = (gcnew System::Windows::Forms::ComboBox());
			this->FinToolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->FinancesAddButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->FinancesClearButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->FinOtherGainsBox = (gcnew System::Windows::Forms::TextBox());
			this->FinOtherGainsLabel = (gcnew System::Windows::Forms::Label());
			this->FinStockExpensesBox = (gcnew System::Windows::Forms::TextBox());
			this->FinStockExpensesLabel = (gcnew System::Windows::Forms::Label());
			this->FinEmployeeExpensesBox = (gcnew System::Windows::Forms::TextBox());
			this->FinEmployeeExpensesLabel = (gcnew System::Windows::Forms::Label());
			this->FinOtherExpensesBox = (gcnew System::Windows::Forms::TextBox());
			this->FinOtherExpensesLabel = (gcnew System::Windows::Forms::Label());
			this->FinStoreGainsBox = (gcnew System::Windows::Forms::TextBox());
			this->FinStoreGainsLabel = (gcnew System::Windows::Forms::Label());
			this->SystemLogGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->SystemLogLabel = (gcnew System::Windows::Forms::RichTextBox());
			this->TabControl->SuspendLayout();
			this->InventoryPage->SuspendLayout();
			this->InvGroupBox1->SuspendLayout();
			this->InvToolStrip2->SuspendLayout();
			this->InvToolStrip1->SuspendLayout();
			this->EmployeesPage->SuspendLayout();
			this->EmpGroupBox1->SuspendLayout();
			this->EmpToolStrip1->SuspendLayout();
			this->EmpToolStrip2->SuspendLayout();
			this->FinancesPage->SuspendLayout();
			this->FinancesGroupBox1->SuspendLayout();
			this->FinToolStrip2->SuspendLayout();
			this->FinToolStrip1->SuspendLayout();
			this->SystemLogGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// TabControl
			// 
			this->TabControl->Controls->Add(this->InventoryPage);
			this->TabControl->Controls->Add(this->EmployeesPage);
			this->TabControl->Controls->Add(this->FinancesPage);
			this->TabControl->Location = System::Drawing::Point(0, 0);
			this->TabControl->Name = L"TabControl";
			this->TabControl->SelectedIndex = 0;
			this->TabControl->Size = System::Drawing::Size(708, 222);
			this->TabControl->TabIndex = 0;
			// 
			// InventoryPage
			// 
			this->InventoryPage->BackColor = System::Drawing::SystemColors::Control;
			this->InventoryPage->Controls->Add(this->InvGroupBox1);
			this->InventoryPage->Location = System::Drawing::Point(4, 22);
			this->InventoryPage->Name = L"InventoryPage";
			this->InventoryPage->Padding = System::Windows::Forms::Padding(3);
			this->InventoryPage->Size = System::Drawing::Size(700, 196);
			this->InventoryPage->TabIndex = 0;
			this->InventoryPage->Text = L"Inventory";
			// 
			// InvGroupBox1
			// 
			this->InvGroupBox1->Controls->Add(this->InvProductIDLabel);
			this->InvGroupBox1->Controls->Add(this->InvIdLabel);
			this->InvGroupBox1->Controls->Add(this->InvToolStrip2);
			this->InvGroupBox1->Controls->Add(this->InvToolStrip1);
			this->InvGroupBox1->Controls->Add(this->InvListBox);
			this->InvGroupBox1->Controls->Add(this->InvNameBox);
			this->InvGroupBox1->Controls->Add(this->InvNameLabel);
			this->InvGroupBox1->Controls->Add(this->InvPlatformBox);
			this->InvGroupBox1->Controls->Add(this->InvPlatformLabel);
			this->InvGroupBox1->Controls->Add(this->InvRevenueBox);
			this->InvGroupBox1->Controls->Add(this->InvRevenueLabel);
			this->InvGroupBox1->Controls->Add(this->InvCostOfSaleBox);
			this->InvGroupBox1->Controls->Add(this->InvCostOfSaleLabel);
			this->InvGroupBox1->Controls->Add(this->InvCstockBox);
			this->InvGroupBox1->Controls->Add(this->CurrentStockLabel);
			this->InvGroupBox1->Controls->Add(this->InvIdBox);
			this->InvGroupBox1->Location = System::Drawing::Point(8, 6);
			this->InvGroupBox1->Name = L"InvGroupBox1";
			this->InvGroupBox1->Size = System::Drawing::Size(684, 182);
			this->InvGroupBox1->TabIndex = 12;
			this->InvGroupBox1->TabStop = false;
			this->InvGroupBox1->Text = L"Enter Product Information";
			// 
			// InvProductIDLabel
			// 
			this->InvProductIDLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->InvProductIDLabel->Location = System::Drawing::Point(386, 15);
			this->InvProductIDLabel->Name = L"InvProductIDLabel";
			this->InvProductIDLabel->Size = System::Drawing::Size(88, 20);
			this->InvProductIDLabel->TabIndex = 0;
			this->InvProductIDLabel->Text = L"Product ID";
			this->InvProductIDLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// InvIdLabel
			// 
			this->InvIdLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->InvIdLabel->Location = System::Drawing::Point(6, 16);
			this->InvIdLabel->Name = L"InvIdLabel";
			this->InvIdLabel->Size = System::Drawing::Size(115, 20);
			this->InvIdLabel->TabIndex = 0;
			this->InvIdLabel->Text = L"Product ID";
			this->InvIdLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// InvToolStrip2
			// 
			this->InvToolStrip2->AllowMerge = false;
			this->InvToolStrip2->BackColor = System::Drawing::Color::Transparent;
			this->InvToolStrip2->CanOverflow = false;
			this->InvToolStrip2->Dock = System::Windows::Forms::DockStyle::None;
			this->InvToolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->InvToolStrip2->ImageScalingSize = System::Drawing::Size(30, 30);
			this->InvToolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->InvClearEntryButton, 
				this->InvViewEntryButton});
			this->InvToolStrip2->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->InvToolStrip2->Location = System::Drawing::Point(477, 16);
			this->InvToolStrip2->Name = L"InvToolStrip2";
			this->InvToolStrip2->Size = System::Drawing::Size(65, 46);
			this->InvToolStrip2->TabIndex = 9;
			this->InvToolStrip2->Text = L"InvToolStrip2";
			// 
			// InvClearEntryButton
			//
			this->InvClearEntryButton->BackColor = System::Drawing::Color::Transparent;
			this->InvClearEntryButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ClearEntryButton.bmp"))));
			this->InvClearEntryButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->InvClearEntryButton->Name = L"InvClearEntryButton";
			this->InvClearEntryButton->Size = System::Drawing::Size(64, 47);
			this->InvClearEntryButton->Text = L"Clear Entry";
			this->InvClearEntryButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->InvClearEntryButton->ToolTipText = L"Clears the selected Product ID from the database.";
			this->InvClearEntryButton->Click += gcnew System::EventHandler(this, &ChildUI::InvClearEntryButton_Click);
			// 
			// InvViewEntryButton
			// 
			this->InvViewEntryButton->BackColor = System::Drawing::Color::Transparent;
			this->InvViewEntryButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ViewEntryButton.bmp"))));
			this->InvViewEntryButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->InvViewEntryButton->Name = L"InvViewEntryButton";
			this->InvViewEntryButton->Size = System::Drawing::Size(64, 47);
			this->InvViewEntryButton->Text = L"View Entry";
			this->InvViewEntryButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->InvViewEntryButton->ToolTipText = L"View information on the selected Product ID.\r\n";
			this->InvViewEntryButton->Click += gcnew System::EventHandler(this, &ChildUI::InvViewEntryButton_Click);
			// 
			// InvToolStrip1
			// 
			this->InvToolStrip1->AllowMerge = false;
			this->InvToolStrip1->BackColor = System::Drawing::Color::Transparent;
			this->InvToolStrip1->CanOverflow = false;
			this->InvToolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->InvToolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->InvToolStrip1->ImageScalingSize = System::Drawing::Size(30, 30);
			this->InvToolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->InvAddButton, 
				this->InvClearFormButton});
			this->InvToolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->InvToolStrip1->Location = System::Drawing::Point(276, 16);
			this->InvToolStrip1->Name = L"InvToolStrip1";
			this->InvToolStrip1->Size = System::Drawing::Size(64, 72);
			this->InvToolStrip1->TabIndex = 7;
			this->InvToolStrip1->Text = L"InvToolStrip1";
			// 
			// InvAddButton
			// 
			this->InvAddButton->BackColor = System::Drawing::Color::Transparent;
			this->InvAddButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\AddButton.bmp"))));
			this->InvAddButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->InvAddButton->Name = L"InvAddButton";
			this->InvAddButton->Size = System::Drawing::Size(62, 17);
			this->InvAddButton->Text = L"Add Entry";
			this->InvAddButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->InvAddButton->ToolTipText = L"Adds an entry into the database.";
			this->InvAddButton->Click += gcnew System::EventHandler(this, &ChildUI::InvAddButton_Click);
			// 
			// InvClearFormButton
			// 
			this->InvClearFormButton->BackColor = System::Drawing::Color::Transparent;
			this->InvClearFormButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ClearFormButton.bmp"))));
			this->InvClearFormButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->InvClearFormButton->Name = L"InvClearFormButton";
			this->InvClearFormButton->Size = System::Drawing::Size(62, 47);
			this->InvClearFormButton->Text = L"Clear Form";
			this->InvClearFormButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->InvClearFormButton->ToolTipText = L"Clears the product information form.";
			this->InvClearFormButton->Click += gcnew System::EventHandler(this, &ChildUI::InvClearButton_Click);
			// 
			// InvListBox
			// 
			this->InvListBox->FormattingEnabled = true;
			this->InvListBox->Items->AddRange(gcnew cli::array< System::Object^  >(11) {L"001", L"002", L"003", L"004", L"005", L"006", 
				L"007", L"008", L"009", L"010", L"011"});
			this->InvListBox->Location = System::Drawing::Point(386, 39);
			this->InvListBox->Name = L"InvListBox";
			this->InvListBox->Size = System::Drawing::Size(88, 134);
			this->InvListBox->TabIndex = 8;
			this->InvListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ChildUI::InvListBox_SelectedIndexChanged);
			// 
			// InvNameBox
			// 
			this->InvNameBox->Location = System::Drawing::Point(127, 42);
			this->InvNameBox->Name = L"InvNameBox";
			this->InvNameBox->Size = System::Drawing::Size(146, 20);
			this->InvNameBox->TabIndex = 2;
			// 
			// InvNameLabel
			// 
			this->InvNameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->InvNameLabel->Location = System::Drawing::Point(6, 42);
			this->InvNameLabel->Name = L"InvNameLabel";
			this->InvNameLabel->Size = System::Drawing::Size(115, 20);
			this->InvNameLabel->TabIndex = 0;
			this->InvNameLabel->Text = L"Name";
			this->InvNameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// InvPlatformBox
			// 
			this->InvPlatformBox->Location = System::Drawing::Point(127, 68);
			this->InvPlatformBox->Name = L"InvPlatformBox";
			this->InvPlatformBox->Size = System::Drawing::Size(146, 20);
			this->InvPlatformBox->TabIndex = 3;
			// 
			// InvPlatformLabel
			// 
			this->InvPlatformLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->InvPlatformLabel->Location = System::Drawing::Point(6, 68);
			this->InvPlatformLabel->Name = L"InvPlatformLabel";
			this->InvPlatformLabel->Size = System::Drawing::Size(115, 20);
			this->InvPlatformLabel->TabIndex = 0;
			this->InvPlatformLabel->Text = L"Platform";
			this->InvPlatformLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// InvRevenueBox
			// 
			this->InvRevenueBox->Location = System::Drawing::Point(127, 94);
			this->InvRevenueBox->Name = L"InvRevenueBox";
			this->InvRevenueBox->Size = System::Drawing::Size(146, 20);
			this->InvRevenueBox->TabIndex = 4;
			// 
			// InvRevenueLabel
			// 
			this->InvRevenueLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->InvRevenueLabel->Location = System::Drawing::Point(6, 94);
			this->InvRevenueLabel->Name = L"InvRevenueLabel";
			this->InvRevenueLabel->Size = System::Drawing::Size(112, 20);
			this->InvRevenueLabel->TabIndex = 0;
			this->InvRevenueLabel->Text = L"Revenue";
			this->InvRevenueLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// InvCostOfSaleBox
			// 
			this->InvCostOfSaleBox->Location = System::Drawing::Point(127, 120);
			this->InvCostOfSaleBox->Name = L"InvCostOfSaleBox";
			this->InvCostOfSaleBox->Size = System::Drawing::Size(146, 20);
			this->InvCostOfSaleBox->TabIndex = 5;
			// 
			// InvCostOfSaleLabel
			// 
			this->InvCostOfSaleLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->InvCostOfSaleLabel->Location = System::Drawing::Point(6, 120);
			this->InvCostOfSaleLabel->Name = L"InvCostOfSaleLabel";
			this->InvCostOfSaleLabel->Size = System::Drawing::Size(115, 20);
			this->InvCostOfSaleLabel->TabIndex = 0;
			this->InvCostOfSaleLabel->Text = L"Cost Of Sale";
			this->InvCostOfSaleLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// InvCstockBox
			// 
			this->InvCstockBox->Location = System::Drawing::Point(127, 146);
			this->InvCstockBox->Name = L"InvCstockBox";
			this->InvCstockBox->Size = System::Drawing::Size(146, 20);
			this->InvCstockBox->TabIndex = 6;
			// 
			// CurrentStockLabel
			// 
			this->CurrentStockLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->CurrentStockLabel->Location = System::Drawing::Point(6, 146);
			this->CurrentStockLabel->Name = L"CurrentStockLabel";
			this->CurrentStockLabel->Size = System::Drawing::Size(112, 20);
			this->CurrentStockLabel->TabIndex = 0;
			this->CurrentStockLabel->Text = L"Current Stock";
			this->CurrentStockLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// InvIdBox
			// 
			this->InvIdBox->Location = System::Drawing::Point(127, 16);
			this->InvIdBox->Name = L"InvIdBox";
			this->InvIdBox->Size = System::Drawing::Size(146, 20);
			this->InvIdBox->TabIndex = 1;
			// 
			// EmployeesPage
			// 
			this->EmployeesPage->BackColor = System::Drawing::SystemColors::Control;
			this->EmployeesPage->Controls->Add(this->EmpGroupBox1);
			this->EmployeesPage->Location = System::Drawing::Point(4, 22);
			this->EmployeesPage->Name = L"EmployeesPage";
			this->EmployeesPage->Padding = System::Windows::Forms::Padding(3);
			this->EmployeesPage->Size = System::Drawing::Size(700, 196);
			this->EmployeesPage->TabIndex = 1;
			this->EmployeesPage->Text = L"Employees";
			// 
			// EmpGroupBox1
			// 
			this->EmpGroupBox1->Controls->Add(this->EmpToolStrip1);
			this->EmpGroupBox1->Controls->Add(this->EmpToolStrip2);
			this->EmpGroupBox1->Controls->Add(this->EmpStatusBox);
			this->EmpGroupBox1->Controls->Add(this->EmpLabel1);
			this->EmpGroupBox1->Controls->Add(this->EmpListBox);
			this->EmpGroupBox1->Controls->Add(this->EmpFirstNameBox);
			this->EmpGroupBox1->Controls->Add(this->EmpFirstNameLabel);
			this->EmpGroupBox1->Controls->Add(this->EmpLastNameBox);
			this->EmpGroupBox1->Controls->Add(this->EmpLastNameLabel);
			this->EmpGroupBox1->Controls->Add(this->EmpHoursWorkedBox);
			this->EmpGroupBox1->Controls->Add(this->EmpHoursWorkedLabel);
			this->EmpGroupBox1->Controls->Add(this->EmpStatusLabel);
			this->EmpGroupBox1->Controls->Add(this->EmpIdBox);
			this->EmpGroupBox1->Controls->Add(this->EmpIdLabel);
			this->EmpGroupBox1->Location = System::Drawing::Point(8, 6);
			this->EmpGroupBox1->Name = L"EmpGroupBox1";
			this->EmpGroupBox1->Size = System::Drawing::Size(684, 182);
			this->EmpGroupBox1->TabIndex = 17;
			this->EmpGroupBox1->TabStop = false;
			this->EmpGroupBox1->Text = L"Enter Employee Information";
			// 
			// EmpToolStrip1
			// 
			this->EmpToolStrip1->AllowMerge = false;
			this->EmpToolStrip1->BackColor = System::Drawing::Color::Transparent;
			this->EmpToolStrip1->CanOverflow = false;
			this->EmpToolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->EmpToolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->EmpToolStrip1->ImageScalingSize = System::Drawing::Size(30, 30);
			this->EmpToolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->EmpAddButton, 
				this->EmpClearFormButton});
			this->EmpToolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->EmpToolStrip1->Location = System::Drawing::Point(276, 16);
			this->EmpToolStrip1->Name = L"EmpToolStrip1";
			this->EmpToolStrip1->ShowItemToolTips = false;
			this->EmpToolStrip1->Size = System::Drawing::Size(65, 46);
			this->EmpToolStrip1->TabIndex = 20;
			this->EmpToolStrip1->Text = L"EmpToolStrip1";
			// 
			// EmpAddButton
			// 
			this->EmpAddButton->BackColor = System::Drawing::Color::Transparent;
			this->EmpAddButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\AddButton.bmp"))));
			this->EmpAddButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->EmpAddButton->Name = L"EmpAddButton";
			this->EmpAddButton->Size = System::Drawing::Size(62, 17);
			this->EmpAddButton->Text = L"Add Entry";
			this->EmpAddButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->EmpAddButton->ToolTipText = L"Adds an entry into the database.";
			this->EmpAddButton->Click += gcnew System::EventHandler(this, &ChildUI::EmpAddButton_Click);
			// 
			// EmpClearFormButton
			// 
			this->EmpClearFormButton->BackColor = System::Drawing::Color::Transparent;
			this->EmpClearFormButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ClearFormButton.bmp"))));
			this->EmpClearFormButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->EmpClearFormButton->Name = L"EmpClearFormButton";
			this->EmpClearFormButton->Size = System::Drawing::Size(62, 17);
			this->EmpClearFormButton->Text = L"Clear Form";
			this->EmpClearFormButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->EmpClearFormButton->ToolTipText = L"Clears the employee information form.";
			this->EmpClearFormButton->Click += gcnew System::EventHandler(this, &ChildUI::EmpClearFormButton_Click);
			// 
			// EmpToolStrip2
			// 
			this->EmpToolStrip2->AllowMerge = false;
			this->EmpToolStrip2->BackColor = System::Drawing::Color::Transparent;
			this->EmpToolStrip2->CanOverflow = false;
			this->EmpToolStrip2->Dock = System::Windows::Forms::DockStyle::None;
			this->EmpToolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->EmpToolStrip2->ImageScalingSize = System::Drawing::Size(30, 30);
			this->EmpToolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->EmpClearEntryButton, 
				this->EmpViewEntryButton});
			this->EmpToolStrip2->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->EmpToolStrip2->Location = System::Drawing::Point(477, 16);
			this->EmpToolStrip2->Name = L"EmpToolStrip2";
			this->EmpToolStrip2->ShowItemToolTips = false;
			this->EmpToolStrip2->Size = System::Drawing::Size(65, 46);
			this->EmpToolStrip2->TabIndex = 19;
			this->EmpToolStrip2->Text = L"EmpToolStrip2";
			// 
			// EmpClearEntryButton
			// 
			this->EmpClearEntryButton->BackColor = System::Drawing::Color::Transparent;
			this->EmpClearEntryButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ClearEntryButton.bmp"))));
			this->EmpClearEntryButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->EmpClearEntryButton->Name = L"EmpClearEntryButton";
			this->EmpClearEntryButton->Size = System::Drawing::Size(64, 17);
			this->EmpClearEntryButton->Text = L"Clear Entry";
			this->EmpClearEntryButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->EmpClearEntryButton->ToolTipText = L"Clears the selected Employee ID from the database.";
			this->EmpClearEntryButton->Click += gcnew System::EventHandler(this, &ChildUI::EmpClearEntryButton_Click);
			// 
			// EmpViewEntryButton
			// 
			this->EmpViewEntryButton->BackColor = System::Drawing::Color::Transparent;
			this->EmpViewEntryButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ViewEntryButton.bmp"))));
			this->EmpViewEntryButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->EmpViewEntryButton->Name = L"EmpViewEntryButton";
			this->EmpViewEntryButton->Size = System::Drawing::Size(64, 17);
			this->EmpViewEntryButton->Text = L"View Entry";
			this->EmpViewEntryButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->EmpViewEntryButton->ToolTipText = L"View information on the selected Employee ID.";
			this->EmpViewEntryButton->Click += gcnew System::EventHandler(this, &ChildUI::EmpViewEntryButton_Click);
			// 
			// EmpStatusBox
			// 
			this->EmpStatusBox->FormattingEnabled = true;
			this->EmpStatusBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Manager", L"Storage Worker"});
			this->EmpStatusBox->Location = System::Drawing::Point(127, 135);
			this->EmpStatusBox->Name = L"EmpStatusBox";
			this->EmpStatusBox->Size = System::Drawing::Size(146, 21);
			this->EmpStatusBox->TabIndex = 5;
			this->EmpStatusBox->Text = L"Select...";
			// 
			// EmpLabel1
			// 
			this->EmpLabel1->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->EmpLabel1->Location = System::Drawing::Point(383, 16);
			this->EmpLabel1->Name = L"EmpLabel1";
			this->EmpLabel1->Size = System::Drawing::Size(91, 20);
			this->EmpLabel1->TabIndex = 13;
			this->EmpLabel1->Text = L"Employee ID";
			this->EmpLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// EmpListBox
			// 
			this->EmpListBox->FormattingEnabled = true;
			this->EmpListBox->Items->AddRange(gcnew cli::array< System::Object^  >(11) {L"001", L"002", L"003", L"004", L"005", L"006", 
				L"007", L"008", L"009", L"010", L"011"});
			this->EmpListBox->Location = System::Drawing::Point(386, 39);
			this->EmpListBox->Name = L"EmpListBox";
			this->EmpListBox->Size = System::Drawing::Size(88, 134);
			this->EmpListBox->TabIndex = 13;
			this->EmpListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ChildUI::EmpListBox_SelectedIndexChanged);
			// 
			// EmpFirstNameBox
			// 
			this->EmpFirstNameBox->Location = System::Drawing::Point(127, 58);
			this->EmpFirstNameBox->Name = L"EmpFirstNameBox";
			this->EmpFirstNameBox->Size = System::Drawing::Size(146, 20);
			this->EmpFirstNameBox->TabIndex = 2;
			// 
			// EmpFirstNameLabel
			// 
			this->EmpFirstNameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->EmpFirstNameLabel->Location = System::Drawing::Point(6, 58);
			this->EmpFirstNameLabel->Name = L"EmpFirstNameLabel";
			this->EmpFirstNameLabel->Size = System::Drawing::Size(115, 20);
			this->EmpFirstNameLabel->TabIndex = 10;
			this->EmpFirstNameLabel->Text = L"First Name";
			this->EmpFirstNameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// EmpLastNameBox
			// 
			this->EmpLastNameBox->Location = System::Drawing::Point(127, 84);
			this->EmpLastNameBox->Name = L"EmpLastNameBox";
			this->EmpLastNameBox->Size = System::Drawing::Size(146, 20);
			this->EmpLastNameBox->TabIndex = 3;
			// 
			// EmpLastNameLabel
			// 
			this->EmpLastNameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->EmpLastNameLabel->Location = System::Drawing::Point(6, 84);
			this->EmpLastNameLabel->Name = L"EmpLastNameLabel";
			this->EmpLastNameLabel->Size = System::Drawing::Size(115, 20);
			this->EmpLastNameLabel->TabIndex = 8;
			this->EmpLastNameLabel->Text = L"Last Name";
			this->EmpLastNameLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// EmpHoursWorkedBox
			// 
			this->EmpHoursWorkedBox->Location = System::Drawing::Point(127, 110);
			this->EmpHoursWorkedBox->Name = L"EmpHoursWorkedBox";
			this->EmpHoursWorkedBox->Size = System::Drawing::Size(146, 20);
			this->EmpHoursWorkedBox->TabIndex = 4;
			// 
			// EmpHoursWorkedLabel
			// 
			this->EmpHoursWorkedLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->EmpHoursWorkedLabel->Location = System::Drawing::Point(6, 110);
			this->EmpHoursWorkedLabel->Name = L"EmpHoursWorkedLabel";
			this->EmpHoursWorkedLabel->Size = System::Drawing::Size(112, 20);
			this->EmpHoursWorkedLabel->TabIndex = 6;
			this->EmpHoursWorkedLabel->Text = L"Hours Worked";
			this->EmpHoursWorkedLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// EmpStatusLabel
			// 
			this->EmpStatusLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->EmpStatusLabel->Location = System::Drawing::Point(6, 136);
			this->EmpStatusLabel->Name = L"EmpStatusLabel";
			this->EmpStatusLabel->Size = System::Drawing::Size(115, 20);
			this->EmpStatusLabel->TabIndex = 4;
			this->EmpStatusLabel->Text = L"Status";
			this->EmpStatusLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// EmpIdBox
			// 
			this->EmpIdBox->Location = System::Drawing::Point(127, 32);
			this->EmpIdBox->Name = L"EmpIdBox";
			this->EmpIdBox->Size = System::Drawing::Size(146, 20);
			this->EmpIdBox->TabIndex = 1;
			// 
			// EmpIdLabel
			// 
			this->EmpIdLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->EmpIdLabel->Location = System::Drawing::Point(6, 32);
			this->EmpIdLabel->Name = L"EmpIdLabel";
			this->EmpIdLabel->Size = System::Drawing::Size(115, 20);
			this->EmpIdLabel->TabIndex = 0;
			this->EmpIdLabel->Text = L"ID Number";
			this->EmpIdLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FinancesPage
			// 
			this->FinancesPage->BackColor = System::Drawing::SystemColors::Control;
			this->FinancesPage->Controls->Add(this->FinancesGroupBox1);
			this->FinancesPage->Location = System::Drawing::Point(4, 22);
			this->FinancesPage->Name = L"FinancesPage";
			this->FinancesPage->Padding = System::Windows::Forms::Padding(3);
			this->FinancesPage->Size = System::Drawing::Size(700, 196);
			this->FinancesPage->TabIndex = 2;
			this->FinancesPage->Text = L"Finances";
			// 
			// FinancesGroupBox1
			// 
			this->FinancesGroupBox1->Controls->Add(this->FinToolStrip2);
			this->FinancesGroupBox1->Controls->Add(this->FinancesYearLabel);
			this->FinancesGroupBox1->Controls->Add(this->FinancesYearBox);
			this->FinancesGroupBox1->Controls->Add(this->FinancesMonthLabel);
			this->FinancesGroupBox1->Controls->Add(this->FinancesMonthBox);
			this->FinancesGroupBox1->Controls->Add(this->FinToolStrip1);
			this->FinancesGroupBox1->Controls->Add(this->FinOtherGainsBox);
			this->FinancesGroupBox1->Controls->Add(this->FinOtherGainsLabel);
			this->FinancesGroupBox1->Controls->Add(this->FinStockExpensesBox);
			this->FinancesGroupBox1->Controls->Add(this->FinStockExpensesLabel);
			this->FinancesGroupBox1->Controls->Add(this->FinEmployeeExpensesBox);
			this->FinancesGroupBox1->Controls->Add(this->FinEmployeeExpensesLabel);
			this->FinancesGroupBox1->Controls->Add(this->FinOtherExpensesBox);
			this->FinancesGroupBox1->Controls->Add(this->FinOtherExpensesLabel);
			this->FinancesGroupBox1->Controls->Add(this->FinStoreGainsBox);
			this->FinancesGroupBox1->Controls->Add(this->FinStoreGainsLabel);
			this->FinancesGroupBox1->Location = System::Drawing::Point(8, 6);
			this->FinancesGroupBox1->Name = L"FinancesGroupBox1";
			this->FinancesGroupBox1->Size = System::Drawing::Size(684, 182);
			this->FinancesGroupBox1->TabIndex = 17;
			this->FinancesGroupBox1->TabStop = false;
			this->FinancesGroupBox1->Text = L"Enter Finance Information";
			// 
			// FinToolStrip2
			// 
			this->FinToolStrip2->AllowMerge = false;
			this->FinToolStrip2->BackColor = System::Drawing::Color::Transparent;
			this->FinToolStrip2->CanOverflow = false;
			this->FinToolStrip2->Dock = System::Windows::Forms::DockStyle::None;
			this->FinToolStrip2->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->FinToolStrip2->ImageScalingSize = System::Drawing::Size(30, 30);
			this->FinToolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->FinancesClearEntryButton, 
				this->FinancesViewEntryButton, this->FinancesCalculationsButton});
			this->FinToolStrip2->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->FinToolStrip2->Location = System::Drawing::Point(496, 16);
			this->FinToolStrip2->Name = L"FinToolStrip2";
			this->FinToolStrip2->ShowItemToolTips = false;
			this->FinToolStrip2->Size = System::Drawing::Size(71, 87);
			this->FinToolStrip2->TabIndex = 23;
			this->FinToolStrip2->Text = L"FinToolStrip2";
			// 
			// FinancesClearEntryButton
			// 
			this->FinancesClearEntryButton->BackColor = System::Drawing::Color::Transparent;
			this->FinancesClearEntryButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ClearEntryButton.bmp"))));
			this->FinancesClearEntryButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->FinancesClearEntryButton->Name = L"FinancesClearEntryButton";
			this->FinancesClearEntryButton->Size = System::Drawing::Size(64, 17);
			this->FinancesClearEntryButton->Text = L"Clear Entry";
			this->FinancesClearEntryButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->FinancesClearEntryButton->Click += gcnew System::EventHandler(this, &ChildUI::FinancesClearEntryButton_Click);
			// 
			// FinancesViewEntryButton
			// 
			this->FinancesViewEntryButton->BackColor = System::Drawing::Color::Transparent;
			this->FinancesViewEntryButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ViewEntryButton.bmp"))));
			this->FinancesViewEntryButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->FinancesViewEntryButton->Name = L"FinancesViewButton";
			this->FinancesViewEntryButton->Size = System::Drawing::Size(64, 17);
			this->FinancesViewEntryButton->Text = L"View Entry";
			this->FinancesViewEntryButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->FinancesViewEntryButton->Click += gcnew System::EventHandler(this, &ChildUI::FinancesViewButton_Click);
			// 
			// FinancesCalculationsButton
			// 
			this->FinancesCalculationsButton->BackColor = System::Drawing::Color::Transparent;
			this->FinancesCalculationsButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\Calculations.bmp"))));
			this->FinancesCalculationsButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->FinancesCalculationsButton->Name = L"FinancesCalculationsButton";
			this->FinancesCalculationsButton->Size = System::Drawing::Size(69, 19);
			this->FinancesCalculationsButton->Text = L"Calculations";
			this->FinancesCalculationsButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->FinancesCalculationsButton->Click += gcnew System::EventHandler(this, &ChildUI::FinancesCalculationsButton_Click);
			// 
			// FinancesYearLabel
			// 
			this->FinancesYearLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->FinancesYearLabel->Location = System::Drawing::Point(374, 63);
			this->FinancesYearLabel->Name = L"FinancesYearLabel";
			this->FinancesYearLabel->Size = System::Drawing::Size(91, 21);
			this->FinancesYearLabel->TabIndex = 22;
			this->FinancesYearLabel->Text = L"Year";
			this->FinancesYearLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FinancesYearBox
			// 
			this->FinancesYearBox->FormattingEnabled = true;
			this->FinancesYearBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"2006", L"2007", L"2008"});
			this->FinancesYearBox->Location = System::Drawing::Point(377, 87);
			this->FinancesYearBox->Name = L"FinancesYearBox";
			this->FinancesYearBox->Size = System::Drawing::Size(116, 21);
			this->FinancesYearBox->TabIndex = 7;
			this->FinancesYearBox->Text = L"Select Year...";
			// 
			// FinancesMonthLabel
			// 
			this->FinancesMonthLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->FinancesMonthLabel->Location = System::Drawing::Point(374, 16);
			this->FinancesMonthLabel->Name = L"FinancesMonthLabel";
			this->FinancesMonthLabel->Size = System::Drawing::Size(91, 20);
			this->FinancesMonthLabel->TabIndex = 20;
			this->FinancesMonthLabel->Text = L"Month";
			this->FinancesMonthLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FinancesMonthBox
			// 
			this->FinancesMonthBox->FormattingEnabled = true;
			this->FinancesMonthBox->Items->AddRange(gcnew cli::array< System::Object^  >(12) {L"January", L"February", L"March", L"April", 
				L"May", L"June", L"July", L"August", L"September", L"October", L"November", L"December"});
			this->FinancesMonthBox->Location = System::Drawing::Point(377, 39);
			this->FinancesMonthBox->Name = L"FinancesMonthBox";
			this->FinancesMonthBox->Size = System::Drawing::Size(116, 21);
			this->FinancesMonthBox->TabIndex = 6;
			this->FinancesMonthBox->Text = L"Select Month...";
			// 
			// FinToolStrip1
			// 
			this->FinToolStrip1->AllowMerge = false;
			this->FinToolStrip1->BackColor = System::Drawing::Color::Transparent;
			this->FinToolStrip1->CanOverflow = false;
			this->FinToolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->FinToolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->FinToolStrip1->ImageScalingSize = System::Drawing::Size(30, 30);
			this->FinToolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->FinancesAddButton, 
				this->FinancesClearButton});
			this->FinToolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::VerticalStackWithOverflow;
			this->FinToolStrip1->Location = System::Drawing::Point(297, 16);
			this->FinToolStrip1->Name = L"FinToolStrip1";
			this->FinToolStrip1->ShowItemToolTips = false;
			this->FinToolStrip1->Size = System::Drawing::Size(65, 46);
			this->FinToolStrip1->TabIndex = 12;
			this->FinToolStrip1->Text = L"FinToolStrip1";
			// 
			// FinancesAddButton
			// 
			this->FinancesAddButton->BackColor = System::Drawing::Color::Transparent;
			this->FinancesAddButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\AddButton.bmp"))));
			this->FinancesAddButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->FinancesAddButton->Name = L"FinancesAddButton";
			this->FinancesAddButton->Size = System::Drawing::Size(62, 17);
			this->FinancesAddButton->Text = L"Add";
			this->FinancesAddButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->FinancesAddButton->Click += gcnew System::EventHandler(this, &ChildUI::FinancesAddButton_Click);
			// 
			// FinancesClearButton
			// 
			this->FinancesClearButton->BackColor = System::Drawing::Color::Transparent;
			this->FinancesClearButton->Image = (cli::safe_cast<System::Drawing::Image^  >(Image::FromFile( String::Concat(
				Directory, L"\\images\\ClearFormButton.bmp"))));
			this->FinancesClearButton->ImageTransparentColor = System::Drawing::Color::Gray;
			this->FinancesClearButton->Name = L"FinancesClearButton";
			this->FinancesClearButton->Size = System::Drawing::Size(62, 17);
			this->FinancesClearButton->Text = L"Clear Form";
			this->FinancesClearButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->FinancesClearButton->Click += gcnew System::EventHandler(this, &ChildUI::FinancesClearButton_Click);
			// 
			// FinOtherGainsBox
			// 
			this->FinOtherGainsBox->Location = System::Drawing::Point(148, 56);
			this->FinOtherGainsBox->Name = L"FinOtherGainsBox";
			this->FinOtherGainsBox->Size = System::Drawing::Size(146, 20);
			this->FinOtherGainsBox->TabIndex = 2;
			// 
			// FinOtherGainsLabel
			// 
			this->FinOtherGainsLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->FinOtherGainsLabel->Location = System::Drawing::Point(6, 56);
			this->FinOtherGainsLabel->Name = L"FinOtherGainsLabel";
			this->FinOtherGainsLabel->Size = System::Drawing::Size(136, 20);
			this->FinOtherGainsLabel->TabIndex = 10;
			this->FinOtherGainsLabel->Text = L"Other Gains";
			this->FinOtherGainsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FinStockExpensesBox
			// 
			this->FinStockExpensesBox->Location = System::Drawing::Point(148, 82);
			this->FinStockExpensesBox->Name = L"FinStockExpensesBox";
			this->FinStockExpensesBox->Size = System::Drawing::Size(146, 20);
			this->FinStockExpensesBox->TabIndex = 3;
			// 
			// FinStockExpensesLabel
			// 
			this->FinStockExpensesLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->FinStockExpensesLabel->Location = System::Drawing::Point(6, 82);
			this->FinStockExpensesLabel->Name = L"FinStockExpensesLabel";
			this->FinStockExpensesLabel->Size = System::Drawing::Size(136, 20);
			this->FinStockExpensesLabel->TabIndex = 8;
			this->FinStockExpensesLabel->Text = L"Stock Expenses";
			this->FinStockExpensesLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FinEmployeeExpensesBox
			// 
			this->FinEmployeeExpensesBox->Location = System::Drawing::Point(148, 108);
			this->FinEmployeeExpensesBox->Name = L"FinEmployeeExpensesBox";
			this->FinEmployeeExpensesBox->Size = System::Drawing::Size(146, 20);
			this->FinEmployeeExpensesBox->TabIndex = 4;
			// 
			// FinEmployeeExpensesLabel
			// 
			this->FinEmployeeExpensesLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->FinEmployeeExpensesLabel->Location = System::Drawing::Point(6, 108);
			this->FinEmployeeExpensesLabel->Name = L"FinEmployeeExpensesLabel";
			this->FinEmployeeExpensesLabel->Size = System::Drawing::Size(136, 20);
			this->FinEmployeeExpensesLabel->TabIndex = 6;
			this->FinEmployeeExpensesLabel->Text = L"Employee Expenses";
			this->FinEmployeeExpensesLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FinOtherExpensesBox
			// 
			this->FinOtherExpensesBox->Location = System::Drawing::Point(148, 134);
			this->FinOtherExpensesBox->Name = L"FinOtherExpensesBox";
			this->FinOtherExpensesBox->Size = System::Drawing::Size(146, 20);
			this->FinOtherExpensesBox->TabIndex = 5;
			// 
			// FinOtherExpensesLabel
			// 
			this->FinOtherExpensesLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->FinOtherExpensesLabel->Location = System::Drawing::Point(6, 134);
			this->FinOtherExpensesLabel->Name = L"FinOtherExpensesLabel";
			this->FinOtherExpensesLabel->Size = System::Drawing::Size(136, 20);
			this->FinOtherExpensesLabel->TabIndex = 4;
			this->FinOtherExpensesLabel->Text = L"Other Expenses";
			this->FinOtherExpensesLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// FinStoreGainsBox
			// 
			this->FinStoreGainsBox->Location = System::Drawing::Point(148, 30);
			this->FinStoreGainsBox->Name = L"FinStoreGainsBox";
			this->FinStoreGainsBox->Size = System::Drawing::Size(146, 20);
			this->FinStoreGainsBox->TabIndex = 1;
			// 
			// FinStoreGainsLabel
			// 
			this->FinStoreGainsLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->FinStoreGainsLabel->Location = System::Drawing::Point(6, 30);
			this->FinStoreGainsLabel->Name = L"FinStoreGainsLabel";
			this->FinStoreGainsLabel->Size = System::Drawing::Size(136, 20);
			this->FinStoreGainsLabel->TabIndex = 0;
			this->FinStoreGainsLabel->Text = L"Store Gains";
			this->FinStoreGainsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// SystemLogGroupBox
			// 
			this->SystemLogGroupBox->Controls->Add(this->SystemLogLabel);
			this->SystemLogGroupBox->Location = System::Drawing::Point(12, 224);
			this->SystemLogGroupBox->Name = L"SystemLogGroupBox";
			this->SystemLogGroupBox->Size = System::Drawing::Size(684, 208);
			this->SystemLogGroupBox->TabIndex = 2;
			this->SystemLogGroupBox->TabStop = false;
			this->SystemLogGroupBox->Text = L"System Log";
			// 
			// SystemLogLabel
			// 
			this->SystemLogLabel->BackColor = System::Drawing::Color::White;
			this->SystemLogLabel->Cursor = System::Windows::Forms::Cursors::Default;
			this->SystemLogLabel->Location = System::Drawing::Point(6, 19);
			this->SystemLogLabel->Name = L"SystemLogLabel";
			this->SystemLogLabel->ReadOnly = true;
			this->SystemLogLabel->Size = System::Drawing::Size(670, 180);
			this->SystemLogLabel->TabIndex = 0;
			this->SystemLogLabel->TabStop = false;
			this->SystemLogLabel->Text = L"";
			// 
			// ChildUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(708, 435);
			this->ControlBox = false;
			this->Controls->Add(this->SystemLogGroupBox);
			this->Controls->Add(this->TabControl);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(716, 466);
			this->MinimizeBox = false;
			this->Name = L"ChildUI";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->TransparencyKey = System::Drawing::Color::Transparent;
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->TabControl->ResumeLayout(false);
			this->InventoryPage->ResumeLayout(false);
			this->InvGroupBox1->ResumeLayout(false);
			this->InvGroupBox1->PerformLayout();
			this->InvToolStrip2->ResumeLayout(false);
			this->InvToolStrip2->PerformLayout();
			this->InvToolStrip1->ResumeLayout(false);
			this->InvToolStrip1->PerformLayout();
			this->EmployeesPage->ResumeLayout(false);
			this->EmpGroupBox1->ResumeLayout(false);
			this->EmpGroupBox1->PerformLayout();
			this->EmpToolStrip1->ResumeLayout(false);
			this->EmpToolStrip1->PerformLayout();
			this->EmpToolStrip2->ResumeLayout(false);
			this->EmpToolStrip2->PerformLayout();
			this->FinancesPage->ResumeLayout(false);
			this->FinancesGroupBox1->ResumeLayout(false);
			this->FinancesGroupBox1->PerformLayout();
			this->FinToolStrip2->ResumeLayout(false);
			this->FinToolStrip2->PerformLayout();
			this->FinToolStrip1->ResumeLayout(false);
			this->FinToolStrip1->PerformLayout();
			this->SystemLogGroupBox->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

//////////////////////////////////////////////////
/////// INVENTORY ADD ENTRY BUTTON CLICK /////////
//////////////////////////////////////////////////
private: System::Void InvAddButton_Click(System::Object^  sender, System::EventArgs^  e) {

			//CHECK IF INPUTS ARE VALID
			if ( InvNameBox->Text->Length > 0 && InvPlatformBox->Text->Length > 0
						&& Int32::Parse(InvIdBox->Text) > 0
						&& Int32::Parse(InvIdBox->Text) <= NUM_OF_PRODUCTS )
			{
				//INPUT ENTRY INTO ARRAY
				double revenue = double::Parse(InvRevenueBox->Text);
				double costofsale = double::Parse(InvCostOfSaleBox->Text);
				int cstock = Int32::Parse(InvCstockBox->Text);
				int id = Int32::Parse(InvIdBox->Text);
				Inv[id-1]->ID = id;
				Inv[id-1]->Name = InvNameBox->Text;
				Inv[id-1]->Platform = InvPlatformBox->Text;
				Inv[id-1]->Revenue = revenue;
				Inv[id-1]->CostOfSale = costofsale;
				Inv[id-1]->CurrentStock = cstock;

				//OUTPUT ENTRY INFORMATION INTO SYSTEM LOG BOX
				SystemLogLabel->Text = ( "ADDED-> Entry #" + id.ToString() + 
					L" " + InvNameBox->Text + "\n\n" + SystemLogLabel->Text );
					 
				//CLEAR FORM
				InvIdBox->Clear();
				InvNameBox->Clear();
				InvPlatformBox->Clear();
				InvRevenueBox->Clear();
				InvCostOfSaleBox->Clear();
				InvCstockBox->Clear();
			}
			
			//RETURN ERROR IF INPUTS ARE INVALID
			else
			{
				MessageBox::Show( L"Invalid Name or Platform or ID", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );
			}
		 }

//////////////////////////////////////////////////
////// INVENTORY CLEAR FORM BUTTON CLICK /////////
//////////////////////////////////////////////////
private: System::Void InvClearButton_Click(System::Object^  sender, System::EventArgs^  e) {
	 
			//CLEAR FORM
			InvIdBox->Clear();
			InvNameBox->Clear();
			InvPlatformBox->Clear();
			InvRevenueBox->Clear();
			InvCostOfSaleBox->Clear();
			InvCstockBox->Clear();
		 }

/////////////////////////////////////////////
////// INVENTORY LIST BOX SELECTION /////////
/////////////////////////////////////////////
private: System::Void InvListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

			//SHOW SELECTED PRODUCT ID INFORMATION IN THE FORM BOXES
			InvIdBox->Text = Inv[InvListBox->SelectedIndex]->ID.ToString();
			InvNameBox->Text = Inv[InvListBox->SelectedIndex]->Name;
			InvPlatformBox->Text = Inv[InvListBox->SelectedIndex]->Platform;
			InvRevenueBox->Text = Inv[InvListBox->SelectedIndex]->Revenue.ToString();
			InvCostOfSaleBox->Text = Inv[InvListBox->SelectedIndex]->CostOfSale.ToString();
			InvCstockBox->Text = Inv[InvListBox->SelectedIndex]->CurrentStock.ToString();
		 }

///////////////////////////////////////////////////
////// INVENTORY CLEAR ENTRY BUTTON CLICK /////////
///////////////////////////////////////////////////
private: System::Void InvClearEntryButton_Click(System::Object^  sender, System::EventArgs^  e) {

		if (InvListBox->SelectedIndex >= 0 && EmpListBox->SelectedIndex < NUM_OF_PRODUCTS) {
			//SHOW CLEAR INFORMATION IN SYSTEM LOG BOX
			SystemLogLabel->Text = ( L"CLEARED-> Entry #" + (InvListBox->SelectedIndex+1) + 
					L" " + Inv[InvListBox->SelectedIndex]->Name + "\n\n" + SystemLogLabel->Text );

			//CLEAR ENTRY AND SET THE INFORMATION TO DEFAULT
			Inv[InvListBox->SelectedIndex]->ID = 0;
			Inv[InvListBox->SelectedIndex]->Name = L"Default Name";
			Inv[InvListBox->SelectedIndex]->Platform = L"Default Platform";
			Inv[InvListBox->SelectedIndex]->Revenue = 0;
			Inv[InvListBox->SelectedIndex]->CostOfSale = 0;
			Inv[InvListBox->SelectedIndex]->CurrentStock = 0;
	 
			//CLEAR FORM
			InvIdBox->Clear();
			InvNameBox->Clear();
			InvPlatformBox->Clear();
			InvRevenueBox->Clear();
			InvCostOfSaleBox->Clear();
			InvCstockBox->Clear();
		}
		else
			MessageBox::Show(L"Invalid Product ID\nPlease Select a Product ID", L"Error",
				MessageBoxButtons::OK, MessageBoxIcon::Error );
	 }
		 
///////////////////////////////////////////////////////
////// INVENTORY VIEW ENTRY INFO BUTTON CLICK /////////
///////////////////////////////////////////////////////
private: System::Void InvViewEntryButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
			//CHECK IF SELECTION IS VALID AND DISPLAY INFORMATION USING TOSTRING() 
			if (InvListBox->SelectedIndex >= 0 && EmpListBox->SelectedIndex < NUM_OF_PRODUCTS)
				SystemLogLabel->Text = ( Inv[InvListBox->SelectedIndex]->ToString() + "\n" + SystemLogLabel->Text );
			else
				MessageBox::Show(L"Invalid Product ID\nPlease Select a Product ID", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );
		 }
		 
////////////////////////////////////////////////
////// EMPLOYEE ADD ENTRY BUTTON CLICK /////////
////////////////////////////////////////////////
private: System::Void EmpAddButton_Click(System::Object^  sender, System::EventArgs^  e) {

			//CHECK IF INPUTS ARE VALID
			if ( EmpFirstNameBox->Text->Length > 0 && EmpLastNameBox->Text->Length > 0
						&& Int32::Parse(EmpIdBox->Text) > 0
						&& Int32::Parse(EmpIdBox->Text) <= NUM_OF_EMPLOYEES )
			{
				//INPUT ENTRY INTO ARRAY
				int hours = Int32::Parse(EmpHoursWorkedBox->Text);
				int type = EmpStatusBox->SelectedIndex;
				int id = Int32::Parse(EmpIdBox->Text);

				//CHECK ENTRY TYPE AND USE CORRESPONDING ARRAY
				//OUTPUT ENTRY INFORMATION INTO SYSTEM LOG BOX
				if (type == 0)
				{
					Emp[id-1] = gcnew Manager();
					Emp[id-1]->ID = id;
					Emp[id-1]->FirstName = EmpFirstNameBox->Text;
					Emp[id-1]->LastName = EmpLastNameBox->Text;
					Emp[id-1]->HoursWorked = hours;
					Emp[id-1]->Type = 0;
					SystemLogLabel->Text = ( "ADDED-> Entry #" + id.ToString() + 
						L" Manager, " + EmpFirstNameBox->Text + L" " + EmpLastNameBox->Text + "\n\n" + SystemLogLabel->Text);
				}
				else
				{
					Emp[id-1] = gcnew StorageWorker();
					Emp[id-1]->ID = id;
					Emp[id-1]->FirstName = EmpFirstNameBox->Text;
					Emp[id-1]->LastName = EmpLastNameBox->Text;
					Emp[id-1]->HoursWorked = hours;
					Emp[id-1]->Type = 1;
					SystemLogLabel->Text = ( "ADDED-> Entry #" + id.ToString() + 
						L" Storage Worker, "  + EmpFirstNameBox->Text + L" " + EmpLastNameBox->Text + "\n\n" + SystemLogLabel->Text );
				}

				//CLEAR FORM
				EmpIdBox->Clear();
				EmpFirstNameBox->Clear();
				EmpLastNameBox->Clear();
				EmpHoursWorkedBox->Clear();
			}
			
			//RETURN ERROR IF INPUTS ARE INVALID
			else
			{
				MessageBox::Show( L"Invalid Name or ID", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );
			}
		 }
		 
////////////////////////////////////////////
////// EMPLOYEE LIST BOX SELECTION /////////
////////////////////////////////////////////
private: System::Void EmpListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

			//SHOW SELECTED EMPLOYEE INFORMATION IN THE FORM BOXES
			EmpIdBox->Text =			Emp[EmpListBox->SelectedIndex]->ID.ToString();
			EmpFirstNameBox->Text =		Emp[EmpListBox->SelectedIndex]->FirstName;
			EmpLastNameBox->Text =		Emp[EmpListBox->SelectedIndex]->LastName;
			EmpHoursWorkedBox->Text =	Emp[EmpListBox->SelectedIndex]->HoursWorked.ToString();

			if (Emp[EmpListBox->SelectedIndex]->Type == 0)
			{
				EmpStatusBox->SelectedIndex = 0;
			}
	
			else
			{
				EmpStatusBox->SelectedIndex = 1;
			}
		 }
		 
/////////////////////////////////////////////////
////// EMPLOYEE CLEAR FORM BUTTON CLICK /////////
/////////////////////////////////////////////////
private: System::Void EmpClearFormButton_Click(System::Object^  sender, System::EventArgs^  e) {
		 
			//CLEAR FORM
		 	EmpIdBox->Clear();
			EmpFirstNameBox->Clear();
			EmpLastNameBox->Clear();
			EmpHoursWorkedBox->Clear();
		 }
		 
/////////////////////////////////////////////////
////// EMPLOYEE VIEW ENTRY BUTTON CLICK /////////
/////////////////////////////////////////////////
private: System::Void EmpViewEntryButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
			//CHECK IF SELECTION IS VALID AND DISPLAY INFORMATION USING TOSTRING() 
			if (EmpListBox->SelectedIndex >= 0 && EmpListBox->SelectedIndex < NUM_OF_EMPLOYEES)
			SystemLogLabel->Text = ( Emp[EmpListBox->SelectedIndex]->ToString() + "\n\n" + SystemLogLabel->Text );
			else
				MessageBox::Show(L"Invalid Employee ID\nPlease Select an Employee ID", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );
		 }
		 
//////////////////////////////////////////////////
////// EMPLOYEE CLEAR ENTRY BUTTON CLICK /////////
//////////////////////////////////////////////////
private: System::Void EmpClearEntryButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
		if (EmpListBox->SelectedIndex >= 0 && EmpListBox->SelectedIndex < NUM_OF_EMPLOYEES) {
			//SHOW CLEAR INFORMATION IN THE SYSTEM LOG BOX
			if (Emp[EmpListBox->SelectedIndex]->Type == 0)
			{
				SystemLogLabel->Text = ( L"CLEARED-> Entry #" + (EmpListBox->SelectedIndex+1) + 
					L" Manager " + Emp[EmpListBox->SelectedIndex]->FirstName + Emp[EmpListBox->SelectedIndex]->LastName + "\n\n" + SystemLogLabel->Text );
			}
			else
			{
				SystemLogLabel->Text = ( L"CLEARED-> Entry #" + (EmpListBox->SelectedIndex+1) + 
					L" Storage Worker " + Emp[EmpListBox->SelectedIndex]->FirstName + Emp[EmpListBox->SelectedIndex]->LastName + "\n\n" + SystemLogLabel->Text );
			}

			//CLEAR ENTRY AND SET TO DEFAULT
			Emp[EmpListBox->SelectedIndex]->ID = 0;
			Emp[EmpListBox->SelectedIndex]->FirstName = L"Default First Name";
			Emp[EmpListBox->SelectedIndex]->LastName = L"Default Last Name";
			Emp[EmpListBox->SelectedIndex]->HoursWorked = 0;
	 
			//CLEAR FORM
			EmpIdBox->Clear();
			EmpFirstNameBox->Clear();
			EmpLastNameBox->Clear();
			EmpHoursWorkedBox->Clear();
		}
		
		else
			MessageBox::Show(L"Invalid Employee ID\nPlease Select an Employee ID", L"Error",
				MessageBoxButtons::OK, MessageBoxIcon::Error );
	}
		 
////////////////////////////////////////////////
////// FINANCES ADD ENTRY BUTTON CLICK /////////
////////////////////////////////////////////////
private: System::Void FinancesAddButton_Click(System::Object^  sender, System::EventArgs^  e) {

	//TRY FUNCTION USED TO CHECK VALIDITY OF INPUTS
	try
	{
			 //CHECK IF DATE INPUTS ARE VALID
			 if ( FinancesMonthBox->SelectedIndex >= 0 &&
				  FinancesYearBox->SelectedIndex >= 0)
			 {
				//CONVERT AND INPUT ENTRY INTO ARRAY
				double storegains = double::Parse(FinStoreGainsBox->Text);
				double othergains = double::Parse(FinOtherGainsBox->Text);
				double stockexpenses = double::Parse(FinStockExpensesBox->Text);
				double empexpenses = double::Parse(FinEmployeeExpensesBox->Text);
				double otherexpenses = double::Parse(FinOtherExpensesBox->Text);
				int month = FinancesMonthBox->SelectedIndex;
				int year = FinancesYearBox->SelectedIndex;
				Gain[month, year]->StoreGains = storegains;
				Gain[month, year]->OtherGains = othergains;
				Expense[month, year]->StockExpense = stockexpenses;
				Expense[month, year]->EmployeeExpense = empexpenses;
				Expense[month, year]->OtherExpense = otherexpenses;
				
				//OUTPUT ENTRY INFORMATION INTO THE SYSTEM LOG BOX
				SystemLogLabel->Text = ( "ADDED-> Finances Entry for " + (month+1).ToString()
					+ L"/" + (2006+year).ToString() + "\n\n" + SystemLogLabel->Text );
					 
				FinStoreGainsBox->Clear();
				FinOtherGainsBox->Clear();
				FinStockExpensesBox->Clear();
				FinEmployeeExpensesBox->Clear();
				FinOtherExpensesBox->Clear();
			}
			
			//RETURN ERROR IF DATE INPUTS ARE INVALID
			else
			{
				MessageBox::Show( L"Invalid Dates", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );
			}
	}
	catch ( FormatException ^)
	{
				MessageBox::Show( L"Invalid Inputs", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );
	}
}
		 
/////////////////////////////////////////////////
////// FINANCES CLEAR FORM BUTTON CLICK /////////
/////////////////////////////////////////////////
private: System::Void FinancesClearButton_Click(System::Object^  sender, System::EventArgs^  e) {
					 
			//CLEAR FORM
			FinStoreGainsBox->Clear();
			FinOtherGainsBox->Clear();
			FinStockExpensesBox->Clear();
			FinEmployeeExpensesBox->Clear();
			FinOtherExpensesBox->Clear();
		 }
		 
//////////////////////////////////////////////////
////// FINANCES CLEAR ENTRY BUTTON CLICK /////////
//////////////////////////////////////////////////
private: System::Void FinancesClearEntryButton_Click(System::Object^  sender, System::EventArgs^  e) {

	if (FinancesMonthBox->SelectedIndex >= 0 && FinancesMonthBox->SelectedIndex < 12
		&& FinancesYearBox->SelectedIndex >= 0 && FinancesYearBox->SelectedIndex < NUM_OF_YEARS){
			//CONVERT SELECTION TO STANDARD MONTH/YEAR VALUES
			int month = FinancesMonthBox->SelectedIndex + 1;
			int year = 2006 + FinancesYearBox->SelectedIndex % 12;

			//SHOW CLEAR INFORMATION IN SYSTEM LOG BOX
			SystemLogLabel->Text = ( L"CLEARED-> Finances Entry for " + month.ToString()
					+ L"/" + year.ToString() + "\n\n" + SystemLogLabel->Text);

			//CLEAR ENTRY AND SET TO DEFAULT
			Gain[FinancesMonthBox->SelectedIndex, FinancesYearBox->SelectedIndex]->StoreGains = 0;
			Gain[FinancesMonthBox->SelectedIndex, FinancesYearBox->SelectedIndex]->OtherGains = 0;
			Expense[FinancesMonthBox->SelectedIndex, FinancesYearBox->SelectedIndex]->StockExpense = 0;
			Expense[FinancesMonthBox->SelectedIndex, FinancesYearBox->SelectedIndex]->EmployeeExpense = 0;
			Expense[FinancesMonthBox->SelectedIndex, FinancesYearBox->SelectedIndex]->OtherExpense = 0;
	 
			//CLEAR FORM
			FinStoreGainsBox->Clear();
			FinOtherGainsBox->Clear();
			FinStockExpensesBox->Clear();
			FinEmployeeExpensesBox->Clear();
			FinOtherExpensesBox->Clear();
	}
	else
		MessageBox::Show(L"Invalid Date Selection\nPlease Select A Valid Month And Year", L"Error",
			MessageBoxButtons::OK, MessageBoxIcon::Error );
}
		 
///////////////////////////////////////////////
////// FINANCES VIEW ENTRY BUTTON CLICK ///////
///////////////////////////////////////////////
private: System::Void FinancesViewButton_Click(System::Object^  sender, System::EventArgs^  e) {
		 	
			//CHECK IF SELECTED INDEX IS VALID
			if (FinancesMonthBox->SelectedIndex >= 0 && FinancesMonthBox->SelectedIndex < 12
				&& FinancesYearBox->SelectedIndex >= 0 && FinancesYearBox->SelectedIndex < NUM_OF_YEARS)
			{
				//CONVERT SELECTION TO STANDARD MONTH/YEAR VALUES
				int month = FinancesMonthBox->SelectedIndex + 1;
				int year = 2006 + FinancesYearBox->SelectedIndex % 12;

				//OUTPUT ENTRY INFORMATION TO SYSTEM LOG BOX
				SystemLogLabel->Text = ( L"FINANCIAL REPORT FOR " + month.ToString() + L"/" + year.ToString()
					+ L"\n" + Gain[FinancesMonthBox->SelectedIndex, FinancesYearBox->SelectedIndex]->ToString()
					+ L"\n" + Expense[FinancesMonthBox->SelectedIndex, FinancesYearBox->SelectedIndex]->ToString() + "\n\n" + SystemLogLabel->Text);
			}
	
			//RETURN ERROR IF SELECTED INDEX IS INVALID
			else
				MessageBox::Show(L"Invalid Date Selection\nPlease Select A Valid Month And Year", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );


		 }
		 
///////////////////////////////////////////////////////
//	IMPORTANT:	USE THIS BUTTON CLICK FUNCTION
//				TO OUTPUT ANY DESIRED FINANCIAL
//				INFORMATION FUNCTIONS
///////////////////////////////////////////////////////
private: System::Void FinancesCalculationsButton_Click(System::Object^  sender, System::EventArgs^  e) {
		 
			SystemLogLabel->Text = ( L"INSERT CALCULATIONS AND OTHER NECESSARY INFORMATION IN THIS BUTTON CLICK FUNCTION"
				+ L"\n\n" + SystemLogLabel->Text );
		 }
};
}
