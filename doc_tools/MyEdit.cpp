// MyEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "doc_tools.h"
#include "MyEdit.h"

#include "MainFrm.h"


// MyEdit

IMPLEMENT_DYNAMIC(MyEdit, CEdit)

MyEdit::MyEdit()
{

}

MyEdit::~MyEdit()
{
}


BEGIN_MESSAGE_MAP(MyEdit, CEdit)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// MyEdit 消息处理程序



void MyEdit::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CString cstrTemp;
	CString cstrText;
	CString cstrF1,cstrF2;
	GetWindowText(cstrText);
	int nF,nB;
	GetSel(nF,nB);
	if (nF <= 0 )
	{
		nF = 0;
	}
	else
	{
		cstrF1 = cstrText.Mid(nF-1,1);
		cstrF2 = cstrText.Mid(nF,1);

		if (cstrF1 != ' ' && cstrF2 != ' ')
		{
			nF--;
		}
	}

	if ( nB == -1)
	{
		nB = cstrText.GetLength();
	}
	if (nB < cstrText.GetLength()-1)
	{
		cstrF1 = cstrText.Mid(nB-1,1);
		cstrF2 = cstrText.Mid(nB,1);
		if (cstrF1 != ' ' && cstrF2 != ' ')
		{
			nB++;
		}
	}

	SetSel(nF,nB);

	

	

	cstrTemp = cstrText.Mid(nF,nB-nF);
	cstrTemp.Trim();
	MAINFRAME->SetHexStringShow(cstrTemp);

	CEdit::OnLButtonUp(nFlags, point);
}
