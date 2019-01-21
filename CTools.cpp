//==============================================================================
// CTools.cpp
//==============================================================================
     
#include "CTools.h"
     
CTools Tools;
     
//==============================================================================

char *CTools::GetDirectoryFile(char *filename)
{
	static char path[320];
	strcpy_s(path, dlldir);
	strcat_s(path, filename);
	return path;
}

//==============================================================================

void CTools::Log(const char *fmt, ...)
{
	if (!fmt)	return;

	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	ofstream logfile(Tools.GetDirectoryFile((PCHAR)"log.txt"), ios::app);
	if (logfile.is_open() && text)	logfile << text << endl;
	logfile.close();
}

//==============================================================================

DWORD CTools::D3D9VTable()
{
	DWORD dwObjBase = (DWORD)LoadLibraryA("D3D9.DLL");
	while ( dwObjBase++ < dwObjBase + 0x127850 )
	{
		if ( (*(WORD*)(dwObjBase + 0x00)) == 0x06C7 && (*(WORD*)(dwObjBase + 0x06)) == 0x8689 && (*(WORD*)(dwObjBase + 0x0C)) == 0x8689 ) 
		{ 
			dwObjBase += 2; 
    		break; 
    	}
	}
	return ( dwObjBase );
}

//==============================================================================

typedef LONG NTSTATUS, *PNTSTATUS;
#define STATUS_SUCCESS (0x00000000)

typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

RTL_OSVERSIONINFOW CTools::GetRealOSVersion()
{
	HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
	if (hMod)
	{
		RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
		if (fxPtr != nullptr)
		{
			RTL_OSVERSIONINFOW rovi = { 0 };
			rovi.dwOSVersionInfoSize = sizeof(rovi);
			if (STATUS_SUCCESS == fxPtr(&rovi))
			{
				//Log("rovi.dwMajorVersion == %d", rovi.dwMajorVersion); //10
				//Log("rovi.dwMinorVersion == %d", rovi.dwMinorVersion); //0
				return rovi;
			}
		}
	}
	RTL_OSVERSIONINFOW rovi = { 0 };
	return rovi;
}

BOOL CTools::isWindows10()
{
	RTL_OSVERSIONINFOW osv = Tools.GetRealOSVersion();
	return ((osv.dwMajorVersion == 10) && (osv.dwMinorVersion == 0));
	//return (osv.dwMajorVersion >= 10);
}

BOOL CTools::isWindows81()
{
	RTL_OSVERSIONINFOW osv = Tools.GetRealOSVersion();
	return ((osv.dwMajorVersion == 6) && (osv.dwMinorVersion == 3));
}

BOOL CTools::isWindows80()
{
	RTL_OSVERSIONINFOW osv = Tools.GetRealOSVersion();
	return ((osv.dwMajorVersion == 6) && (osv.dwMinorVersion == 2));
}

BOOL CTools::isWindows7()
{
	RTL_OSVERSIONINFOW osv = Tools.GetRealOSVersion();
	return ((osv.dwMajorVersion == 6) && (osv.dwMinorVersion == 1));
}

BOOL CTools::isWindowsVista()
{
	RTL_OSVERSIONINFOW osv = Tools.GetRealOSVersion();
	return ((osv.dwMajorVersion == 6) && (osv.dwMinorVersion == 0));
}

BOOL CTools::isWinXPProandServer()
{
	RTL_OSVERSIONINFOW osv = Tools.GetRealOSVersion();
	return ((osv.dwMajorVersion == 5) && (osv.dwMinorVersion == 2));
}

BOOL CTools::isWindowsXP()
{
	RTL_OSVERSIONINFOW osv = Tools.GetRealOSVersion();
	return ((osv.dwMajorVersion == 5) && (osv.dwMinorVersion == 1));
}
//==============================================================================
     
void *CTools::DetourCreate(BYTE *src, const BYTE *dst, const int len)
{
    BYTE *jmp = (BYTE*)malloc(len+5);
    DWORD dwBack;
     
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
    memcpy(jmp, src, len);	
    jmp += len;
    jmp[0] = 0xE9;
    *(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;
    src[0] = 0xE9;
    *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;
    for (int i=5; i<len; i++)  src[i]=0x90;
    VirtualProtect(src, len, dwBack, &dwBack);
    return (jmp-len);
}
     
//==============================================================================