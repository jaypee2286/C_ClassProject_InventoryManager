// MainProject.h
// Main Parent Form

#pragma once
#include "ChildUI.h"

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
#define GAINS_ARRAY_SIZE (NUM_OF_MONTHS * 2)
#define EXPENSES_ARRAY_SIZE (NUM_OF_MONTHS * 3)
#define FINANCES_ARRAY_SIZE (NUM_OF_MONTHS * (GAINS_ARRAY_SIZE + EXPENSES_ARRAY_SIZE))

namespace PROJECTGUITEMPLATE {
	/*
	Main Project GUI Form
	Includes a Menu Strip
	*/
	public ref class MainProject : public System::Windows::Forms::Form
	{
	public:
		MainProject(void)
		{
			ChildUI::Directory = Directory::GetCurrentDirectory();
			InitializeComponent();
			saveAsToolStripMenuItem->Enabled = false;
		}

	protected:
		~MainProject()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  closeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;

	private: static ConsoleGames ^InvTest = gcnew ConsoleGames();	//allocate InvTest
	private: static StorageWorker ^EmpTest = gcnew StorageWorker();	//allocate EmpTest
	private: static Gains ^GainTest = gcnew Gains();				//allocate GainTest
	private: static Expenses ^ExpenseTest = gcnew Expenses();		//allocate ExpenseTest
	private: static FileStream ^fileInput;							//filstream for input
	private: static FileStream ^fileOutput;							//filestream for output
	private: static BinaryWriter ^binaryOutput;						//binarywriter to output to file
	private: static BinaryReader ^binaryInput;						//binaryreader to read a file
	private: static String ^fileName;								//used for file directory
	private: static String ^Directory;								//used for image directory

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->closeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(714, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->newToolStripMenuItem, 
				this->openToolStripMenuItem, this->toolStripSeparator2, this->closeToolStripMenuItem, this->toolStripSeparator3, this->saveAsToolStripMenuItem, 
				this->toolStripSeparator1, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(116, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainProject::newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(116, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainProject::openToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(113, 6);
			// 
			// closeToolStripMenuItem
			// 
			this->closeToolStripMenuItem->Name = L"closeToolStripMenuItem";
			this->closeToolStripMenuItem->Size = System::Drawing::Size(116, 22);
			this->closeToolStripMenuItem->Text = L"Close";
			this->closeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainProject::closeToolStripMenuItem_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(113, 6);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(116, 22);
			this->saveAsToolStripMenuItem->Text = L"Save...";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainProject::saveAsToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(113, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(116, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainProject::exitToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(46, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainProject::aboutToolStripMenuItem_Click);
			// 
			// MainProject
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(714, 469);
			this->Controls->Add(this->menuStrip1);
			this->IsMdiContainer = true;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(722, 500);
			this->MinimumSize = System::Drawing::Size(722, 500);
			this->Name = L"MainProject";
			this->Text = L"Organizer";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
// FILE-OPEN CLICKED
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

				//OPENS A FILE-SELECT BOX AND SETS A FILENAME AND LOCATION
				OpenFileDialog ^fileChooser = gcnew OpenFileDialog();
				Windows::Forms::DialogResult result = fileChooser->ShowDialog();

				fileName = fileChooser->FileName;

				if ( result == System::Windows::Forms::DialogResult::Cancel )
					return;

				//TEST IF SELECTED FILE IS VALID
				//SIZES WILL NOT MATCH IN INVALID FILES
				try
				{					
					fileInput = gcnew FileStream( fileName, FileMode::Open, FileAccess::Read );
					binaryInput = gcnew BinaryReader( fileInput );

					for (int i = 0; i < NUM_OF_PRODUCTS; i++)
					{					
						fileInput->Seek( i * ConsoleGames::SIZE, SeekOrigin::Begin );

						InvTest->ID = binaryInput->ReadInt32();
						InvTest->Name = binaryInput->ReadString();
						InvTest->Platform = binaryInput->ReadString();
						InvTest->Revenue = binaryInput->ReadDouble();
						InvTest->CostOfSale = binaryInput->ReadDouble();
						InvTest->CurrentStock = binaryInput->ReadInt32();
					}

					//READ EMPLOYEE ITEMS
					for ( int j = 0; j < NUM_OF_EMPLOYEES; j++)
					{
						fileInput->Seek((NUM_OF_PRODUCTS) * ConsoleGames::SIZE + j * Employee::SIZE,
							SeekOrigin::Begin);

						EmpTest->ID = binaryInput->ReadInt32();
						EmpTest->FirstName = binaryInput->ReadString();
						EmpTest->LastName = binaryInput->ReadString();
						EmpTest->HoursWorked = binaryInput->ReadInt32();
					}

					//READ FINANCE ITEMS
					for ( int k = 0; k < 12; k++ )
					{
						fileInput->Seek((NUM_OF_PRODUCTS) * ConsoleGames::SIZE + (NUM_OF_EMPLOYEES) * Employee::SIZE
							+ k * (Gains::SIZE + Expenses::SIZE), SeekOrigin::Begin);

						for ( int l = 0; l < NUM_OF_YEARS; l++ )
						{						
							GainTest->StoreGains = binaryInput->ReadDouble();
							GainTest->OtherGains = binaryInput->ReadDouble();
							ExpenseTest->StockExpense = binaryInput->ReadDouble();
							ExpenseTest->EmployeeExpense = binaryInput->ReadDouble();
							ExpenseTest->OtherExpense = binaryInput->ReadDouble();
						}
					}

					//CHECK IF A FILENAME WAS CORRECTLY INPUTTED
					if ( fileName->Equals( L"") )
						MessageBox::Show( L"Invalid File Name", L"Error",
						MessageBoxButtons::OK, MessageBoxIcon::Error );

					else
					{	
						while (MainProject::ActiveMdiChild::get())
						{
							MainProject::ActiveMdiChild->Close();
						}
						saveAsToolStripMenuItem->Enabled = true;
		 				ChildUI ^formChild = gcnew ChildUI( fileName, 0 );
						formChild->MdiParent = this;
						formChild->Show();
					}
					fileInput->Close();
					binaryInput->Close();
				}
	
				//CLOSE FILESTREAM AND RETURN AN ERROR IF FILE IS INVALID
				catch (IOException ^ )
				{
					MessageBox::Show( L"Invalid File", L"Error",
						MessageBoxButtons::OK, MessageBoxIcon::Error );
					fileInput->Close();
					binaryInput->Close();
				}
		}

// FILE-NEW CLICKED
private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			
				//create BLANK DEFAULT objects to write to file
				ConsoleGames ^FileList1 = gcnew ConsoleGames();
				Employee ^FileList2 = gcnew Employee();
				Manager ^FileList3 = gcnew Manager();
				FileList2 = FileList3;
				Gains ^FileList4 = gcnew Gains();
				Expenses ^FileList5 = gcnew Expenses();

				//OPEN FILESTREAM AND SELECT FILENAME
				System::IO::FileStream ^fileOutput;
				BinaryWriter ^binaryOutput;		
				SaveFileDialog ^fileChooser = gcnew SaveFileDialog();
				Windows::Forms::DialogResult result = fileChooser->ShowDialog();
				fileName = fileChooser->FileName;

				if ( result == System::Windows::Forms::DialogResult::Cancel )
					return;

				//CHECK IF FILENAME WAS INPUTTED CORRECTLY
				if ( fileName->Equals( L"" ) )
					MessageBox::Show( L"Invalid File Name", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );

				//WRITE BLANKS TO FILE
				else
				{
					try
					{
						//OPENS AN OUTPUT FILESTREAM
						fileOutput = gcnew FileStream ( fileName, FileMode::Create,
							FileAccess::Write );
						fileOutput->SetLength( 
							ConsoleGames::SIZE * NUM_OF_PRODUCTS + 
							Employee::SIZE * NUM_OF_EMPLOYEES + 
							(Gains::SIZE + Expenses::SIZE ) * NUM_OF_MONTHS);

						binaryOutput = gcnew BinaryWriter( fileOutput );

						//WRITE ALLOCATION FOR INVENTORY ITEMS
						for ( int i = 0; i < NUM_OF_PRODUCTS; i++ )
						{
							fileOutput->Position = i * ConsoleGames::SIZE;

							binaryOutput->Write( FileList1->ID );
							binaryOutput->Write( FileList1->Name );
							binaryOutput->Write( FileList1->Platform );
							binaryOutput->Write( FileList1->Revenue );
							binaryOutput->Write( FileList1->CostOfSale );
							binaryOutput->Write( FileList1->CurrentStock );
						}

						//WRITE ALLOCATION FOR MANAGER ITEMS
						for ( int j = 0; j < NUM_OF_EMPLOYEES; j++)
						{
							fileOutput->Position = (NUM_OF_PRODUCTS) * ConsoleGames::SIZE + j * Employee::SIZE ;
							binaryOutput->Write( FileList2->ID );
							binaryOutput->Write( FileList2->FirstName );
							binaryOutput->Write( FileList2->LastName );
							binaryOutput->Write( FileList2->HoursWorked );
						}

						//WRITE ALLOCATION FOR FINANCE ITEMS
						for ( int l = 0; l < FINANCES_ARRAY_SIZE; l++ )
						{
							fileOutput->Position = (NUM_OF_PRODUCTS) * ConsoleGames::SIZE + (NUM_OF_EMPLOYEES) * Employee::SIZE
								+ l * (Gains::SIZE + Expenses::SIZE) ;

							binaryOutput->Write( FileList4->StoreGains );
							binaryOutput->Write( FileList4->OtherGains );
							binaryOutput->Write( FileList5->StockExpense );
							binaryOutput->Write( FileList5->EmployeeExpense );
							binaryOutput->Write( FileList5->OtherExpense );
						}

						MessageBox::Show( L"File Created", L"Success",
							MessageBoxButtons::OK, MessageBoxIcon::Information );
						fileOutput->Close();
						binaryOutput->Close();
					}

					//CLOSE FILESTREAM AND RETURN AN ERROR IF FILE CANNOT BE WRITTEN
					catch (IOException ^fileException )
					{
						MessageBox::Show( fileException->Message, L"Error",
							MessageBoxButtons::OK, MessageBoxIcon::Error );
						fileOutput->Close();
						binaryOutput->Close();
					}

					//CLOSE ANY PREVIOUS FILES BEFORE OPENING NEW CHILD WINDOW
					while (MainProject::ActiveMdiChild::get())
					{
						MainProject::ActiveMdiChild->Close();
					}
					
					saveAsToolStripMenuItem->Enabled = true;
					ChildUI ^formChild = gcnew ChildUI( fileName );
					formChild->MdiParent = this;
					formChild->Show();
					}
		 }

//FILE-CLOSE CLICKED
//CLOSES CURRENT FILE
private: System::Void closeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			while (MainProject::ActiveMdiChild::get())
			{
				MainProject::ActiveMdiChild->Close();
			}
			saveAsToolStripMenuItem->Enabled = false;
		 }

//FILE-SAVE CLICKED
//SAVES CURRENT FILE
private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				
			fileOutput = gcnew FileStream( fileName, FileMode::Open, FileAccess::Write );
			binaryOutput = gcnew BinaryWriter( fileOutput );

			try
			{
				//WRITES INVENTORY ITEMS
				for ( int i = 0; i < NUM_OF_PRODUCTS; i++ )
				{
					fileOutput->Seek( i * ConsoleGames::SIZE, SeekOrigin::Begin );
					binaryOutput->Write( i+1 );
					binaryOutput->Write( ChildUI::Inv[i]->Name );
					binaryOutput->Write( ChildUI::Inv[i]->Platform );
					binaryOutput->Write( ChildUI::Inv[i]->Revenue );
					binaryOutput->Write( ChildUI::Inv[i]->CostOfSale );
					binaryOutput->Write( ChildUI::Inv[i]->CurrentStock );
				}

				//WRITES EMPLOYEE ITEMS
				for ( int j = 0; j < NUM_OF_EMPLOYEES; j++)
				{
					fileOutput->Position = (NUM_OF_PRODUCTS) * ConsoleGames::SIZE + j * Employee::SIZE ;
					binaryOutput->Write( ChildUI::Emp[j]->ID );
					binaryOutput->Write( ChildUI::Emp[j]->FirstName );
					binaryOutput->Write( ChildUI::Emp[j]->LastName );
					binaryOutput->Write( ChildUI::Emp[j]->HoursWorked );
				}

				//WRITES FINANCE ITEMS
				for ( int k = 0; k < 12; k++ )
				{
					fileOutput->Position = (NUM_OF_PRODUCTS) * ConsoleGames::SIZE + (NUM_OF_EMPLOYEES) * Employee::SIZE
						+ k * 12 * (Gains::SIZE + Expenses::SIZE) ;

					for ( int l = 0; l < NUM_OF_YEARS; l++ )
					{
						binaryOutput->Write( ChildUI::Gain[k, l]->StoreGains );
						binaryOutput->Write( ChildUI::Gain[k, l]->OtherGains );
						binaryOutput->Write( ChildUI::Expense[k, l]->StockExpense );
						binaryOutput->Write( ChildUI::Expense[k, l]->EmployeeExpense );
						binaryOutput->Write( ChildUI::Expense[k, l]->OtherExpense );
					}
				}
			}

			//RETURN ERROR IF FILE CANNOT BE WRITTEN
			catch (FormatException ^ )
			{
				MessageBox::Show( L"File Does Not Exist", L"Error",
					MessageBoxButtons::OK, MessageBoxIcon::Error );
				return;
			}

			//CLOSE FILESTREAMS
			fileOutput->Close();
			binaryOutput->Close();
		 }

//FILE-EXIT CLICKED
//EXITS THE PROGRAM
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Application::Exit();
		 }

//HELP-ABOUT CLICKED
//RETURNS INFORMATION ON PROGRAM
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

			 MessageBox::Show( L"Cal Poly Pomona ECE256\nSmall Business Organizer Project\nby Nathaniel Allen & John Paul Canlas", L"About...",
				 MessageBoxButtons::OK, MessageBoxIcon::Information );
		 }
};
}

