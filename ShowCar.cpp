// ShowCar.cpp: 实现文件
//

#include "stdafx.h"
#include "ParkingManager.h"
#include "ShowCar.h"
#include "afxdialogex.h"


// ShowCar 对话框

IMPLEMENT_DYNAMIC(ShowCar, CDialogEx)

ShowCar::ShowCar(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOWCAR, pParent)
{

}

ShowCar::~ShowCar()
{
}

void ShowCar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShowCar, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ShowCar 消息处理程序


int ShowCar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect   rcTemp;
	int x, y;
	if (NUM < 20)
		x = 30 + 50 * NUM;
	else
		x = 30 + 50 * 20;
	y = 45 + 70*(NUM/20+(int)(NUM % 20!=0)) + 10;
	rcTemp.BottomRight() = CPoint(x, y);
	rcTemp.TopLeft() = CPoint(0, 0);
	MoveWindow(&rcTemp);
	return 0;
}


void ShowCar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CDialog::OnPaint();
	CPen cpen;
	UpdateWindow();				// 告诉系统对话框已更新过
	CDC* pDC = GetDC();
	CBrush br;
	CRect rcClient;
	GetClientRect(rcClient);	// 获取对话框客户区大小
	CRect rcDraw;
	CString str;
	int i = 0;
	for (i=0;i<NUM/20;i++)
		for (int j = 0; j < 20; j++)
		{
			int p = 20 * i + j;
			if (*(PNUM + p) == 0)
			{
				cpen.CreatePen(PS_SOLID,3,RGB(0, 255, 0));
				pDC->SelectObject(&cpen);
			}
			else
			{
				cpen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
				pDC->SelectObject(&cpen);
			}
			str.Format(_T("%d"), p + 1);
			rcDraw.SetRect(10 + j * 50, 10 + 70 * i, 10 + j * 50 + 40, 10 + 70 * i + 60);
			br.CreateStockObject(NULL_BRUSH);
			pDC->SelectObject(&br);
			pDC->Rectangle(rcDraw);
			pDC->TextOut(10 + j * 50, 10 + 70 * i, str);
			cpen.DeleteObject();
			br.DeleteObject();
		}
	if (i == NUM / 20)
		for (int j = 0; j < NUM%20; j++)
		{
			int p = 20 * i + j;
			if (*(PNUM + p) == 0)
			{
				cpen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
				pDC->SelectObject(&cpen);
			}
			else
			{
				cpen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
				pDC->SelectObject(&cpen);
			}
			str.Format(_T("%d"), p + 1);
			rcDraw.SetRect(10 + j * 50, 10 + 70 * i, 10 + j * 50 + 40, 10 + 70 * i + 60);
			br.CreateStockObject(NULL_BRUSH);
			pDC->SelectObject(&br);
			pDC->Rectangle(rcDraw);
			pDC->TextOut(10 + j * 50, 10 + 70 * i, str);
			cpen.DeleteObject();
			br.DeleteObject();
		}

	
	//CBrush *oldBrush = pDC->SelectObject(&brush);
	
	////pDC->SelectObject(oldBrush);
}
