#pragma once

// AddCar 对话框
class AddCar : public CDialogEx
{
	DECLARE_DYNAMIC(AddCar)

public:
	AddCar(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddCar();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDCAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

void dataopen();


char* UnicodeToUtf8(CString unicode);

void ReadStringCharToUnicode(CString & str);

CString UTF8ToUnicode(const char* szUtf8);
