#pragma once

#include "Helpers.h"
#include "Debugger.h"

extern STDebugger* g_STDebugger;

ref class Form1;

namespace CppCLRWinformsSTDebugger 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Preferences : public System::Windows::Forms::Form
	{
	public:
		Preferences(void)
		{
			InitializeComponent();
		}
	private: System::Windows::Forms::ComboBox^ ComPorts;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ BaudRate;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Button^ OKButton;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ComboBox^ ComputerType;
	private: System::Windows::Forms::ComboBox^ SystemMemory;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::ComboBox^ TOSVersion;
	private: System::Windows::Forms::Label^ label5;
	public:

	System::Windows::Forms::Form^ mainWindow = nullptr;
	System::Windows::Forms::ComboBox^ GetComportsList() { return ComPorts; }
	System::Windows::Forms::RichTextBox^ GetSerialPortDescBox() { return SerialPortDesc; }
	System::Windows::Forms::ComboBox^ GetBaudRateList() { return BaudRate; }
	System::Windows::Forms::ComboBox^ GetComputerTypeList() { return ComputerType; }
	System::Windows::Forms::ComboBox^ GetSystemMemoryList() { return SystemMemory; }
	System::Windows::Forms::ComboBox^ GetTosVersionList() { return TOSVersion; }

	u32 SelectedMemoryAmount;
	u32 SelectedTos;
	System::String^ SelectedComputerType;

	u32 SelectedBaudRate;
	System::String^ SelectedComPort;

	private: System::Windows::Forms::TabControl^ PreferencesTabControl;
	public:
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;

	private: System::Windows::Forms::RichTextBox^ SerialPortDesc;


	protected:
		bool	MemoryWindowInsertModeOn = false;

		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Preferences()
		{
			if (components)
			{
				delete components;
			}
		}	
	protected:

	private: System::Windows::Forms::ErrorProvider^ errorProvider2;
	private: System::Windows::Forms::ErrorProvider^ errorProvider1;		
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->errorProvider2 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->PreferencesTabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->BaudRate = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ComPorts = (gcnew System::Windows::Forms::ComboBox());
			this->SerialPortDesc = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->TOSVersion = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->SystemMemory = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ComputerType = (gcnew System::Windows::Forms::ComboBox());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->BeginInit();
			this->PreferencesTabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// errorProvider1
			// 
			this->errorProvider1->ContainerControl = this;
			// 
			// errorProvider2
			// 
			this->errorProvider2->ContainerControl = this;
			// 
			// PreferencesTabControl
			// 
			this->PreferencesTabControl->Controls->Add(this->tabPage1);
			this->PreferencesTabControl->Controls->Add(this->tabPage2);
			this->PreferencesTabControl->Location = System::Drawing::Point(9, 8);
			this->PreferencesTabControl->Margin = System::Windows::Forms::Padding(2);
			this->PreferencesTabControl->Name = L"PreferencesTabControl";
			this->PreferencesTabControl->SelectedIndex = 0;
			this->PreferencesTabControl->Size = System::Drawing::Size(538, 271);
			this->PreferencesTabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->tabPage1->Controls->Add(this->BaudRate);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->ComPorts);
			this->tabPage1->Controls->Add(this->SerialPortDesc);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Margin = System::Windows::Forms::Padding(2);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(2);
			this->tabPage1->Size = System::Drawing::Size(530, 245);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Serial Port";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// BaudRate
			// 
			this->BaudRate->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->BaudRate->FormattingEnabled = true;
			this->BaudRate->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"115200", L"57600", L"38400", L"19200", L"9600",
					L"4800", L"2400"
			});
			this->BaudRate->Location = System::Drawing::Point(338, 41);
			this->BaudRate->Margin = System::Windows::Forms::Padding(2);
			this->BaudRate->Name = L"BaudRate";
			this->BaudRate->Size = System::Drawing::Size(92, 21);
			this->BaudRate->TabIndex = 6;
			this->BaudRate->SelectedIndexChanged += gcnew System::EventHandler(this, &Preferences::BaudRate_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(336, 15);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Baud Rate";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(115, 15);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Description";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 15);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Select COM port";
			// 
			// ComPorts
			// 
			this->ComPorts->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComPorts->FormattingEnabled = true;
			this->ComPorts->Location = System::Drawing::Point(9, 41);
			this->ComPorts->Margin = System::Windows::Forms::Padding(2);
			this->ComPorts->Name = L"ComPorts";
			this->ComPorts->Size = System::Drawing::Size(82, 21);
			this->ComPorts->TabIndex = 2;
			this->ComPorts->SelectedIndexChanged += gcnew System::EventHandler(this, &Preferences::ComPorts_SelectedIndexChanged);
			// 
			// SerialPortDesc
			// 
			this->SerialPortDesc->Location = System::Drawing::Point(115, 41);
			this->SerialPortDesc->Margin = System::Windows::Forms::Padding(2);
			this->SerialPortDesc->Name = L"SerialPortDesc";
			this->SerialPortDesc->ReadOnly = true;
			this->SerialPortDesc->Size = System::Drawing::Size(203, 42);
			this->SerialPortDesc->TabIndex = 1;
			this->SerialPortDesc->Text = L"";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->label6);
			this->tabPage2->Controls->Add(this->TOSVersion);
			this->tabPage2->Controls->Add(this->label5);
			this->tabPage2->Controls->Add(this->SystemMemory);
			this->tabPage2->Controls->Add(this->label4);
			this->tabPage2->Controls->Add(this->ComputerType);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Margin = System::Windows::Forms::Padding(2);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(2);
			this->tabPage2->Size = System::Drawing::Size(530, 245);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Computer";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(19, 77);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(67, 13);
			this->label6->TabIndex = 5;
			this->label6->Text = L"TOS Version";
			// 
			// TOSVersion
			// 
			this->TOSVersion->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TOSVersion->FormattingEnabled = true;
			this->TOSVersion->Items->AddRange(gcnew cli::array< System::Object^  >(15) {
				L"Tos 1.0", L"Tos 1.02", L"Tos 1.04", L"Tos 1.06",
					L"Tos 1.62", L"Tos 2.05", L"Tos 2.06", L"Tos 3.00", L"Tos 3.01", L"Tos 3.05", L"Tos 3.06", L"Tos 4.00", L"Tos 4.01", L"Tos 4.02",
					L"Tos 4.04"
			});
			this->TOSVersion->Location = System::Drawing::Point(22, 93);
			this->TOSVersion->Name = L"TOSVersion";
			this->TOSVersion->Size = System::Drawing::Size(121, 21);
			this->TOSVersion->TabIndex = 4;
			this->TOSVersion->SelectedIndexChanged += gcnew System::EventHandler(this, &Preferences::TOSVersion_SelectedIndexChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(179, 19);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(81, 13);
			this->label5->TabIndex = 3;
			this->label5->Text = L"System Memory";
			// 
			// SystemMemory
			// 
			this->SystemMemory->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SystemMemory->FormattingEnabled = true;
			this->SystemMemory->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"512 KB", L"1 MB", L"2.5 MB", L"4 MB", L"14 MB" });
			this->SystemMemory->Location = System::Drawing::Point(182, 38);
			this->SystemMemory->Name = L"SystemMemory";
			this->SystemMemory->Size = System::Drawing::Size(121, 21);
			this->SystemMemory->TabIndex = 2;
			this->SystemMemory->SelectedIndexChanged += gcnew System::EventHandler(this, &Preferences::SystemMemory_SelectedIndexChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(19, 19);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(79, 13);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Computer Type";
			// 
			// ComputerType
			// 
			this->ComputerType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComputerType->FormattingEnabled = true;
			this->ComputerType->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Atari ST / Mega ST", L"Atari STe", L"Atari TT",
					L"Atari Falcon"
			});
			this->ComputerType->Location = System::Drawing::Point(22, 38);
			this->ComputerType->Name = L"ComputerType";
			this->ComputerType->Size = System::Drawing::Size(121, 21);
			this->ComputerType->TabIndex = 0;
			this->ComputerType->SelectedIndexChanged += gcnew System::EventHandler(this, &Preferences::ComputerType_SelectedIndexChanged);
			// 
			// OKButton
			// 
			this->OKButton->FlatAppearance->BorderColor = System::Drawing::Color::Blue;
			this->OKButton->Location = System::Drawing::Point(414, 300);
			this->OKButton->Margin = System::Windows::Forms::Padding(2);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(61, 29);
			this->OKButton->TabIndex = 7;
			this->OKButton->Text = L"OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &Preferences::OKButton_Click);
			this->OKButton->Enter += gcnew System::EventHandler(this, &Preferences::OKButton_Enter);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(488, 300);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(56, 29);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Cancel";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Preferences::button1_Click);
			// 
			// Preferences
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(557, 339);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->OKButton);
			this->Controls->Add(this->PreferencesTabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"Preferences";
			this->Text = L"Preferences";
			this->Activated += gcnew System::EventHandler(this, &Preferences::Preferences_Activated);
			this->Enter += gcnew System::EventHandler(this, &Preferences::Preferences_Enter);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->EndInit();
			this->PreferencesTabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	   

private: System::Void ComPorts_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
{
	System::Windows::Forms::ComboBox^ cb = (System::Windows::Forms::ComboBox^)sender;
	SelectedComPort = cb->SelectedItem->ToString();
	char* portName = ConvertStringToChar(SelectedComPort);

	// set the new description
	bool foundComPort = false;
	DynArray<ComPort*>& comPorts = g_STDebugger->GetComPortsArray();
	for (s32 i = 0; i < comPorts.Count(); i++)
	{
		if (comPorts[i]->PortName == portName)
		{
			SerialPortDesc->Text = ConvertCharToString(comPorts[i]->PortDescription.GetPtr());
			foundComPort = true;
			break;
		}
	}

	if (!foundComPort)
	{
		SerialPortDesc->Text = "";
	}
}
private: System::Void BaudRate_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
{
	System::Windows::Forms::ComboBox^ cb = (System::Windows::Forms::ComboBox^)sender;
	char* baud = ConvertStringToChar(cb->SelectedItem->ToString());
	SelectedBaudRate = atoi(baud);
}

// OK
private: System::Void OKButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	// send values to the debugger
	g_STDebugger->SetBaudRate(SelectedBaudRate);
	char* portName = ConvertStringToChar(SelectedComPort);
	g_STDebugger->SetComPortName(portName);
	g_STDebugger->ClearMainWindowPreferencesReference();
	g_STDebugger->WriteIniFile();
	Close();
}
private: System::Void OKButton_Enter(System::Object^ sender, System::EventArgs^ e) 
{

}

