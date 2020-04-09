// DelCar.cpp: 实现文件
//

#include "stdafx.h"
#include "ParkingManager.h"
#include "DelCar.h"
#include "afxdialogex.h"
#include "sqlite3.h"
#include <stdio.h>
#include <atlbase.h>
#pragma comment(lib, "sqlite3.lib")


// DelCar 对话框

IMPLEMENT_DYNAMIC(DelCar, CDialogEx)

DelCar::DelCar(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DELCAR, pParent)
{

}

DelCar::~DelCar()
{
}

void DelCar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DelCar, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &DelCar::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &DelCar::OnBnClickedOk)
END_MESSAGE_MAP()


// DelCar 消息处理程序


void DelCar::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	sqlite3* m_pDB;
	int rc;
	char* err_msg = NULL;
	CString str;
	rc = sqlite3_open("myDatabase.db", &m_pDB);// 打开数据库，不存在时创建  
	if (rc)
	{
		sqlite3_close(m_pDB);  //打开失败！   
		AfxMessageBox(_T("数据库打开失败，请检查后再操作！"), NULL, MB_ICONSTOP);
		return;
	}
	char sql[256];
	sqlite3_stmt* stmt;
	char timstr[32]; 
	timstr[31] = '\0';
	asctime_s(timstr, &timeinfo);
	sprintf_s(sql, SQL_UPDATE_DATA, timstr, (int)rawtime, COST);
	sqlite3_exec(m_pDB, sql, NULL, NULL, &err_msg);
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	char* p = UnicodeToUtf81(str);
	sprintf_s(sql, SQL_QUERY_DATA1, p);
	rc = sqlite3_prepare_v2(m_pDB, sql, -1, &stmt, 0);
	if (rc != SQLITE_OK)
	{
		if (sqlite3_exec(m_pDB, SQL_CREATE_TABLE, NULL, NULL, &err_msg) != SQLITE_OK)
		{
			AfxMessageBox(_T("操作失败，数据库链表生成错误！"), NULL, MB_ICONSTOP);
			return;
		}
	}
	rc = sqlite3_step(stmt);
	int i = 0;
	while (rc == SQLITE_ROW)
	{
		str = CString(sqlite3_column_text(stmt, 1));
		GetDlgItem(IDC_STATIC3)->SetWindowText(str);
		str = CString(sqlite3_column_text(stmt, 6));
		GetDlgItem(IDC_STATIC5)->SetWindowText(str);
		rc = sqlite3_step(stmt);
		i++;
	}
	if (i == 0)
	{
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("0"));
		GetDlgItem(IDC_STATIC5)->SetWindowText(_T("0"));
	}
	sqlite3_close(m_pDB);
	// TODO:  在此添加控件通知处理程序代码
}

char* UnicodeToUtf81(CString unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)unicode, -1, NULL, 0, NULL, NULL);
	char* szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len * 2 + 2);
	WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}


void DelCar::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	sqlite3* m_pDB;
	int rc;
	char* err_msg = NULL;
	CString str;
	GetDlgItem(IDC_STATIC3)->GetWindowText(str);
	if (str == _T("0"))
	{
		AfxMessageBox(_T("操作无效！车库中没有这辆车！"));
		return;
	}
	rc = sqlite3_open("myDatabase.db", &m_pDB);// 打开数据库，不存在时创建  
	if (rc)
	{
		sqlite3_close(m_pDB);  //打开失败！   
		AfxMessageBox(_T("数据库打开失败，请检查后再操作！"), NULL, MB_ICONSTOP);
		return;
	}

	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	char* p = UnicodeToUtf81(str);
	char sql[256];
	sprintf_s(sql, SQL_UPDATE_DATA1, p);
	int exit=sqlite3_exec(m_pDB, sql, NULL, NULL, &err_msg);
	if (exit != SQLITE_OK)
	{
		sqlite3_close(m_pDB);
		AfxMessageBox(_T("数据更新失败！请重新尝试！"));
		CDialogEx::OnOK();
		return;
	}
	GetDlgItem(IDC_STATIC3)->GetWindowText(str);
	int i = _ttoi(str);
	*(PNUM + i - 1) = 0;
	sqlite3_close(m_pDB);

	CDialogEx::OnOK();
}


BOOL DelCar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (REC == 0) return TRUE;
	// TODO:  在此添加您专用的创建代码
	CStdioFile file;
	CString str;
	char* p;
	if (file.Open(L"result.txt", CFile::modeRead))
		file.ReadString(str);
	ReadStringCharToUnicode1(str);

	GetDlgItem(IDC_EDIT1)->SetWindowText(str);
	REC = 0;
	file.Close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void ReadStringCharToUnicode1(CString &str)
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
