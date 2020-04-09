// AddCar.cpp: 实现文件
//

#include "stdafx.h"
#include "ParkingManager.h"
#include "AddCar.h"
#include "afxdialogex.h"
#include "Car.h"
#include <time.h>
#include "Manager.h"
#include "sqlite3.h"
#include <stdio.h>
#include <atlbase.h>
#include <stdio.h>
#pragma comment(lib, "sqlite3.lib")

int i;
sqlite3* m_pDB;
int rc;
char* err_msg = NULL;
// AddCar 对话框

IMPLEMENT_DYNAMIC(AddCar, CDialogEx)

AddCar::AddCar(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDCAR, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

AddCar::~AddCar()
{
}

void AddCar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddCar, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddCar::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &AddCar::OnEnChangeEdit1)
//	ON_WM_CREATE()
ON_WM_CREATE()
END_MESSAGE_MAP()


// AddCar 消息处理程序


void AddCar::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	if (!str.IsEmpty()) {
		Car car;
		car.setCnum(str);
		char* p = UnicodeToUtf8(str);
		char sql[256];
		sqlite3_stmt* stmt;
		sprintf_s(sql, SQL_QUERY_DATA1, p);
		sqlite3_prepare_v2(m_pDB, sql, -1, &stmt, 0);
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW)
		{
			AfxMessageBox(_T("已存在该车辆！"));
			return;
		}
		p=UnicodeToUtf8(str);
		//USES_CONVERSION;
		//char* p = T2A(str);
		GetDlgItem(IDC_STATIC3)->GetWindowText(str);
		int num;
		num = _ttoi(LPCTSTR(str));
		car.setPnum(num);
		car.setItime1(rawtime);
		char timstr[32];
		timstr[31] = '\0';
		asctime_s(timstr, &timeinfo);
		car.setItime(CString(timstr));
		car.setOtime1(rawtime);
		car.setOtime(CString(timstr));
		car.setCost(0);
		car.setExit(false);
		sprintf_s(sql, SQL_INSERT_DATA,p, car.getPnum(), timstr, timstr,car.getItime1(),car.getOtime1(),car.getCost(),car.getExit());
		int exit = sqlite3_exec(m_pDB, sql, 0, 0, &err_msg);
		if (exit != SQLITE_OK)
		{
			sqlite3_close(m_pDB);
			AfxMessageBox(_T("添加过快！请重新添加！"));
			CDialogEx::OnOK();
			return;
		}
		*(PNUM + i) = 1;
	}
	sqlite3_close(m_pDB);
	CDialogEx::OnOK();
}


void AddCar::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


BOOL AddCar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	i = 0;
	while (i<NUM && *(PNUM+i)==1)
	{
		i++;
	}
	if (*(PNUM+i) == 0)
	{
		CString str;
		str.Format(_T("%d"), i+1);
		GetDlgItem(IDC_STATIC3)->SetWindowText(str);

	}
	else
	{
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("0"));
		AfxMessageBox(_T("没有余位！"));
		CDialogEx::OnOK();
	}
	dataopen();
	if (REC == 0) return TRUE;
	// TODO:  在此添加您专用的创建代码
	CStdioFile file;
	CString str;
	char* p;
	if (file.Open(L"result.txt", CFile::modeRead))
		file.ReadString(str);
	ReadStringCharToUnicode(str);

	GetDlgItem(IDC_EDIT1)->SetWindowText(str);
	REC = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void dataopen()
{
	rc = sqlite3_open("myDatabase.db", &m_pDB);// 打开数据库，不存在时创建  
	if (rc)
	{
		sqlite3_close(m_pDB);  //打开失败！   
		AfxMessageBox(_T("数据库打开失败，请检查后再操作！"), NULL, MB_ICONSTOP);
		return;
	}

	if (sqlite3_exec(m_pDB, SQL_CREATE_TABLE, NULL, NULL, &err_msg) != SQLITE_OK)
	{
		AfxMessageBox(_T("操作失败，数据库链表生成错误！"), NULL, MB_ICONSTOP);
		return;
	}
}

char* UnicodeToUtf8(CString unicode)
{
	int len;
	USES_CONVERSION;
	len = WideCharToMultiByte(CP_UTF8, 0,(LPCWCH)unicode, -1, NULL, 0, NULL, NULL);
	char* szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len * 2 + 2);
	WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}



int AddCar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}
void ReadStringCharToUnicode(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1];//注意“+1”，char字符要求结束符，而CString没有
	memset(szBuf, '\0', str.GetLength());

	int i;
	for (i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//结束符。否则会在末尾产生乱码。

	int nLen;
	WCHAR *ptch;
	CString strOut;
	if (szBuf == NULL)
	{
		return;
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, szBuf, -1, NULL, 0);//获得需要的宽字符字节数
	ptch = new WCHAR[nLen];
	memset(ptch, '\0', nLen);
	MultiByteToWideChar(CP_ACP, 0, szBuf, -1, ptch, nLen);
	str.Format(_T("%s"), ptch);

	if (NULL != ptch)
		delete[] ptch;
	ptch = NULL;

	if (NULL != szBuf)
		delete[]szBuf;
	szBuf = NULL;
	return;
}

