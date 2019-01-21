//==============================================================================
// CTools.h
//==============================================================================
     
#include <windows.h>
#include <fstream>
#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")
using namespace std;
   
//==============================================================================
     
class CTools
{
	public:
		char dlldir[320];
		char *GetDirectoryFile(char *filename);
		void Log(const char *fmt, ...);
		DWORD	D3D9VTable();
		void    *DetourCreate( BYTE *src, const BYTE *dst, const int len );
		RTL_OSVERSIONINFOW GetRealOSVersion();
		BOOL isWindows10();
		BOOL isWindows81();
		BOOL isWindows80();
		BOOL isWindows7();
		BOOL isWindowsVista();
		BOOL isWinXPProandServer();
		BOOL isWindowsXP();
};
extern CTools Tools;
     
//==============================================================================