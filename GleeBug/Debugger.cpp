#include "Debugger.h"

namespace GleeBug
{
	Debugger::Debugger()
	{
		_processes.clear();
	}

	bool Debugger::Init(const wchar_t* szFilePath,
		const wchar_t* szCommandLine,
		const wchar_t* szCurrentDirectory)
	{
		

		STARTUPINFOW si;
		memset(&si, 0, sizeof(si));
		const wchar_t* szFileNameCreateProcess;
		wchar_t* szCommandLineCreateProcess;
		if (szCommandLine == NULL || !wcslen(szCommandLine))
		{
			szCommandLineCreateProcess = 0;
			szFileNameCreateProcess = szFilePath;
		}
		else
		{
			wchar_t szCreateWithCmdLine[1024];
			swprintf_s(szCreateWithCmdLine, L"\"%s\" %s", szFilePath, szCommandLine);
			szCommandLineCreateProcess = szCreateWithCmdLine;
			szFileNameCreateProcess = 0;
		}

		return !!CreateProcessW(szFileNameCreateProcess,
			szCommandLineCreateProcess,
			NULL,
			NULL,
			FALSE,
			DEBUG_PROCESS | CREATE_NEW_CONSOLE,
			NULL,
			szCurrentDirectory,
			&si,
			&_mainProcess);
	}

	bool Debugger::Stop()
	{
		return !!TerminateProcess(_mainProcess.hProcess, 0);
	}

	bool Debugger::Detach()
	{
		return !!DebugActiveProcessStop(_mainProcess.dwProcessId);
	}

	bool Debugger::SetBreakPointMainProcess(LPVOID address, uint32_t bp_type){
		breakpoint new_bp = breakpoint(_curProcess->hProcess, address, bp_type);
		breakpoint_id new_id = breakpoint_id((uint32_t)address, bp_type);
		return new_bp.enabled;
	}
	bool Debugger::DelBreakPointMainProcess(LPVOID address, uint32_t bp_type){
		breakpoint_id new_id = breakpoint_id((uint32_t)address, bp_type);
		breakpoint bp_del = _curProcess->bpManager[new_id];
		bp_del.DeleteBP(_curProcess->hProcess);
		_curProcess->bpManager.erase(new_id);
		return true;
	}

};