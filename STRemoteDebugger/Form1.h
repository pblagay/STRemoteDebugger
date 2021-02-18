#pragma once

#include "Debugger.h"
#include "Helpers.h"

extern STDebugger* g_STDebugger;

namespace CppCLRWinformsSTDebugger {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			void* thisPtr = System::Runtime::InteropServices::GCHandle::ToIntPtr(System::Runtime::InteropServices::GCHandle::Alloc(this)).ToPointer();
			g_STDebugger->Init(thisPtr);
		}

		System::Windows::Forms::RichTextBox^ GetRegisterWindow() { return RegisterWindow; }
		System::Windows::Forms::RichTextBox^ GetAssemblyWindow() { return AssemblyWindow; }
		System::Windows::Forms::RichTextBox^ GetSourceWindow() { return SourceCodeWindow; }
		System::Windows::Forms::RichTextBox^ GetMemoryWindow() { return MemoryWindow; }

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			g_STDebugger->Shutdown();
			if (components)
			{
				delete components;
			}
		
		}	
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ quitToolStripMenuItem;
	private: System::Windows::Forms::RichTextBox^ SourceCodeWindow;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RichTextBox^ RegisterWindow;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::RichTextBox^ MemoryWindow;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^ preferencesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
	private: System::Windows::Forms::RichTextBox^ AssemblyWindow;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;	
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::RichTextBox^ AsciiBox;

	private: System::Windows::Forms::ErrorProvider^ errorProvider1;		
	private: System::Windows::Forms::RichTextBox^ AsciiWindow;
//	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->preferencesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->quitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SourceCodeWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->RegisterWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->MemoryWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->AssemblyWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->AsciiBox = (gcnew System::Windows::Forms::RichTextBox());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1738, 35);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->openToolStripMenuItem,
					this->preferencesToolStripMenuItem, this->toolStripSeparator1, this->quitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(54, 29);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(204, 34);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// preferencesToolStripMenuItem
			// 
			this->preferencesToolStripMenuItem->Name = L"preferencesToolStripMenuItem";
			this->preferencesToolStripMenuItem->Size = System::Drawing::Size(204, 34);
			this->preferencesToolStripMenuItem->Text = L"Preferences";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(201, 6);
			// 
			// quitToolStripMenuItem
			// 
			this->quitToolStripMenuItem->Name = L"quitToolStripMenuItem";
			this->quitToolStripMenuItem->Size = System::Drawing::Size(204, 34);
			this->quitToolStripMenuItem->Text = L"Quit";
			// 
			// SourceCodeWindow
			// 
			this->SourceCodeWindow->Location = System::Drawing::Point(612, 132);
			this->SourceCodeWindow->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->SourceCodeWindow->Name = L"SourceCodeWindow";
			this->SourceCodeWindow->ReadOnly = true;
			this->SourceCodeWindow->Size = System::Drawing::Size(546, 755);
			this->SourceCodeWindow->TabIndex = 1;
			this->SourceCodeWindow->Text = L"";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(604, 89);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 25);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Source Code";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(1176, 89);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(93, 25);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Registers";
			// 
			// RegisterWindow
			// 
			this->RegisterWindow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RegisterWindow->Location = System::Drawing::Point(1184, 132);
			this->RegisterWindow->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->RegisterWindow->Name = L"RegisterWindow";
			this->RegisterWindow->ReadOnly = true;
			this->RegisterWindow->Size = System::Drawing::Size(534, 209);
			this->RegisterWindow->TabIndex = 4;
			this->RegisterWindow->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(18, 951);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(83, 25);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Memory";
			// 
			// MemoryWindow
			// 
			this->MemoryWindow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->MemoryWindow->Location = System::Drawing::Point(18, 1038);
			this->MemoryWindow->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->MemoryWindow->Name = L"MemoryWindow";
			this->MemoryWindow->Size = System::Drawing::Size(942, 216);
			this->MemoryWindow->TabIndex = 6;
			this->MemoryWindow->Text = L"";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->richTextBox1->Location = System::Drawing::Point(18, 994);
			this->richTextBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(319, 33);
			this->richTextBox1->TabIndex = 7;
			this->richTextBox1->Text = L"0x00000000";
			// 
			// AssemblyWindow
			// 
			this->AssemblyWindow->Location = System::Drawing::Point(48, 132);
			this->AssemblyWindow->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->AssemblyWindow->Name = L"AssemblyWindow";
			this->AssemblyWindow->ReadOnly = true;
			this->AssemblyWindow->Size = System::Drawing::Size(546, 755);
			this->AssemblyWindow->TabIndex = 8;
			this->AssemblyWindow->Text = L"";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(40, 89);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(98, 25);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Assembly";
			// 
			// errorProvider1
			// 
			this->errorProvider1->ContainerControl = this;
			// 
			// AsciiBox
			// 
			this->AsciiBox->Location = System::Drawing::Point(1008, 1038);
			this->AsciiBox->Name = L"AsciiBox";
			this->AsciiBox->Size = System::Drawing::Size(710, 225);
			this->AsciiBox->TabIndex = 10;
			this->AsciiBox->Text = L"";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1738, 1275);
			this->Controls->Add(this->AsciiBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->AssemblyWindow);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->MemoryWindow);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->RegisterWindow);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->SourceCodeWindow);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"Form1";
			this->Text = L"Atari ST Remote Debugger";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		// show file dialog
		openFileDialog1->Title = "Load ST Executable";
		openFileDialog1->Filter = "ST files (*.prg;*.acc)|*.prg;*.acc";
		openFileDialog1->FilterIndex = 1;
		openFileDialog1->FileName = L"";
		openFileDialog1->Multiselect = false;
		openFileDialog1->InitialDirectory = L"";	// ConvertCharToString(g_Editor->m_IniSettings.m_ScenePath.Get());

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			int FilenameLength = openFileDialog1->FileName->Length + 2;
			WCHAR* filenameBuffer = new WCHAR[FilenameLength];
			memset(filenameBuffer, 0, FilenameLength);
			ConvertStringToLChar(openFileDialog1->FileName, *filenameBuffer);
			g_STDebugger->LoadExecutable(filenameBuffer);
		}
	}
};
}
