#pragma once


// CarRec 对话框

class CarRec : public CDialogEx
{
	DECLARE_DYNAMIC(CarRec)

public:
	CarRec(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CarRec();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CARREC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CStatic m_picture1;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCancel();
};

