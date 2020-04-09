// CParkingManage.cpp: 实现文件
//

#include "stdafx.h"
#include "ParkingManager.h"
#include "CParkingManage.h"
#include "afxdialogex.h"
#include "AddCar.h"
#include "sqlite3.h"
#include <stdio.h>
#include <atlbase.h>
#include <iostream>
#pragma comment(lib, "sqlite3.lib")
#include "DelCar.h"
#include "CarRec.h"
#include "ShowCar.h"
// CParkingManage 对话框


IMPLEMENT_DYNAMIC(CParkingManage, CDialogEx)

CParkingManage::CParkingManage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ParkingManage, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CParkingManage::~CParkingManage()
{
}

void CParkingManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ListCtrl);
}


BEGIN_MESSAGE_MAP(CParkingManage, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON3, &CParkingManage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CParkingManage::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CParkingManage::OnBnClickedButton4)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CParkingManage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CParkingManage::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CParkingManage::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CParkingManage::OnBnClickedButton6)
//	ON_WM_TIMECHANGE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
//	ON_WM_ERASEBKGND()
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CParkingManage 消息处理程序


void CParkingManage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(&rect);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP1);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
	//将位图选入临时内存设备环境
	CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}



void CParkingManage::ReadStringCharToUnicode(CString &str)
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

//防止中文字符出现乱码
void CParkingManage::OnBnClickedButton3()
{
	LONG lStyle;
	lStyle = GetWindowLong(ListCtrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	lStyle |= LVS_SINGLESEL;//单选模式
	ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);//网格线
	SetWindowLong(ListCtrl.m_hWnd, GWL_STYLE, lStyle);//设置style
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < 6; i++) ListCtrl.DeleteColumn(0);
	ListCtrl.DeleteAllItems();
	CStdioFile file;
	CString strline, m_id, m_name;
	char* t = NULL;
	ListCtrl.InsertColumn(0, L"车号", LVCFMT_CENTER, 100, 10);
	ListCtrl.InsertColumn(1, L"车号", LVCFMT_CENTER, 100, 10);
	ListCtrl.InsertColumn(2, L"车位", LVCFMT_CENTER, 80, 10);
	ListCtrl.InsertColumn(3, L"停入时间", LVCFMT_CENTER, 150, 10);
	ListCtrl.InsertColumn(4, L"计费时间", LVCFMT_CENTER, 150, 10);
	ListCtrl.InsertColumn(5, L"费用", LVCFMT_CENTER, 150, 10);
	ListCtrl.InsertColumn(6, L"是否离开", LVCFMT_CENTER, 80, 10);
	ListCtrl.DeleteColumn(0);
	sqlite3* m_pDB;
	int rc;
	char* err_msg = NULL;
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
	sprintf_s(sql, SQL_UPDATE_DATA, timstr, rawtime, COST);
	rc = sqlite3_exec(m_pDB, sql, NULL, NULL, &err_msg);
	rc = sqlite3_prepare_v2(m_pDB, SQL_QUERY_DATA, -1, &stmt, 0);
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
		CString str = UTF8ToUnicode((char*)sqlite3_column_text(stmt, 0));
		int nRow=ListCtrl.InsertItem(1, str); 
		ListCtrl.SetItemText(nRow,1, CString(sqlite3_column_text(stmt, 1)));
		ListCtrl.SetItemText(nRow, 2, CString(sqlite3_column_text(stmt, 2)));
		ListCtrl.SetItemText(nRow, 3, CString(sqlite3_column_text(stmt, 3)));
		ListCtrl.SetItemText(nRow, 4, CString(sqlite3_column_text(stmt, 6)));
		if (CString(sqlite3_column_text(stmt, 7))=="1")ListCtrl.SetItemText(nRow, 5, _T("是"));
		else ListCtrl.SetItemText(nRow, 5, _T("否"));
		rc = sqlite3_step(stmt);
	}
	sqlite3_close(m_pDB);

	int nCount = ListCtrl.GetItemCount() - 1;
	while (nCount > -1)//为每一行绑定一个值，将来这个值会传递给排序函数的参数lp1和lp2
	{
		ListCtrl.SetItemData(nCount, nCount);
		nCount--;
	}
	ListCtrl.SortItems(CompareByName, (DWORD_PTR)this);

}


void CParkingManage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	AddCar AC;
	AC.DoModal();
}


void CParkingManage::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	LONG lStyle;
	lStyle = GetWindowLong(ListCtrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	lStyle |= LVS_SINGLESEL;//单选模式
	ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);//网格线
	SetWindowLong(ListCtrl.m_hWnd, GWL_STYLE, lStyle);//设置style
	for (int i = 0; i < 6; i++) ListCtrl.DeleteColumn(0);
	ListCtrl.DeleteAllItems();
	ListCtrl.InsertColumn(0, L"空闲车位", LVCFMT_CENTER, 80, 10);
	ListCtrl.InsertColumn(1, L"空闲车位", LVCFMT_CENTER, 80, 10);
	ListCtrl.DeleteColumn(0);
	int count = 1;
	for (int i = 0; i < NUM; i++) {
		if (*(PNUM + i) == 0) {
			CString str;
			str.Format(_T("%d"), i + 1);
			ListCtrl.InsertItem(count,str);
			count++;
		}
	}

}


