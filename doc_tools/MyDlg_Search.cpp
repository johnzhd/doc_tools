// MyDlg_Search.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "doc_tools.h"
#include "MyDlg_Search.h"

#include "doc_toolsView.h"


// MyDlg_Search �Ի���

IMPLEMENT_DYNAMIC(MyDlg_Search, CDialog)

MyDlg_Search::MyDlg_Search(CWnd* pParent /*=NULL*/)
	: CDialog(MyDlg_Search::IDD, pParent)
{

}

MyDlg_Search::~MyDlg_Search()
{
}

void MyDlg_Search::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDlg_Search, CDialog)
	ON_BN_CLICKED(IDCANCEL, &MyDlg_Search::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &MyDlg_Search::OnBnClickedOk)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &MyDlg_Search::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MyDlg_Search::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MyDlg_Search::OnBnClickedButton3)
END_MESSAGE_MAP()

// MyDlg_Search ��Ϣ�������

BOOL MyDlg_Search::OnInitDialog()
{
	CDialog::OnInitDialog();

	ShowWindow(SW_SHOW);
	return TRUE;
}

void MyDlg_Search::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void MyDlg_Search::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void MyDlg_Search::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	CEdit * p;
	CRect rect;

	p = (CEdit *)GetDlgItem(IDC_EDIT1);

	if (IsWindow(p->GetSafeHwnd()))
	{
		p->GetWindowRect(&rect);
		ScreenToClient(&rect);
		::SetWindowPos(p->GetSafeHwnd(),NULL,0,0,cx-rect.left,rect.Height(),SWP_NOOWNERZORDER|SWP_NOMOVE );
	}
	p = (CEdit *)GetDlgItem(IDC_EDIT2);

	if (IsWindow(p->GetSafeHwnd()))
	{
		p->GetWindowRect(&rect);
		ScreenToClient(&rect);
		::SetWindowPos(p->GetSafeHwnd(),NULL,0,0,cx-rect.left,rect.Height(),SWP_NOOWNERZORDER|SWP_NOMOVE );
	}
	p = (CEdit *)GetDlgItem(IDC_EDIT3);

	if (IsWindow(p->GetSafeHwnd()))
	{
		p->GetWindowRect(&rect);
		ScreenToClient(&rect);
		::SetWindowPos(p->GetSafeHwnd(),NULL,0,0,cx-rect.left,rect.Height(),SWP_NOOWNERZORDER|SWP_NOMOVE );
	}
}

void MyDlg_Search::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	char * pMark;
	DWORD nSize,nStart,nF;
	//...

	

	MAIN_VIEW->SearchBuffer(pMark,nSize,nStart,nF,TRUE);

	pMark;//free
}

void MyDlg_Search::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char * pMark;
	DWORD nSize,nStart,nF;
	//...



	MAIN_VIEW->SearchBuffer(pMark,nSize,nStart,nF,TRUE);
	pMark;//free
}

void MyDlg_Search::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char * pMark;
	DWORD nSize,nStart,nF;
	//...



	MAIN_VIEW->SearchBuffer(pMark,nSize,nStart,nF,TRUE);
	pMark;//free
}
