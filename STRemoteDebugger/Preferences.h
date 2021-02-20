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
	public:

	System::Windows::Forms::Form^ mainWindow = nullptr;
	System::Windows::Forms::ComboBox^ GetComportsList() { return ComPorts; }
	System::Windows::Forms::RichTextBox^ GetSerialPortDescBox() { return SerialPortDesc; }


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
			this->ComPorts = (gcnew System::Windows::Forms::ComboBox());
			this->SerialPortDesc = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label1 = (gcnew System::Windows::Forms::Label());
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
			this->PreferencesTabControl->Location = System::Drawing::Point(13, 13);
			this->PreferencesTabControl->Name = L"PreferencesTabControl";
			this->PreferencesTabControl->SelectedIndex = 0;
			this->PreferencesTabControl->Size = System::Drawing::Size(808, 417);
			this->PreferencesTabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->ComPorts);
			this->tabPage1->Controls->Add(this->SerialPortDesc);
			this->tabPage1->Location = System::Drawing::Point(4, 29);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(800, 384);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Serial Port";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// ComPorts
			// 
			this->ComPorts->FormattingEnabled = true;
			this->ComPorts->Location = System::Drawing::Point(14, 62);
			this->ComPorts->Name = L"ComPorts";
			this->ComPorts->Size = System::Drawing::Size(121, 28);
			this->ComPorts->TabIndex = 2;
			// 
			// SerialPortDesc
			// 
			this->SerialPortDesc->Location = System::Drawing::Point(172, 62);
			this->SerialPortDesc->Name = L"SerialPortDesc";
			this->SerialPortDesc->ReadOnly = true;
			this->SerialPortDesc->Size = System::Drawing::Size(302, 63);
			this->SerialPortDesc->TabIndex = 1;
			this->SerialPortDesc->Text = L"";
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 29);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(800, 384);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Options";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(14, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(126, 20);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Select COM port";
			// 
			// Preferences
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(833, 433);
			this->Controls->Add(this->PreferencesTabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
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
