#pragma once


// MyDlg_Search �Ի���

class MyDlg_Search : public CDialog
{
	DECLARE_DYNAMIC(MyDlg_Search)

public:
	MyDlg_Search(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MyDlg_Search();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

public:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