private: System::Void Preferences_Activated(System::Object^ sender, System::EventArgs^ e) 
{
}
	   
private: System::Void Preferences_Enter(System::Object^ sender, System::EventArgs^ e) 
{
}

// cancel
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	g_STDebugger->ClearMainWindowPreferencesReference();
	Close();
}
// computer type
private: System::Void ComputerType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
{
	System::Windows::Forms::ComboBox^ cb = (System::Windows::Forms::ComboBox^)sender;
	System::String^ computerType = cb->SelectedItem->ToString();
	SelectedComputerType = computerType;

	if (computerType == "Atari ST / Mega ST")
	{
		g_STDebugger->SetComputerType(COMPUTER_TYPE_ATARI_ST);
	}
	else if (computerType == "Atari STe")
	{
		g_STDebugger->SetComputerType(COMPUTER_TYPE_ATARI_STE);
	}
	else if (computerType == "Atari TT")
	{
		g_STDebugger->SetComputerType(COMPUTER_TYPE_ATARI_TT);
	}
	else if (computerType == "Atari Falcon")
	{
		g_STDebugger->SetComputerType(COMPUTER_TYPE_ATARI_FALCON);
	}
}
// system memory
private: System::Void SystemMemory_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
{
	System::Windows::Forms::ComboBox^ cb = (System::Windows::Forms::ComboBox^)sender;
	System::String^ memSelected = cb->SelectedItem->ToString();

	if (memSelected == "512 KB")
	{
		SelectedMemoryAmount = ATARI_520ST_MEMORY;
	}
	else if (memSelected == "1 MB")
	{
		SelectedMemoryAmount = ATARI_1040ST_MEMORY;
	}
	else if (memSelected == "2.5 MB")
	{
		SelectedMemoryAmount = ATARI_ST_MID_MEMORY;
	}
	else if (memSelected == "4 MB")
	{
		SelectedMemoryAmount = ATARI_ST_MAX_MEMORY;
	}
	else if (memSelected == "14 MB")
	{
		SelectedMemoryAmount = ATARI_FALCON_MAX_MEMORY;
	}
	g_STDebugger->SetSystemMemory(SelectedMemoryAmount);
}

