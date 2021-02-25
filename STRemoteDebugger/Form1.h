//#pragma once

#include "Debugger.h"
#include "Helpers.h"
#include "Preferences.h"

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
	/// Zusammenfassung f�r Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			void* thisPtr = System::Runtime::InteropServices::GCHandle::ToIntPtr(System::Runtime::InteropServices::GCHandle::Alloc(this)).ToPointer();
			g_STDebugger->Init(thisPtr);

			// set up tick function
			this->TickTimer = (gcnew System::Windows::Forms::Timer(this->components));
			TickTimer->Interval = 17;
			TickTimer->Tick += gcnew System::EventHandler(this, &Form1::TickFunction);

			// Enable timer.  
			TickTimer->Enabled = true;
		}

		System::Windows::Forms::RichTextBox^ GetRegisterWindow() { return RegisterWindow; }
		System::Windows::Forms::RichTextBox^ GetAssemblyWindow() { return AssemblyWindow; }
//		System::Windows::Forms::RichTextBox^ GetSourceWindow() { return SourceCodeWindow; }
		System::Windows::Forms::RichTextBox^ GetMemoryWindow() { return MemoryWindow; }
		System::Windows::Forms::RichTextBox^ GetLogWindow() { return LogWindow; }
		System::Windows::Forms::Form^ GetMainWindow() { return this; }
		Preferences^ GetPreferencesWindow() { return preferencesWindow; }
		void SetPreferencesWindow(Preferences^ pWindow) { preferencesWindow = pWindow; }
		Preferences^ preferencesWindow = nullptr;
		
	// do GUI related updates
	private: System::Void TickFunction(System::Object^ sender, System::EventArgs^ e)
		{
			g_STDebugger->RefreshWindows();
		}

	private: System::Windows::Forms::Timer^ TickTimer;
	public:
		bool	MemoryWindowInsertModeOn = false;

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

	private: System::Windows::Forms::MenuStrip^ menuStrip1;

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
	private: System::Windows::Forms::ErrorProvider^ errorProvider2;
	private: System::Windows::Forms::Button^ ConnectButton;
	private: System::Windows::Forms::Label^ LogLabel;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::RichTextBox^ LogWindow;
	private: System::Windows::Forms::ErrorProvider^ errorProvider1;
	private: System::ComponentModel::IContainer^ components;
		    

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->RegisterWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->MemoryWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->AssemblyWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->errorProvider2 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->ConnectButton = (gcnew System::Windows::Forms::Button());
			this->LogWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->LogLabel = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1156, 33);
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
			this->fileToolStripMenuItem->Size = System::Drawing::Size(54, 32);
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
			this->preferencesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::preferencesToolStripMenuItem_Click);
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
			this->quitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::quitToolStripMenuItem_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(787, 93);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(93, 25);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Registers";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// RegisterWindow
			// 
			this->RegisterWindow->BackColor = System::Drawing::SystemColors::ControlLight;
			this->RegisterWindow->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RegisterWindow->Location = System::Drawing::Point(792, 120);
			this->RegisterWindow->Name = L"RegisterWindow";
			this->RegisterWindow->ReadOnly = true;
			this->RegisterWindow->Size = System::Drawing::Size(344, 254);
			this->RegisterWindow->TabIndex = 4;
			this->RegisterWindow->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(16, 546);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(83, 25);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Memory";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// MemoryWindow
			// 
			this->MemoryWindow->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->MemoryWindow->DetectUrls = false;
			this->MemoryWindow->Font = (gcnew System::Drawing::Font(L"Courier New", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MemoryWindow->Location = System::Drawing::Point(19, 604);
			this->MemoryWindow->Name = L"MemoryWindow";
			this->MemoryWindow->Size = System::Drawing::Size(1118, 137);
			this->MemoryWindow->TabIndex = 6;
			this->MemoryWindow->Text = L"";
			this->MemoryWindow->WordWrap = false;
			this->MemoryWindow->VScroll += gcnew System::EventHandler(this, &Form1::MemoryWindow_VScroll);
			this->MemoryWindow->Enter += gcnew System::EventHandler(this, &Form1::MemoryWindow_Enter);
			this->MemoryWindow->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::MemoryWindow_KeyDown);
			this->MemoryWindow->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::MemoryWindow_KeyPress);
			this->MemoryWindow->Leave += gcnew System::EventHandler(this, &Form1::MemoryWindow_Leave);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Courier New", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(19, 574);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(214, 23);
			this->richTextBox1->TabIndex = 7;
			this->richTextBox1->Text = L"0x00000000";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox1_TextChanged);
			this->richTextBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::richTextBox1_KeyDown);
			this->richTextBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::richTextBox1_KeyPress);
			// 
			// AssemblyWindow
			// 
			this->AssemblyWindow->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->AssemblyWindow->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AssemblyWindow->Location = System::Drawing::Point(21, 120);
			this->AssemblyWindow->Name = L"AssemblyWindow";
			this->AssemblyWindow->ReadOnly = true;
			this->AssemblyWindow->Size = System::Drawing::Size(750, 418);
			this->AssemblyWindow->TabIndex = 8;
			this->AssemblyWindow->Text = L"";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(18, 93);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(98, 25);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Assembly";
			// 
			// errorProvider1
			// 
			this->errorProvider1->ContainerControl = this;
			// 
			// errorProvider2
			// 
			this->errorProvider2->ContainerControl = this;
			// 
			// ConnectButton
			// 
			this->ConnectButton->Location = System::Drawing::Point(76, 34);
			this->ConnectButton->Name = L"ConnectButton";
			this->ConnectButton->Size = System::Drawing::Size(38, 31);
			this->ConnectButton->TabIndex = 10;
			this->ConnectButton->Text = L"Connect";
			this->ConnectButton->UseVisualStyleBackColor = true;
			this->ConnectButton->Click += gcnew System::EventHandler(this, &Form1::ConnectButton_Click);
			// 
			// LogWindow
			// 
			this->LogWindow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LogWindow->Location = System::Drawing::Point(18, 783);
			this->LogWindow->Margin = System::Windows::Forms::Padding(2);
			this->LogWindow->Name = L"LogWindow";
			this->LogWindow->ReadOnly = true;
			this->LogWindow->Size = System::Drawing::Size(1118, 115);
			this->LogWindow->TabIndex = 11;
			this->LogWindow->Text = L"";
			// 
			// LogLabel
			// 
			this->LogLabel->AutoSize = true;
			this->LogLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LogLabel->Location = System::Drawing::Point(13, 756);
			this->LogLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->LogLabel->Name = L"LogLabel";
			this->LogLabel->Size = System::Drawing::Size(130, 25);
			this->LogLabel->TabIndex = 12;
			this->LogLabel->Text = L"Log Window";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(120, 34);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(38, 31);
			this->button1->TabIndex = 13;
			this->button1->Text = L"Disconnected";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(237, 34);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(130, 31);
			this->button2->TabIndex = 14;
			this->button2->Text = L"Test Button";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1156, 909);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->LogLabel);
			this->Controls->Add(this->LogWindow);
			this->Controls->Add(this->ConnectButton);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->AssemblyWindow);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->MemoryWindow);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->RegisterWindow);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Atari ST Remote Debugger";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::Form1_KeyPress);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider2))->EndInit();
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
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e)
{
}
private: System::Void MemoryWindow_VScroll(System::Object^ sender, System::EventArgs^ e)
{
}

