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
	public ref class DialogAddressTextInput : public System::Windows::Forms::Form
	{
	public:
		DialogAddressTextInput(void)
		{
			InitializeComponent();
		}
	public: System::Windows::Forms::Label^ TextBoxTitle;
	public: System::Windows::Forms::TextBox^ TextInputField;

	public: System::Windows::Forms::Button^ button2;
	public: System::Windows::Forms::Button^ button1;

	public:
	System::Windows::Forms::Form^ mainWindow = nullptr;
	System::Windows::Forms::RichTextBox^ searchWindow = nullptr;
	public: System::Windows::Forms::Label^ AddressBoxTitle;
	public: System::Windows::Forms::Label^ SizeTitle;
	public: System::Windows::Forms::TextBox^ SizeInputField;
	public: System::Windows::Forms::TextBox^ AddressInputField;

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~DialogAddressTextInput()
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->TextInputField = (gcnew System::Windows::Forms::TextBox());
			this->TextBoxTitle = (gcnew System::Windows::Forms::Label());
			this->AddressBoxTitle = (gcnew System::Windows::Forms::Label());
			this->AddressInputField = (gcnew System::Windows::Forms::TextBox());
			this->SizeTitle = (gcnew System::Windows::Forms::Label());
			this->SizeInputField = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->BeginInit();
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
			// button1
			// 
			this->button1->Location = System::Drawing::Point(290, 46);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 31);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Fill";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DialogAddressTextInput::DoSearch);
			// 
			// button2
			// 
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Location = System::Drawing::Point(290, 241);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 31);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// TextInputField
			// 
			this->TextInputField->Location = System::Drawing::Point(35, 116);
			this->TextInputField->Name = L"TextInputField";
			this->TextInputField->Size = System::Drawing::Size(203, 26);
			this->TextInputField->TabIndex = 2;
			this->TextInputField->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &DialogAddressTextInput::TextInputField_KeyDown);
			// 
			// TextBoxTitle
			// 
			this->TextBoxTitle->AutoSize = true;
			this->TextBoxTitle->Location = System::Drawing::Point(31, 93);
			this->TextBoxTitle->Name = L"TextBoxTitle";
			this->TextBoxTitle->Size = System::Drawing::Size(50, 20);
			this->TextBoxTitle->TabIndex = 3;
			this->TextBoxTitle->Text = L"Value";
			// 
			// AddressBoxTitle
			// 
			this->AddressBoxTitle->AutoSize = true;
			this->AddressBoxTitle->Location = System::Drawing::Point(31, 28);
			this->AddressBoxTitle->Name = L"AddressBoxTitle";
			this->AddressBoxTitle->Size = System::Drawing::Size(68, 20);
			this->AddressBoxTitle->TabIndex = 5;
			this->AddressBoxTitle->Text = L"Address";
			// 
			// AddressInputField
			// 
			this->AddressInputField->Location = System::Drawing::Point(35, 51);
			this->AddressInputField->Name = L"AddressInputField";
			this->AddressInputField->Size = System::Drawing::Size(203, 26);
			this->AddressInputField->TabIndex = 4;
			// 
			// SizeTitle
			// 
			this->SizeTitle->AutoSize = true;
			this->SizeTitle->Location = System::Drawing::Point(31, 159);
			this->SizeTitle->Name = L"SizeTitle";
			this->SizeTitle->Size = System::Drawing::Size(40, 20);
			this->SizeTitle->TabIndex = 7;
			this->SizeTitle->Text = L"Size";
			// 
			// SizeInputField
			// 
			this->SizeInputField->Location = System::Drawing::Point(35, 182);
			this->SizeInputField->Name = L"SizeInputField";
			this->SizeInputField->Size = System::Drawing::Size(203, 26);
			this->SizeInputField->TabIndex = 6;
			// 
			// DialogAddressTextInput
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(377, 284);
			this->Controls->Add(this->SizeTitle);
			this->Controls->Add(this->SizeInputField);
			this->Controls->Add(this->AddressBoxTitle);
			this->Controls->Add(this->AddressInputField);
			this->Controls->Add(this->TextBoxTitle);
			this->Controls->Add(this->TextInputField);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"DialogAddressTextInput";
			this->Text = L"DialogAddressTextInput";
			this->Shown += gcnew System::EventHandler(this, &DialogAddressTextInput::DialogTextInput_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void DialogTextInput_Shown(System::Object^ sender, System::EventArgs^ e) 
{
	AddressInputField->Select();
}

private: System::Void DoSearch(System::Object^ sender, System::EventArgs^ e)
{
	DialogResult = System::Windows::Forms::DialogResult::OK;
	Close();
}

private: System::Void TextInputField_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) 
{
	if (e->KeyCode == Keys::Enter)
	{
	}
}

};
}
