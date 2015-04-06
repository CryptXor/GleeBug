#ifndef _MYDEBUGGER_H
#define _MYDEBUGGER_H

#include "../GleeBug/Debugger.h"

using namespace GleeBug;

class MyDebugger : public Debugger
{
protected:
	virtual void cbCreateProcessEvent(const CREATE_PROCESS_DEBUG_INFO & createProcess, const ProcessInfo & process)
	{
		printf("Process %d created with entry 0x%p\n", _debugEvent.dwProcessId, createProcess.lpStartAddress);
		if (SetBreakPointMainProcess((LPVOID)0x0406C35, SOFT_BP) == false)
		{
			printf("wtf failed");
		}
	};

	virtual void cbOnUserBreakPointTrigger(breakpoint bp){
		
		printf("wtf!?");
		if (bp.bp_address == (LPVOID)0x00406C35)
		{
			printf("ho noes, a few bytes further of the entry point!");
		}
	
	};

	virtual void cbExitProcessEvent(const EXIT_PROCESS_DEBUG_INFO & exitProcess, const ProcessInfo & process)
	{
		printf("Process %d terminated with exit code 0x%08X\n", _debugEvent.dwProcessId, exitProcess.dwExitCode);
	}

	virtual void cbCreateThreadEvent(const CREATE_THREAD_DEBUG_INFO & createThread, const ThreadInfo & thread)
	{
		printf("Thread %d created with entry 0x%p\n", _debugEvent.dwThreadId, createThread.lpStartAddress);
	};

	virtual void cbExitThreadEvent(const EXIT_THREAD_DEBUG_INFO & exitThread, const ThreadInfo & thread)
	{
		printf("Thread %d terminated with exit code 0x%08X\n", _debugEvent.dwThreadId, exitThread.dwExitCode);
	};

	virtual void cbLoadDllEvent(const LOAD_DLL_DEBUG_INFO & loadDll, const DllInfo & dll)
	{
		printf("DLL loaded at 0x%p\n", loadDll.lpBaseOfDll);
	};

	virtual void cbUnloadDllEvent(const UNLOAD_DLL_DEBUG_INFO & unloadDll, const DllInfo & dll)
	{
		printf("DLL 0x%p unloaded\n", unloadDll.lpBaseOfDll);
	};

	virtual void cbExceptionEvent(const EXCEPTION_DEBUG_INFO & exceptionInfo)
	{
		printf("Exception with code 0x%08X\n", exceptionInfo.ExceptionRecord.ExceptionCode);
	};

	virtual void cbDebugStringEvent(const OUTPUT_DEBUG_STRING_INFO & debugString)
	{
		printf("Debug string at 0x%p with length %d\n", debugString.lpDebugStringData, debugString.nDebugStringLength);
	};

	virtual void cbRipEvent(const RIP_INFO & rip)
	{
		printf("RIP event type 0x%X, error 0x%X", rip.dwType, rip.dwError);
	};

	virtual void cbSystemBreakpoint()
	{
		printf("System breakpoint reached!");
	}
};

#endif //_MYDEBUGGER_H