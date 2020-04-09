#pragma once


// ShowCar 对话框

class ShowCar : public CDialogEx
{
	DECLARE_DYNAMIC(ShowCar)

public:
	ShowCar(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ShowCar();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOWCAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
};
