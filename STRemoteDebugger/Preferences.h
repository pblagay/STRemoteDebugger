#pragma once

#include "Helpers.h"
#include "Debugger.h"

extern STDebugger* g_STDebugger;

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
	public:

	System::Windows::Forms::Form^ mainWindow = nullptr;
	System::Windows::Forms::ComboBox^ GetComportsList() { return ComPorts; }
	System::Windows::Forms::RichTextBox^ GetSerialPortDescBox() { return SerialPortDesc; }
	System::Windows::Forms::ComboBox^ GetBaudRateList() { return BaudRate; }


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ComPorts = (gcnew System::Windows::Forms::ComboBox());
			this->SerialPortDesc = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->BaudRate = (gcnew System::Windows::Forms::ComboBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->BeginInit();
			this->PreferencesTabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
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
			this->PreferencesTabControl->Location = System::Drawing::Point(12, 10);
			this->PreferencesTabControl->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->PreferencesTabControl->Name = L"PreferencesTabControl";
			this->PreferencesTabControl->SelectedIndex = 0;
			this->PreferencesTabControl->Size = System::Drawing::Size(718, 334);
			this->PreferencesTabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->BaudRate);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->ComPorts);
			this->tabPage1->Controls->Add(this->SerialPortDesc);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabPage1->Size = System::Drawing::Size(710, 305);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Serial Port";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(111, 17);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Select COM port";
			// 
			// ComPorts
			// 
			this->ComPorts->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComPorts->FormattingEnabled = true;
			this->ComPorts->Location = System::Drawing::Point(12, 50);
			this->ComPorts->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->ComPorts->Name = L"ComPorts";
			this->ComPorts->Size = System::Drawing::Size(108, 24);
			this->ComPorts->TabIndex = 2;
			// 
			// SerialPortDesc
			// 
			this->SerialPortDesc->Location = System::Drawing::Point(153, 50);
			this->SerialPortDesc->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->SerialPortDesc->Name = L"SerialPortDesc";
			this->SerialPortDesc->ReadOnly = true;
			this->SerialPortDesc->Size = System::Drawing::Size(269, 51);
			this->SerialPortDesc->TabIndex = 1;
			this->SerialPortDesc->Text = L"";
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tabPage2->Size = System::Drawing::Size(710, 305);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Options";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(153, 18);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(79, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Description";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(448, 18);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(75, 17);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Baud Rate";
			// 
			// BaudRate
			// 
			this->BaudRate->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->BaudRate->FormattingEnabled = true;
			this->BaudRate->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"115200", L"57600", L"38400", L"19200", L"9600",
					L"4800", L"2400"
			});
			this->BaudRate->Location = System::Drawing::Point(451, 50);
			this->BaudRate->Name = L"BaudRate";
			this->BaudRate->Size = System::Drawing::Size(121, 24);
			this->BaudRate->TabIndex = 6;
			// 
			// Preferences
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(740, 346);
			this->Controls->Add(this->PreferencesTabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"Preferences";
			this->Text = L"Preferences";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->EndInit();
			this->PreferencesTabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	   

};
}
