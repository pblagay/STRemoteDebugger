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
	public ref class DialogTextInput : public System::Windows::Forms::Form
	{
	public:
		DialogTextInput(void)
		{
			InitializeComponent();
		}
	public: System::Windows::Forms::Label^ TextBoxTitle;
	public: System::Windows::Forms::TextBox^ TextInputField;

	public: System::Windows::Forms::Button^ button2;
	public: System::Windows::Forms::Button^ button1;

	public:
	System::Windows::Forms::Form^ mainWindow = nullptr;
	System::Windows::Forms::RichTextBox^ memoryWindow = nullptr;
	u32 startIndex = 0;
	u32 endIndex = 0;
//	private: System::Void DoSearch();
	
	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~DialogTextInput()
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
			this->button1->Location = System::Drawing::Point(271, 46);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 31);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Find";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DialogTextInput::DoSearch);
			// 
			// button2
			// 
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Location = System::Drawing::Point(271, 116);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 31);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// TextInputField
			// 
			this->TextInputField->Location = System::Drawing::Point(39, 48);
			this->TextInputField->Name = L"TextInputField";
			this->TextInputField->Size = System::Drawing::Size(203, 26);
			this->TextInputField->TabIndex = 2;
			this->TextInputField->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &DialogTextInput::TextInputField_KeyDown);
			// 
			// TextBoxTitle
			// 
			this->TextBoxTitle->AutoSize = true;
			this->TextBoxTitle->Location = System::Drawing::Point(35, 25);
			this->TextBoxTitle->Name = L"TextBoxTitle";
			this->TextBoxTitle->Size = System::Drawing::Size(40, 20);
			this->TextBoxTitle->TabIndex = 3;
			this->TextBoxTitle->Text = L"Find";
			// 
			// DialogTextInput
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(367, 160);
			this->Controls->Add(this->TextBoxTitle);
			this->Controls->Add(this->TextInputField);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"DialogTextInput";
			this->Text = L"DialogTextInput";
			this->Shown += gcnew System::EventHandler(this, &DialogTextInput::DialogTextInput_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void DialogTextInput_Shown(System::Object^ sender, System::EventArgs^ e) 
{
	TextInputField->Select();
	startIndex = 0;
	endIndex = memoryWindow->Text->Length;
}

private: System::Void DoSearch(System::Object^ sender, System::EventArgs^ e)
{
	s32 index = memoryWindow->Find(TextInputField->Text, startIndex, endIndex, System::Windows::Forms::RichTextBoxFinds::None);
	if (index != -1)
	{
		memoryWindow->Select(index, TextInputField->TextLength);
		startIndex = index;
	}
	DialogResult = System::Windows::Forms::DialogResult::OK;
	Close();
}

private: System::Void TextInputField_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) 
{
	if (e->KeyCode == Keys::Enter)
	{
		DoSearch(nullptr, nullptr);
	}
}
};
}