// tos version
private: System::Void TOSVersion_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
{
	System::Windows::Forms::ComboBox^ cb = (System::Windows::Forms::ComboBox^)sender;
	System::String^ tosVersion = cb->SelectedItem->ToString();

	if (tosVersion == "Tos 1.0")
	{
		SelectedTos = 100;
	}
	else if (tosVersion == "Tos 1.02")
	{
		SelectedTos = 102;
	}
	else if (tosVersion == "Tos 1.04")
	{
		SelectedTos = 104;
	}
	else if (tosVersion == "Tos 1.06")
	{
		SelectedTos = 106;
	}
	else if (tosVersion == "Tos 1.62")
	{
		SelectedTos = 162;
	}
	else if (tosVersion == "Tos 2.05")
	{
		SelectedTos = 205;
	}
	else if (tosVersion == "Tos 2.06")
	{
		SelectedTos = 206;
	}
	else if (tosVersion == "Tos 3.00")
	{
		SelectedTos = 300;
	}
	else if (tosVersion == "Tos 3.01")
	{
		SelectedTos = 301;
	}
	else if (tosVersion == "Tos 3.05")
	{
		SelectedTos = 305;
	}
	else if (tosVersion == "Tos 3.06")
	{
		SelectedTos = 306;
	}
	else if (tosVersion == "Tos 4.00")
	{
		SelectedTos = 400;
	}
	else if (tosVersion == "Tos 4.01")
	{
		SelectedTos = 401;
	}
	else if (tosVersion == "Tos 4.02")
	{
		SelectedTos = 402;
	}
	else if (tosVersion == "Tos 4.04")
	{
		SelectedTos = 404;
	}

	g_STDebugger->SetTosVersion(SelectedTos);
}
};
}
