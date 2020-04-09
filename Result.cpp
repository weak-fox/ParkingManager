// Result.cpp: 实现文件
//

#include "stdafx.h"
#include "ParkingManager.h"
#include "Result.h"
#include "afxdialogex.h"
#include "AddCar.h"
#include "DelCar.h"


// Result 对话框

IMPLEMENT_DYNAMIC(Result, CDialogEx)

Result::Result(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESULT, pParent)
{

}

Result::~Result()
{
}

void Result::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Result, CDialogEx)
	ON_BN_CLICKED(IDOK, &Result::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Result::OnBnClickedButton1)
END_MESSAGE_MAP()


// Result 消息处理程序


BOOL Result::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// TODO:  在此添加您专用的创建代码
	CStdioFile file;
	CString str;
	char* p;
	if (file.Open(L"result.txt", CFile::modeRead))
		file.ReadString(str);
	ReadStringCharToUnicode(str);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Result::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	AddCar AC;
	AC.DoModal();
	CDialogEx::OnOK();
}


void Result::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	DelCar DC;
	DC.DoModal();
	CDialogEx::OnOK();
}
