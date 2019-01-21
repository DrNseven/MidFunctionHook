//==============================================================================
// CMain.cpp
//==============================================================================
#include "CTools.h"
#include "CMain.h"
//==============================================================================
BOOL DrawIndexedPrimitive_Check = FALSE;
DWORD DrawIndexedPrimitive_Hook, DrawIndexedPrimitive_Jump;
BOOL DrawIndexedPrimitive_CheckPtr = FALSE;
VOID WINAPI DrawIndexedPrimitive_Breakpoint();
LONG WINAPI DrawIndexedPrimitive_Exception(EXCEPTION_POINTERS* ExceptionInfo);
HRESULT (WINAPI* DrawIndexedPrimitive_Pointer)(LPDIRECT3DDEVICE9,D3DPRIMITIVETYPE,INT,UINT,UINT,UINT,UINT);
//==============================================================================
VOID WINAPI DrawIndexedPrimitive_Main(LPDIRECT3DDEVICE9 pDevice,D3DPRIMITIVETYPE Type,INT BaseVertexIndex,UINT MinIndex,UINT NumVertices,UINT StartIndex,UINT primCount)
{
    LPDIRECT3DVERTEXBUFFER9 Stream;
    UINT Stride;
    UINT Offset;
    if ( pDevice->GetStreamSource(0,&Stream,&Offset,&Stride) == D3D_OK )
    {
    	Stream->Release();
    }
    	DrawIndexedPrimitive_CheckPtr = TRUE;
     
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE); //test code

	if(Stride == 32) //test 2
	{
		pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
    	DrawIndexedPrimitive_Pointer(pDevice,Type,BaseVertexIndex,MinIndex,NumVertices,StartIndex,primCount);
    	pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
    }
           
    	DrawIndexedPrimitive_CheckPtr = FALSE;
}
//==============================================================================
__declspec(naked)VOID WINAPI DrawIndexedPrimitive_Call()
{
    if ( !DrawIndexedPrimitive_Check )
	{
    	DrawIndexedPrimitive_Breakpoint();
    	DrawIndexedPrimitive_Check = true;
    }


	if (Tools.isWindows10())
	{
		__asm
		{
			MOV ESI, DWORD PTR SS : [EBP + 0x8] // --- Windows 10
			TEST ESI, ESI
			PUSHFD
			PUSHAD
			JMP UCFORUM
		}
	}

	if (Tools.isWindows81() || Tools.isWindows80())
	{
		__asm
		{
			MOV EDI, DWORD PTR SS : [EBP + 0x8] // --- Windows 8 / 8.1
			TEST EDI, EDI
			PUSHFD
			PUSHAD
			JMP UCFORUM
		}
	}


	if (Tools.isWindows7() || Tools.isWindowsVista())
	{
		__asm
		{
			MOV EDI, DWORD PTR SS : [EBP + 0x8] // --- Vista and 7
			XOR EBX, EBX
			CMP EDI, EBX
			PUSHFD
			PUSHAD
			JMP UCFORUM
		}
	}

	if (Tools.isWinXPProandServer() || Tools.isWindowsXP())
	{
		__asm
		{
			PUSH EBX // --- XP
			PUSH ESI
			MOV ESI, dword ptr ss : [ebp + 8]
			PUSHFD
			PUSHAD
			JMP UCFORUM
		}
	}


    __asm
	{
    	UCFORUM:
		MOV EDX,[DrawIndexedPrimitive_CheckPtr]
    	CMP EDX,0x0
    	JG Jump
    	PUSH [EBP+0x20]
    	PUSH [EBP+0x1C]
    	PUSH [EBP+0x18]
    	PUSH [EBP+0x14]
    	PUSH [EBP+0x10]
    	PUSH [EBP+0xC]
    	PUSH [EBP+0x8]
		CALL [DrawIndexedPrimitive_Main]
    	Jump:
			POPAD
			POPFD
    		CMP EDI,EBX
    		JMP [DrawIndexedPrimitive_Jump]
	}
		
}
//==============================================================================
LONG WINAPI DrawIndexedPrimitive_Exception(EXCEPTION_POINTERS* ExceptionInfo)
{
	if ( ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP && (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress == DrawIndexedPrimitive_Hook )
	{
    	ExceptionInfo->ContextRecord->Eip = (DWORD)DrawIndexedPrimitive_Call;
    	return ( EXCEPTION_CONTINUE_EXECUTION );
    } 
    return ( EXCEPTION_CONTINUE_SEARCH );
}
//==============================================================================
VOID WINAPI DrawIndexedPrimitive_Breakpoint()
{
    AddVectoredExceptionHandler((rand()%0xFFFFFF),DrawIndexedPrimitive_Exception); 
    CONTEXT Context = {CONTEXT_DEBUG_REGISTERS};
    Context.Dr0 = DrawIndexedPrimitive_Hook;
    Context.Dr7 = 0x1;
    SetThreadContext(GetCurrentThread(),&Context);
}
//==============================================================================
VOID WINAPI UcFoRum()
{
	HMODULE dDll = NULL;
	while (!dDll)
	{
		dDll = GetModuleHandleA("d3d9.dll");
		Sleep(100);
	}
	CloseHandle(dDll);

	Tools.GetRealOSVersion();
	

    PDWORD dwD3DVTable;
    do
    {
    	*(DWORD*)&dwD3DVTable = *(DWORD*)Tools.D3D9VTable();
    }
    while ( !dwD3DVTable );


	if (Tools.isWindows10())
	{
		Tools.Log("win 10 detected");
		DrawIndexedPrimitive_Hook = (dwD3DVTable[82] + 0x30);// ---Windows 10
		DrawIndexedPrimitive_Jump = (DrawIndexedPrimitive_Hook + 0x5);
		*(PDWORD)(&DrawIndexedPrimitive_Pointer) = (DWORD)dwD3DVTable[82];
		Tools.DetourCreate((BYTE*)DrawIndexedPrimitive_Hook, (BYTE*)DrawIndexedPrimitive_Call, 5);
	}
	
	else if (Tools.isWindows81() || Tools.isWindows80())
	{
		Tools.Log("win 8 detected");
		DrawIndexedPrimitive_Hook = (dwD3DVTable[82] + 0x2D);// ---Windows 8
		DrawIndexedPrimitive_Jump = (DrawIndexedPrimitive_Hook + 0x5);
		*(PDWORD)(&DrawIndexedPrimitive_Pointer) = (DWORD)dwD3DVTable[82];
		Tools.DetourCreate((BYTE*)DrawIndexedPrimitive_Hook, (BYTE*)DrawIndexedPrimitive_Call, 5);
	}

	else if (Tools.isWindows7() || Tools.isWindowsVista())
	{
		Tools.Log("win 7 detected");
		DrawIndexedPrimitive_Hook = (dwD3DVTable[82] + 0x2D);// ---Windows 7
		DrawIndexedPrimitive_Jump = (DrawIndexedPrimitive_Hook + 0x7);
		*(PDWORD)(&DrawIndexedPrimitive_Pointer) = (DWORD)dwD3DVTable[82];
		Tools.DetourCreate((BYTE*)DrawIndexedPrimitive_Hook, (BYTE*)DrawIndexedPrimitive_Call, 5);
	}

	else if (Tools.isWinXPProandServer() || Tools.isWindowsXP())
	{
		Tools.Log("win xp detected");
		DrawIndexedPrimitive_Hook = (dwD3DVTable[82] + 0x1D);// ---Windows XP
		DrawIndexedPrimitive_Jump = (DrawIndexedPrimitive_Hook + 0x5);
		*(PDWORD)(&DrawIndexedPrimitive_Pointer) = (DWORD)dwD3DVTable[82];
		Tools.DetourCreate((BYTE*)DrawIndexedPrimitive_Hook, (BYTE*)DrawIndexedPrimitive_Call, 5);
	}

    else 
    {
    	MessageBoxA(GetActiveWindow(),"Your System Isn't Supported","Error",MB_OK);
    	ExitProcess(0);
    }
		
}
//==============================================================================
BOOL WINAPI DllMain(HMODULE hModule,DWORD dwReason,LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);
    if ( dwReason == DLL_PROCESS_ATTACH )
    {
		DisableThreadLibraryCalls(hModule);
		GetModuleFileNameA(hModule, Tools.dlldir, 512);
		for (int i = (int)strlen(Tools.dlldir); i > 0; i--)
		{
			if (Tools.dlldir[i] == '\\')
			{
				Tools.dlldir[i + 1] = 0;
				break;
			}
		}
    	CreateThread(0,0,(LPTHREAD_START_ROUTINE)UcFoRum,0,0,0);
    }
    	return ( TRUE );
}
//==============================================================================
