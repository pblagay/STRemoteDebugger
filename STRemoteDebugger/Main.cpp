
#include "Windows.h"
#include "Form1.h"
#include "Debugger.h"

using namespace System;
using namespace System::Windows::Forms;

// global singletons
STDebugger* g_STDebugger = nullptr;


[STAThread]
int main()
{
	OutputDebugString(L"Starting ST Remote Debugger..\n");
	g_STDebugger = new STDebugger;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinformsSTDebugger::Form1());

	if (g_STDebugger)
	{
		delete g_STDebugger;
		g_STDebugger = nullptr;
	}

	OutputDebugString(L"Closing ST Remote Debugger..\n");

	return 0;
}

