//==============================================================================
// CTools.h
//==============================================================================
     
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include "DXSDK\d3dx9.h"
   
//==============================================================================
     
class CTools
{
	public:
	D3DVIEWPORT9  pViewport;
	DWORD	D3D9VTable();
	BOOL	CheckWindowsVersion(DWORD dwMajorVersion,DWORD dwMinorVersion,DWORD dwProductType);
	void    *DetourCreate( BYTE *src, const BYTE *dst, const int len );
	HRESULT GenerateTexture( IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32 );
};
extern CTools Tools;
     
//==============================================================================