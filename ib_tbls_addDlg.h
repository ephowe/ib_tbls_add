
// ib_tbls_addDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// Cib_tbls_addDlg 对话框
class Cib_tbls_addDlg : public CDialogEx
{
// 构造
public:
	Cib_tbls_addDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IB_TBLS_ADD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	bool is_run;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_in;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
};
