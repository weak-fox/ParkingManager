// CarRec.cpp: 实现文件
//

#include "stdafx.h"
#include "ParkingManager.h"
#include "CarRec.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include "Result.h"
using namespace std;
using namespace cv;
int flag=0;
// CarRec 对话框
CString strFilePath;
CRect rect;
CDC* pDC;
HDC hDC;
CWnd* pwnd;
VideoCapture cap;
Mat frame;
IMPLEMENT_DYNAMIC(CarRec, CDialogEx)
void MatToCImage(Mat& mat, CImage& cImage);
CarRec::CarRec(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CARREC, pParent)
{

}

CarRec::~CarRec()
{
}

void CarRec::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_picture1);
}


BEGIN_MESSAGE_MAP(CarRec, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CarRec::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CarRec::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CarRec::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CarRec::OnBnClickedButton3)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, &CarRec::OnBnClickedButton4)
	ON_BN_CLICKED(IDCANCEL, &CarRec::OnBnClickedCancel)
END_MESSAGE_MAP()


// CarRec 消息处理程序


void CarRec::OnBnClickedButton1()
{

	// TODO: 在此添加控件通知处理程序代码

	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("image Files(*.bmp; *.jpg;*.png)|*.JPG;*.PNG;*.BMP|All Files (*.*) |*.*|"), this);
	fileDlg.DoModal();
	strFilePath = fileDlg.GetPathName();		//文件路径
	if (strFilePath == _T(""))
	{
		return;
	}
	strFilePath.Replace(_T("//"), _T("////"));
	USES_CONVERSION;//这两行是CString转string
	string pathName(W2A(strFilePath));//此处是在CString中读取的图片路径然后再转化为string，大家也可以直接写到string类型的pathName中
	//读取图片  
	Mat img = cv::imread(pathName);
	imwrite("1.bmp", img);
	//显示图片  
	HWND hWndDisplay = GetDlgItem(IDC_IMAGE)->GetSafeHwnd();
	if (img.channels() < 3)
	{
		return;
	}

	//构造将要显示的Mat版本图片  
	RECT rect;
	::GetClientRect(hWndDisplay, &rect);
	cv::Mat imgShow(abs(rect.top - rect.bottom), abs(rect.right - rect.left), CV_8UC3);
	resize(img, imgShow, imgShow.size());

	//在控件上显示要用到的CImage类图片  
	ATL::CImage CI;
	int w = imgShow.cols;//宽    
	int h = imgShow.rows;//高    
	int channels = imgShow.channels();//通道数    
	CI.Create(w, h, 8 * channels);

	//CI像素的复制  
	uchar *pS;
	uchar *pImg = (uchar *)CI.GetBits();//得到CImage数据区地址    
	int step = CI.GetPitch();
	for (int i = 0; i < h; i++)
	{
		pS = imgShow.ptr<uchar>(i);
		for (int j = 0; j < w; j++)
		{
			for (int k = 0; k < 3; k++)
				*(pImg + i * step + j * 3 + k) = pS[j * 3 + k];
			//注意到这里的step不用乘以3    
		}
	}

	//在控件显示图片  
	HDC dc;
	dc = ::GetDC(hWndDisplay);
	CI.Draw(dc, 0, 0);
	::ReleaseDC(hWndDisplay, dc);
	CI.Destroy();
}


void CarRec::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnOK();
}



void CarRec::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	cap.open(0);
	cap >> frame;
	CDC* pDC = GetDlgItem(IDC_IMAGE)->GetDC();//得到图片控件的指针对象。
	HDC hDC = pDC->GetSafeHdc();//得到可以操作的句柄。这种形式类似于 CWND 和HWND
	CImage cimg;
	MatToCImage(frame, cimg);//Mat格式转为 CImage类型。
	CRect rect;
	GetDlgItem(IDC_IMAGE)->GetClientRect(&rect);
	cimg.Draw(hDC, rect);
	ReleaseDC(pDC);
	SetTimer(1, 1, NULL);
	flag = 0;

}

void MatToCImage(Mat& mat, CImage& cImage)
{
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy();//这一步是防止重复利用造成内存问题
	cImage.Create(width, height, 8 * channels);

	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); //获取CImage的像素存贮区的指针
	int step = cImage.GetPitch();//每行的字节数,注意这个返回值有正有负

	// 如果是1个通道的图像(灰度图像) DIB格式才需要对调色板设置  
	// CImage中内置了调色板，我们要对他进行赋值：
	if (1 == channels)
	{
		RGBQUAD* ColorTable;
		int MaxColors = 256;
		//这里可以通过CI.GetMaxColorTableEntries()得到大小(如果你是CI.Load读入图像的话)  
		ColorTable = new RGBQUAD[MaxColors];
		cImage.GetColorTable(0, MaxColors, ColorTable);//这里是取得指针  
		for (int i = 0; i < MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;
			//BYTE和uchar一回事，但MFC中都用它  
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}
		cImage.SetColorTable(0, MaxColors, ColorTable);
		delete[]ColorTable;
	}


	for (int i = 0; i < height; i++)
	{
		ps = mat.ptr<uchar>(i);
		for (int j = 0; j < width; j++)
		{
			if (1 == channels)
			{
				*(pimg + i * step + j) = ps[j];
				//*(pimg + i*step + j) = 105;
			}
			else if (3 == channels)
			{
				*(pimg + i * step + j * 3) = ps[j * 3];
				*(pimg + i * step + j * 3 + 1) = ps[j * 3 + 1];
				*(pimg + i * step + j * 3 + 2) = ps[j * 3 + 2];
			}
		}
	}

}


void CarRec::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	cap >> frame;
	CDC* pDC = GetDlgItem(IDC_IMAGE)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	//IplImage img = frame;
	CImage cimg;
	MatToCImage(frame, cimg);
	CRect rect;
	GetDlgItem(IDC_IMAGE)->GetClientRect(&rect);
	cimg.Draw(hDC, rect);
	ReleaseDC(pDC);
	CDialogEx::OnTimer(nIDEvent);
}


void CarRec::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (flag == 1) return;
	cap >> frame;
	imwrite("1.bmp", frame);
	KillTimer(1);
	cap.release();
	flag = 1;
}


void CarRec::OnPaint()
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


void CarRec::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (flag != 1) {
		KillTimer(1);
		cap.release();
	}
	CDialogEx::OnClose();
}


void CarRec::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	WinExec("Rec.exe", SW_HIDE);
	REC = 1;
	Result R;
	R.DoModal();
}


void CarRec::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (flag != 1) {
		KillTimer(1);
		cap.release();
	}
	CDialogEx::OnCancel();
}