// Memory address change
private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	System::Windows::Forms::RichTextBox^ rtb = (System::Windows::Forms::RichTextBox^)sender;
	System::String^ newText = rtb->Text;
	char* cText = ConvertStringToChar(newText);
	u32 val = atoi(cText);

	g_STDebugger->SetStartingMemoryAddress(val);
}

// memory window events
private: System::Void MemoryWindow_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	System::Windows::Forms::RichTextBox^ rtb = (System::Windows::Forms::RichTextBox^)sender;
	u32 position = rtb->SelectionStart;

	// determine if we are in ascii or not
	u32 relativePosition = position;

	while (1)
	{
		s32 newOffset = relativePosition - g_STDebugger->GetMemoryWindowLineLength();
		if (newOffset < 0)
		{
			break;
		}
		relativePosition = newOffset;
	}

	if (relativePosition >= g_STDebugger->GetMemoryWindowFirstCharacterPositionOfFirstLineOfAscii())
	{
		g_STDebugger->SetMemoryWindowInAsciiBlock(true);
	}
	else
	{
		g_STDebugger->SetMemoryWindowInAsciiBlock(false);
	}

	// if we click in the area between memory / ascii
	if (!g_STDebugger->GetMemoryWindowInAsciiBlock())
	{
		if ((e->KeyCode >= Keys::A && e->KeyCode <= Keys::F) ||
			(e->KeyCode >= Keys::D0 && e->KeyCode <= Keys::D9) ||
			(e->KeyCode >= Keys::NumPad0 && e->KeyCode <= Keys::NumPad9))
		{
			// first line
			if ((position > (g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine() + 1) && position <= g_STDebugger->GetMemoryWindowFirstCharacterPositionOfFirstLineOfAscii()))
			{
				u32 offsetIntoLine = g_STDebugger->GetMemoryWindowFirstCharacterPositionOfFirstLineOfAscii();
				g_STDebugger->SetMemoryWindowInAsciiBlock(true);
				rtb->Select((offsetIntoLine - position) + position, 0);
				e->Handled = true;
				return;
			}
			else if ((relativePosition > (g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine() + 1))) // && ((position - g_STDebugger->GetMemoryWindowFirstCharacterPositionOfFirstLineOfAscii()) % g_STDebugger->GetMemoryWindowLastCharacterOfFirstLineAscii() == 0))
			{
				u32 offsetIntoLine = g_STDebugger->GetMemoryWindowFirstCharacterPositionOfFirstLineOfAscii();

				while (1)
				{
					s32 newOffset = offsetIntoLine + g_STDebugger->GetMemoryWindowLineLength();
					if (newOffset > (s32)position)
					{
						offsetIntoLine = newOffset;
						break;
					}
					offsetIntoLine = newOffset;
				}

				g_STDebugger->SetMemoryWindowInAsciiBlock(true);
				rtb->Select((offsetIntoLine - position) + position, 0);
				e->Handled = true;
				return;
			}
			else // handle address block input (ignore)
			{
				if (position < g_STDebugger->GetMemoryWindowFirstCharacterPosition())
				{
					rtb->Select(g_STDebugger->GetMemoryWindowFirstCharacterPosition(), 0);
					e->Handled = true;
					return;
				}
				else // secondary lines
				{
					if (relativePosition < g_STDebugger->GetMemoryWindowFirstCharacterPosition())
					{
						u32 offsetIntoLine = g_STDebugger->GetMemoryWindowFirstCharacterPosition();

						while (1)
						{
							s32 newOffset = offsetIntoLine + g_STDebugger->GetMemoryWindowLineLength();
							if (newOffset > (s32)position)
							{
								offsetIntoLine = newOffset;
								break;
							}
							offsetIntoLine = newOffset;
						}

						g_STDebugger->SetMemoryWindowInAsciiBlock(true);
						rtb->Select((offsetIntoLine - position) + position, 0);
						e->Handled = true;
						return;
					}
				}
			}
		}
	}
	else // handle clicking on end of ascii block
	{
		if (relativePosition == g_STDebugger->GetMemoryWindowLastCharacterOfFirstLineAscii() + 1)
		{
			g_STDebugger->SetMemoryWindowInAsciiBlock(false);
			rtb->Select(position + g_STDebugger->GetMemoryWindowWrapRight(), 0);
			e->Handled = false;
			return;
		}
	}

	if (e->KeyCode == Keys::Insert)
	{
		MemoryWindowInsertModeOn = !MemoryWindowInsertModeOn;
		e->Handled = true;
		return;
	}

	if (e->KeyCode == Keys::Delete || e->KeyCode == Keys::Back)
	{
		e->Handled = true;
		return;
	}

	// if we are moving the arrow keys we need to only allow within a certain range on the text
	if (e->KeyCode == Keys::Left)
	{
		// clamp cursor left side (first post)
		if (position == g_STDebugger->GetMemoryWindowFirstCharacterPosition())
		{
			rtb->Select(position + 1, 0);
			e->Handled = false;
			return;
		}

		// wrap from other lines to the end of previous
		if ( position > g_STDebugger->GetMemoryWindowFirstCharacterPosition() && (position - g_STDebugger->GetMemoryWindowFirstCharacterPosition()) % g_STDebugger->GetMemoryWindowLineLength() == 0)
		{
			rtb->Select(position - g_STDebugger->GetMemoryWindowWrapRight(), 0);
			e->Handled = false;
			return;
		}

		// gaps
		if (position > 0 && rtb->Text[position - 1] == ' ')
		{
			rtb->Select(position - 3, 0);
			e->Handled = true;
			return;
		}
	}
	if (e->KeyCode == Keys::Right)
	{
		// temp until we get memory window scrolling in
		if (position > 3962)
		{
			rtb->Select(position - 1, 0);
			e->Handled = false;
			return;
		}

		// jump to ascii
		if (position == g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine() || (position > g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine() && (position - g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine()) % g_STDebugger->GetMemoryWindowLineLength() == 0))
		{
			g_STDebugger->SetMemoryWindowInAsciiBlock(true);
			rtb->Select(position + 3, 0);
			e->Handled = false;
			return;
		}

		// wrap from end of line to next start
		if (position == g_STDebugger->GetMemoryWindowLastCharacterOfFirstLineAscii() || (position > g_STDebugger->GetMemoryWindowLastCharacterOfFirstLineAscii() && (position - g_STDebugger->GetMemoryWindowLastCharacterOfFirstLineAscii()) % g_STDebugger->GetMemoryWindowLineLength() == 0))
		{
			g_STDebugger->SetMemoryWindowInAsciiBlock(false);
			rtb->Select(position + g_STDebugger->GetMemoryWindowWrapRight(), 0);
			e->Handled = false;
			return;
		}

		if (rtb->Text[position + 1] == ' ')
		{
			rtb->Select(position + 3, 0);
			e->Handled = true;
			return;
		}
	}

	if ( (e->KeyCode >= Keys::A && e->KeyCode <= Keys::F) ||
		 (e->KeyCode >= Keys::D0 && e->KeyCode <= Keys::D9)  ||
		(e->KeyCode >= Keys::NumPad0 && e->KeyCode <= Keys::NumPad9))
	{
		if (rtb->Text[position] == ' ')
		{
			u32 gapValue = 1;
			if (rtb->Text[position + 1] == ' ')
			{
				gapValue = 2;
			}

			if (position > g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine())
			{
				rtb->Select(position + gapValue, 0);
			}
			else
			{
				rtb->Select(position + gapValue, 0);
			}
			e->Handled = true;
			return;
		}
	}
}

