#pragma once


// CParkingManage 对话框

class CParkingManage : public CDialogEx
{
	DECLARE_DYNAMIC(CParkingManage)

public:
	CParkingManage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CParkingManage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ParkingManage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void ReadStringCharToUnicode(CString &str);
	CListCtrl ListCtrl;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton2();
	static int CALLBACK CompareByName(LPARAM lP1, LPARAM lP2, LPARAM lP);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
//	afx_msg void OnTimeChange();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

