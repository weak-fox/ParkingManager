// Manager.cpp: 实现文件
//

#include "stdafx.h"
#include "ParkingManager.h"
#include "Manager.h"
#include "afxdialogex.h"
#include <clocale>


// Manager 对话框

IMPLEMENT_DYNAMIC(Manager, CDialogEx)

Manager::Manager(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Manager, pParent)
{
}

Manager::~Manager()
{
}

void Manager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Manager, CDialogEx)
	ON_BN_CLICKED(IDOK, &Manager::OnBnClickedOk)
	ON_WM_PAINT()
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Manager 消息处理程序



void Manager::OnBnClickedOk()
{
	
	UpdateData(TRUE);
	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	if (str.IsEmpty()) 
	{
		return;
	}
	CStdioFile file;
	file.Open(L"text.txt", CFile::modeWrite | CFile::modeCreate);
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	if (str.IsEmpty())
	{
		return;
	}
	NUM = _ttoi(LPCTSTR(str));
	if (NUM > 250) 
	{
		AfxMessageBox(_T("车位数必须小于250！"));
		return;
	}
	else if(NUM<=0)
	{
		AfxMessageBox(_T("车位数必须为大于0的数！"));
		return;
	}
	file.WriteString(str);
	file.WriteString(_T(" "));
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	COST = _ttof(LPCTSTR(str));
	if (COST <= 0)
	{
		AfxMessageBox(_T("价格必须为大于0的数！"));
		return;
	}
	file.WriteString(str);
	file.WriteString(_T(" "));
	PNUM = new int[NUM];
	memset(PNUM,0,NUM*sizeof(int));
	for (int i = 0; i < NUM; i++)
	{
		file.WriteString(_T("0"));
		file.WriteString(_T(" "));
	}
	file.Close();
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	CParkingManage PM;
	PM.DoModal();


}


void Manager::OnPaint()
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



//HBRUSH Manager::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// TODO:  在此更改 DC 的任何特性
//	switch (pWnd->GetDlgCtrlID())
//	{
//	case IDC_STATIC1:
//		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetTextColor(RGB(0, 0, 0));
//		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
//	case IDC_STATIC2:
//		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetTextColor(RGB(0, 0, 0));
//		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
//	case IDC_STATIC3:
//		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetTextColor(RGB(0, 0, 0));
//		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
//	case IDC_STATIC:
//		pDC->SetBkMode(TRANSPARENT);
//		pDC->SetTextColor(RGB(0, 0, 0));
//		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
//	default:
//		break;
//	}
//	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
//	return hbr;
//}