// memory window text changed
private: System::Void MemoryWindow_TextChanged(System::Object^ sender, System::EventArgs^ e) 
{
	System::Windows::Forms::RichTextBox^ rtb = (System::Windows::Forms::RichTextBox^)sender;
	System::String^ newText = rtb->Text;
	u32 position = rtb->SelectionStart;

	rtb->Text = rtb->Text->Remove(position, 1);
	rtb->SelectionStart = position;

	// also need to change the memory / ascii in relation to this change

	// typed off end of mem into ascii
	if (position == (g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine() + 1) || (position > (g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine() + 1) && (position - (g_STDebugger->GetMemoryWindowLastCharacterOfFirstLine() + 1)) % g_STDebugger->GetMemoryWindowLineLength() == 0))
	{
		rtb->Select(position + 3, 0);
		g_STDebugger->SetMemoryWindowInAsciiBlock(true);
	}

	// typed off end of ascii / wrap to next line
	if (position == (g_STDebugger->GetMemoryWindowLastCharacterOfFirstLineAscii() + 1) || (position > (g_STDebugger->GetMemoryWindowLastCharacterOfFirstLineAscii() + 1) && (position - (g_STDebugger->GetMemoryWindowLastCharacterOfFirstLineAscii() + 1)) % g_STDebugger->GetMemoryWindowLineLength() == 0))
	{
		rtb->Select(position + g_STDebugger->GetMemoryWindowWrapRight(), 0);
		g_STDebugger->SetMemoryWindowInAsciiBlock(false);
	}
}

