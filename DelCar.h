#pragma once


// DelCar 对话框

class DelCar : public CDialogEx
{
	DECLARE_DYNAMIC(DelCar)

public:
	DelCar(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DelCar();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELCAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
char* UnicodeToUtf81(CString unicode);

void ReadStringCharToUnicode1(CString & str);
