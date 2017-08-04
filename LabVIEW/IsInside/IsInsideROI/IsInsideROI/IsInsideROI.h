// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ISINSIDEROI_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ISINSIDEROI_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ISINSIDEROI_EXPORTS
#define ISINSIDEROI_API extern "C" __declspec(dllexport)
#else
#define ISINSIDEROI_API __declspec(dllimport)
#endif

ISINSIDEROI_API BOOL G_PtInPolyRect(POINT *rgpts, int wnumpts, POINT ptTest, RECT *prbound);
ISINSIDEROI_API BOOL G_PtInPolygon(POINT *ppt, int wnumpts, POINT *ptTest, RECT *prbound);