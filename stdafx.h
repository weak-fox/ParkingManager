
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
extern int* PNUM;
extern int NUM;
extern double COST;
extern int REC;
extern time_t rawtime;
extern struct tm timeinfo;









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#define SQL_CREATE_TABLE "Create table if not exists car_info(Cnum string, Pnum int, Itime string, Otime string, Itime1 int , Otime1 int , Cost double, Exit int)"

#define SQL_INSERT_DATA "Insert into car_info (Cnum,Pnum, Itime, Otime , Itime1 , Otime1,Cost ,Exit) values ('%s', '%d', '%s', '%s', '%d', '%d', '%lf', '%d')"

#define SQL_QUERY_DATA "Select * from car_info ORDER BY Exit,Otime1 ASC"

#define SQL_QUERY_DATA1 "Select * from car_info WHERE Cnum='%s' AND Exit = 0"

#define SQL_QUERY_DATA2 "Select Cost from car_info WHERE  Exit = 1"

#define SQL_UPDATE_DATA "UPDATE car_info SET Otime = '%s',Otime1 = %d,Cost =(Otime1-Itime1)*%f WHERE Exit = 0"

#define SQL_UPDATE_DATA1 "UPDATE car_info SET Exit = 1 WHERE Cnum='%s' AND Exit = 0"