// memory window key press
private: System::Void MemoryWindow_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	System::Windows::Forms::RichTextBox^ rtb = (System::Windows::Forms::RichTextBox^)sender;

	// ignore anything but 0 / alphanumeric and arrows
	if (!System::Char::IsDigit(e->KeyChar) &&
		!System::Char::IsLetter(e->KeyChar))
	{
		e->Handled = true;
		return;
	}

	String^ letter = System::Char::ToString(e->KeyChar);
	char* cl = ConvertStringToChar(letter);
	int lk = *cl;

	bool keyAllowed = false;
	if ((lk >= 'A' && lk <= 'F') || 
		(lk >= 'a' && lk <= 'f') ||
		(lk >= '0' && lk <= '9'))
	{
		keyAllowed = true;
	}

	if (!keyAllowed)
	{
		e->Handled = true;
		return;
	}

	if (System::Char::IsLower(e->KeyChar))
	{
		e->KeyChar = System::Char::ToUpper(e->KeyChar);
	}
}

// Form 1 keypress
private: System::Void Form1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) 
{
}

// Memory Address key press
private: System::Void richTextBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{

}

// Memory address key down
private: System::Void richTextBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
}

// Memory Window lost focus
private: System::Void MemoryWindow_Leave(System::Object^ sender, System::EventArgs^ e)
{
	System::Windows::Forms::RichTextBox^ rtb = (System::Windows::Forms::RichTextBox^)sender;
	rtb->TextChanged -= gcnew System::EventHandler(this, &Form1::MemoryWindow_TextChanged);
}