BOOL CParkingManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(2, 50, NULL);
	//setPNUM();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CParkingManage::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	CStdioFile file;
	file.Open(L"text.txt", CFile::modeWrite | CFile::modeCreate);
	str.Format(_T("%d"), NUM);
	file.WriteString(str);
	file.WriteString(_T(" "));
	str.Format(_T("%lf"), COST);
	file.WriteString(str);
	file.WriteString(_T(" "));
	for (int i = 0; i < NUM; i++)
	{
		str.Format(_T("%d"), *(PNUM+i));
		file.WriteString(str);
		file.WriteString(_T(" "));
	}
	file.Close();
	CDialogEx::OnClose();
}
CString UTF8ToUnicode(const char* szUtf8)
{
	//预转换，得到所需空间的大小;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szUtf8, strlen(szUtf8), NULL, 0);

	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* unicode = new wchar_t[wcsLen + 1];

	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szUtf8, strlen(szUtf8), unicode, wcsLen);

	//最后加上'\0'
	unicode[wcsLen] = '\0';
	CString unicodeString(unicode);
	return unicode;
}

void CParkingManage::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	DelCar DC;
	DC.DoModal();
}

int CALLBACK CParkingManage::CompareByName(LPARAM lP1, LPARAM lP2, LPARAM lP)
{
	CParkingManage* pThis = (CParkingManage*)lP;

	//分别获取参与排序的两个行的姓名

	CString str1 = pThis->ListCtrl.GetItemText(lP1, 5);

	CString str2 = pThis->ListCtrl.GetItemText(lP2, 5);

	//返回值:如果为真交换两个行的数据，如果为假两个行不进行交换

	return str1 > str2;//按照名字的汉语拼音，由大向小排列
}


void CParkingManage::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CarRec CR;
	CR.DoModal();
}


void CParkingManage::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	sqlite3* m_pDB;
	int rc;
	char* err_msg = NULL;
	rc = sqlite3_open("myDatabase.db", &m_pDB);// 打开数据库，不存在时创建  
	if (rc)
	{
		sqlite3_close(m_pDB);  //打开失败！   
		AfxMessageBox(_T("数据库打开失败，请检查后再操作！"), NULL, MB_ICONSTOP);
		return;
	}
	char sql[256];
	sqlite3_stmt* stmt;
	rc = sqlite3_prepare_v2(m_pDB, SQL_QUERY_DATA2, -1, &stmt, 0);
	if (rc != SQLITE_OK)
	{
		if (sqlite3_exec(m_pDB, SQL_CREATE_TABLE, NULL, NULL, &err_msg) != SQLITE_OK)
		{
			AfxMessageBox(_T("操作失败，数据库链表生成错误！"), NULL, MB_ICONSTOP);
			return;
		}
	}
	rc = sqlite3_step(stmt);
	double sum = 0;
	while (rc == SQLITE_ROW)
	{
		sum+=atof((char*)sqlite3_column_text(stmt, 0));
		rc = sqlite3_step(stmt);
	}
	sqlite3_close(m_pDB);
	CString str;
	str.Format(_T("%.2lf"),sum);
	str += "元";
	AfxMessageBox(str, NULL);
}


void CParkingManage::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowCar SC;
	SC.DoModal();
}


//void CParkingManage::OnTimeChange()
//{
//	CDialogEx::OnTimeChange();
//
//	// TODO: 在此处添加消息处理程序代码
//}


void CParkingManage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	CString timstr, daystr, str;
	timstr.Format(_T("%02d:%02d:%02d"), timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
	daystr.Format(_T("%d年%d月%d日"), timeinfo.tm_year+1900, timeinfo.tm_mon, timeinfo.tm_mday);
	int sum = 0;
	for (int i = 0; i < NUM; i++) if (*(PNUM + i) == 0) sum++;
	str.Format(_T("%d"), sum);
	GetDlgItem(IDC_STATIC4)->SetWindowText(str);
	GetDlgItem(IDC_STATIC1)->SetWindowText(timstr);
	GetDlgItem(IDC_STATIC2)->SetWindowText(daystr);
	CRect rtlbl;
	GetDlgItem(IDC_STATIC4)->GetWindowRect(&rtlbl);
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	GetDlgItem(IDC_STATIC1)->GetWindowRect(&rtlbl);
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	GetDlgItem(IDC_STATIC2)->GetWindowRect(&rtlbl);
	ScreenToClient(&rtlbl); //转到客户端界面
	InvalidateRect(&rtlbl);//最后刷新对话框背景 
	UpdateWindow();
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CParkingManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//将界面上static控件的背景设为透明
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC1:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC2:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC3:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_STATIC4:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


//BOOL CParkingManage::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	return CDialogEx::OnEraseBkgnd(pDC);
//}


BOOL CParkingManage::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
