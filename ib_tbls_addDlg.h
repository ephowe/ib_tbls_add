
// ib_tbls_addDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// Cib_tbls_addDlg �Ի���
class Cib_tbls_addDlg : public CDialogEx
{
// ����
public:
	Cib_tbls_addDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IB_TBLS_ADD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	bool is_run;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