// Memory Window Got Focus
private: System::Void MemoryWindow_Enter(System::Object^ sender, System::EventArgs^ e)
{
	System::Windows::Forms::RichTextBox^ rtb = (System::Windows::Forms::RichTextBox^)sender;
	rtb->TextChanged += gcnew System::EventHandler(this, &Form1::MemoryWindow_TextChanged);

//	rtb->Cursor = System::Windows::Forms::Cursors.Cross;
}

private: System::Void preferencesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	// open preferences window
	if (preferencesWindow == nullptr)
	{
		preferencesWindow = gcnew Preferences();
		preferencesWindow->mainWindow = this;

		// setup the dropdownlist with the COM ports available
		System::Windows::Forms::ComboBox^ comportsList = preferencesWindow->GetComportsList();
		System::Windows::Forms::RichTextBox^ comportsDesc = preferencesWindow->GetSerialPortDescBox();
		System::Windows::Forms::ComboBox^ baudRateList = preferencesWindow->GetBaudRateList();

		preferencesWindow->SelectedBaudRate = g_STDebugger->GetBaudRate();
		preferencesWindow->SelectedComPort = ConvertCharToString(g_STDebugger->GetComPortName());

		u32 currentPortIndex = 0;
		DynArray<ComPort*>& comports = g_STDebugger->GetComPortsArray();
		comportsList->Items->Add("<None>");
		for (s32 i = 0; i < comports.Count(); i++)
		{
			ComPort* port = comports[i];
			comportsList->Items->Add(ConvertCharToString(port->PortName.GetPtr()));
			comportsDesc->Text = ConvertCharToString(port->PortDescription.GetPtr());

			if (port->PortName == g_STDebugger->GetComPortName())
			{
				currentPortIndex = i;
			}
		}

		// skip the <none>
		if (comports.Count() > 1)
		{
			comportsList->SelectedItem = comportsList->Items[currentPortIndex + 1];
			comportsDesc->Text = ConvertCharToString(comports[currentPortIndex]->PortDescription.GetPtr());
		}
		else
		{
			comportsDesc->Text = "";
		}

		// set correct selected item
		int index = 0;
		switch (g_STDebugger->GetBaudRate())
		{
		case 2400:
			index = 6;
			break;
		case 4800:
			index = 5;
			break;
		case 9600:
			index = 4;
			break;
		case 19200:
			index = 3;
			break;
		case 38400:
			index = 2;
			break;
		case 57600:
			index = 1;
			break;
		case 115200:
			index = 0;
			break;
		default:
			break;
		}

		baudRateList->SelectedItem = baudRateList->Items[index];	// set to ST max as default
		preferencesWindow->Show();
	}
}

// Clicked connect
private: System::Void ConnectButton_Click(System::Object^ sender, System::EventArgs^ e) 
{
	g_STDebugger->ConnectToTarget();
}
// Clicked disconnected
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	g_STDebugger->DisconnectFromTarget();
}

// for testing
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
{
	g_STDebugger->RequestRegisters();
//	g_STDebugger->RequestMemory();
}
private: System::Void quitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
{
	g_STDebugger->Shutdown();
	Close();
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
