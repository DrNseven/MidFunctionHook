//==============================================================================
// CMain.cpp
//==============================================================================
#include "CTools.h"
 #include "CMain.h"
#pragma comment(lib, "d3dx9.lib")
//#pragma comment(lib, "DXSDK/d3dx9.lib") 
#pragma comment(lib, "d3d9.lib")
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
     
	//test code
	if(T_Models|| CT_Models)
	//if(Stride == 32)
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

	if (Tools.CheckWindowsVersion(6, 1, VER_NT_WORKSTATION) || Tools.CheckWindowsVersion(6, 0, VER_NT_WORKSTATION))
	//if (EqualsMajorVersion(6) && EqualsMinorVersion(1))
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

	if (Tools.CheckWindowsVersion(5, 1, VER_NT_WORKSTATION) || Tools.CheckWindowsVersion(5, 2, VER_NT_WORKSTATION))
	//if (EqualsMajorVersion(5) && EqualsMinorVersion(1))
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

	if (Tools.CheckWindowsVersion(6, 3, VER_NT_WORKSTATION))
	//if (EqualsMajorVersion(6) && EqualsMinorVersion(3))
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

	if (Tools.CheckWindowsVersion(6, 2, VER_NT_WORKSTATION))
	//if (EqualsMajorVersion(6) && EqualsMinorVersion(2))
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
    PDWORD dwD3DVTable;
    do
    {
    	*(DWORD*)&dwD3DVTable = *(DWORD*)Tools.D3D9VTable();
    }
    while ( !dwD3DVTable );


	if (Tools.CheckWindowsVersion(6, 3, VER_NT_WORKSTATION))
	{
	DrawIndexedPrimitive_Hook = (dwD3DVTable[82] + 0x2D);// ---Windows 8
	DrawIndexedPrimitive_Jump = (DrawIndexedPrimitive_Hook + 0x5);
	*(PDWORD)(&DrawIndexedPrimitive_Pointer) = (DWORD)dwD3DVTable[82];
	Tools.DetourCreate((BYTE*)DrawIndexedPrimitive_Hook, (BYTE*)DrawIndexedPrimitive_Call, 5);
	}
	else if (Tools.CheckWindowsVersion(6, 1, VER_NT_WORKSTATION) || Tools.CheckWindowsVersion(6, 0, VER_NT_WORKSTATION))
	{
	DrawIndexedPrimitive_Hook = (dwD3DVTable[82] + 0x2D);// ---Windows 7
	DrawIndexedPrimitive_Jump = (DrawIndexedPrimitive_Hook + 0x7);
	*(PDWORD)(&DrawIndexedPrimitive_Pointer) = (DWORD)dwD3DVTable[82];
	Tools.DetourCreate((BYTE*)DrawIndexedPrimitive_Hook, (BYTE*)DrawIndexedPrimitive_Call, 5);
	}
	else if (Tools.CheckWindowsVersion(5, 1, VER_NT_WORKSTATION) || Tools.CheckWindowsVersion(5, 2, VER_NT_WORKSTATION))
	{
	DrawIndexedPrimitive_Hook = (dwD3DVTable[82] + 0x1D);// ---Windows XP
	DrawIndexedPrimitive_Jump = (DrawIndexedPrimitive_Hook + 0x5);
	*(PDWORD)(&DrawIndexedPrimitive_Pointer) = (DWORD)dwD3DVTable[82];
	Tools.DetourCreate((BYTE*)DrawIndexedPrimitive_Hook, (BYTE*)DrawIndexedPrimitive_Call, 5);
	}
	else if (Tools.CheckWindowsVersion(6, 2, VER_NT_WORKSTATION))
	{
	DrawIndexedPrimitive_Hook = (dwD3DVTable[82] + 0x30);// ---Windows 10
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
    	CreateThread(0,0,(LPTHREAD_START_ROUTINE)UcFoRum,0,0,0);
    }
    	return ( TRUE );
}
//==============================================================================
