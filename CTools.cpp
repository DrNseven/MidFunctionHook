//==============================================================================
// CTools.cpp
//==============================================================================
     
#include "CTools.h"
     
CTools Tools;
     
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
     
BOOL CTools::CheckWindowsVersion(DWORD dwMajorVersion,DWORD dwMinorVersion,DWORD dwProductType)
{
	OSVERSIONINFOEX VersionInfo;
	ZeroMemory(&VersionInfo,sizeof(OSVERSIONINFOEX));
	VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
	GetVersionEx((OSVERSIONINFO*)&VersionInfo);
	if ( VersionInfo.dwMajorVersion	== dwMajorVersion )
    {
    	if ( VersionInfo.dwMinorVersion == dwMinorVersion )
    	{
    		if ( VersionInfo.wProductType == dwProductType )
    		{
    			return ( TRUE );
    		}
    	}
    }
    return ( FALSE );
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