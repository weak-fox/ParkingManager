#pragma once

#include "LoginWindow.h"
#include "ParkingManager.h"
#include "CParkingManage.h"
// Manager 对话框
class Manager : public CDialogEx
{
	DECLARE_DYNAMIC(Manager)

public:
	Manager(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Manager();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Manager };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void OnBnClickedOk();
	afx_msg void OnPaint();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
