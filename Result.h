#pragma once


// Result 对话框

class Result : public CDialogEx
{
	DECLARE_DYNAMIC(Result)

public:
	Result(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Result();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
