// MyDlg_Search.cpp : 实现文件
//

#include "stdafx.h"
#include "doc_tools.h"
#include "MyDlg_Search.h"

#include "MainFrm.h"
#include "doc_toolsView.h"


// MyDlg_Search 对话框

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

// MyDlg_Search 消息处理程序

BOOL MyDlg_Search::OnInitDialog()
{
	CDialog::OnInitDialog();

	ShowWindow(SW_SHOW);
	return TRUE;
}

void MyDlg_Search::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void MyDlg_Search::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void MyDlg_Search::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码

	char * pMark;
	DWORD nSize;
	int nStart,nF;
	//...
	CString cstrTemp;
	DE_Buffer buff;

	GetDlgItemText(IDC_EDIT1,cstrTemp);
	if (FALSE == MAIN_VIEW->HexString2Data(cstrTemp,buff))
	{
	}


	pMark = buff.GetBuffer();
	nSize = buff.GetSize();
	MAIN_VIEW->GetCulSel(NULL,&nStart);
	if (nStart < 0)
	{
		nStart = 0;
	}
	MAIN_VIEW->LengthChange(nStart,DE_Pos::POS_HEX);

	MAIN_VIEW->SearchBuffer(pMark,nSize,nStart,nF,TRUE);
}

void MyDlg_Search::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	char * pMark;
	DWORD nSize;
	int nStart,nF;
	//...
	CString cstrTemp;
	DE_Buffer buff;
	GetDlgItemText(IDC_EDIT2,cstrTemp);
	

	pMark = buff.NewBuffer(cstrTemp.GetLength()*sizeof(TCHAR));

	memcpy(pMark,cstrTemp,cstrTemp.GetLength()*sizeof(TCHAR));

	nSize = buff.GetSize();
	MAIN_VIEW->GetCulSel(NULL,&nStart);
	if (nStart < 0)
	{
		nStart = 0;
	}

	MAIN_VIEW->SearchBuffer(pMark,nSize,nStart,nF,TRUE);
}

void MyDlg_Search::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	char * pMark;
	DWORD nSize;
	int nStart,nF;
	//...
	CString cstrTemp;
	DE_Buffer buff;
	GetDlgItemText(IDC_EDIT3,cstrTemp);
	
	DWORD n = _ttoi(cstrTemp);

	pMark = buff.NewBuffer(sizeof(DWORD));
	memcpy(pMark,&n,sizeof(DWORD));


	pMark = buff.GetBuffer();
	nSize = buff.GetSize();
	MAIN_VIEW->GetCulSel(NULL,&nStart);
	if (nStart < 0)
	{
		nStart = 0;
	}

	MAIN_VIEW->SearchBuffer(pMark,nSize,nStart,nF,TRUE);
}
