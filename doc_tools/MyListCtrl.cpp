// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "doc_tools.h"
#include "MyListCtrl.h"


// MyListCtrl

IMPLEMENT_DYNAMIC(MyListCtrl, CWnd)

MyListCtrl::MyListCtrl()
{

}

MyListCtrl::~MyListCtrl()
{
}


BEGIN_MESSAGE_MAP(MyListCtrl, CWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()



// MyListCtrl 消息处理程序

BOOL MyListCtrl::Create(const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if (FALSE == CWnd::Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, rect, pParentWnd, nID))
	{
		return FALSE;
	}

	if (FALSE == m_list.Create(LVS_REPORT|LVS_SINGLESEL,rect,this, IDC_LIST1))
	{
		return FALSE;
	}
	m_list.ShowWindow(SW_SHOW);

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() |LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,_T("属性"));
	m_list.SetColumnWidth(0, 50);
	m_list.InsertColumn(1,_T("值"));
	m_list.SetColumnWidth(1, 100);

	m_list.InsertItem(DE_INT_LINE_O,	_T("HEX"));
	m_list.InsertItem(DE_INT_LINE_INT,	_T("整形"));
	m_list.InsertItem(DE_INT_LINE_UN_INT,	_T("非负整形"));
	m_list.InsertItem(DE_INT_LINE_DOUBLE,	_T("浮点型"));
	m_list.InsertItem(DE_INT_LINE_GBK,	_T("GBK"));
	return TRUE;
}



void MyListCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindow(m_list.GetSafeHwnd()))
	{
		::SetWindowPos(m_list.GetSafeHwnd(),NULL,0,0,cx,cy,SWP_NOOWNERZORDER );
	}
}

void MyListCtrl::SetHexString( const CString& cstrHexString )
{
	m_cstrOriginal = cstrHexString;

	CString cstrTemp;

	ToBuffer();

	ToInt();

	ToUnsigned();

	ToDouble();

	ToGBK();
}

void MyListCtrl::ToInt()
{
	CString cstrTemp;
	cstrTemp.Trim();

	if (m_buffer_ForNumber.GetSize() > sizeof(int))
	{
		cstrTemp = _T("(overflow)");
		m_list.SetItemText(DE_INT_LINE_INT,1,cstrTemp );
		return ;
	}
	if (NULL == m_buffer_ForNumber.GetBuffer())
	{
		cstrTemp = _T("(N/A)");
		m_list.SetItemText(DE_INT_LINE_INT,1,cstrTemp );
		return ;
	}
	int nTemp;
	nTemp = 0;
	memcpy(&nTemp, m_buffer_ForNumber.GetBuffer(), min(m_buffer_ForNumber.GetSize(),sizeof(int)));


	

	cstrTemp.Format(_T("%d"), nTemp);
	m_list.SetItemText(DE_INT_LINE_INT,1,cstrTemp );
}

char MyListCtrl::HexToChar( TCHAR cHigh, TCHAR cLow )
{
	return (char)(((cHigh << 4)& 0xF0) | (cLow & 0x0F) & 0xFF);
}

void MyListCtrl::ToBuffer()
{
	CString cstrTemp;
	cstrTemp = m_cstrOriginal;
	cstrTemp.Trim();
	m_list.SetItemText(DE_INT_LINE_O,1,cstrTemp );
	if (cstrTemp.IsEmpty())
	{
		return ;
	}

	char * p = m_buffer_ForNumber.NewBuffer( (cstrTemp.GetLength()+2)/3  );
	if (p == NULL)
	{
		return ;
	}
	char * pO = m_buffer_O.NewBuffer( (cstrTemp.GetLength()+2)/3 );
	if (pO == NULL)
	{
		return ;
	}
	pO += m_buffer_O.GetSize() - 1;
	LPCTSTR pSrc = cstrTemp;

	for ( int i = cstrTemp.GetLength()-1
		; i > 0
		; --i)
	{
		if (pSrc[i] != _T(' ')	&& pSrc[i-1] != _T(' '))
		{
			*p++ = HexToChar(pSrc[i-1],pSrc[i]);
			--i;
		}
	}

	for (int i = 0 ; i < m_buffer_ForNumber.GetSize(); ++i)
	{
		*pO-- = *p++;
	}
}

void MyListCtrl::ToUnsigned()
{
	CString cstrTemp;
	cstrTemp.Trim();

	if (m_buffer_ForNumber.GetSize() > sizeof(unsigned int))
	{
		cstrTemp = _T("(overflow)");
		m_list.SetItemText(DE_INT_LINE_UN_INT,1,cstrTemp );
		return ;
	}
	if (NULL == m_buffer_ForNumber.GetBuffer())
	{
		cstrTemp = _T("(N/A)");
		m_list.SetItemText(DE_INT_LINE_UN_INT,1,cstrTemp );
		return ;
	}
	unsigned int nTemp;
	nTemp = 0;
	memcpy(&nTemp, m_buffer_ForNumber.GetBuffer(), min(m_buffer_ForNumber.GetSize(),sizeof(unsigned int)));




	cstrTemp.Format(_T("%u"), nTemp);
	m_list.SetItemText(DE_INT_LINE_UN_INT,1,cstrTemp );
}

void MyListCtrl::ToDouble()
{
	CString cstrTemp;
	cstrTemp.Trim();

	if (m_buffer_ForNumber.GetSize() > sizeof(double))
	{
		cstrTemp = _T("(overflow)");
		m_list.SetItemText(DE_INT_LINE_DOUBLE,1,cstrTemp );
		return ;
	}
	if (NULL == m_buffer_ForNumber.GetBuffer())
	{
		cstrTemp = _T("(N/A)");
		m_list.SetItemText(DE_INT_LINE_DOUBLE,1,cstrTemp );
		return ;
	}
	double nTemp;
	nTemp = 0;
	memcpy(&nTemp, m_buffer_ForNumber.GetBuffer(), min(m_buffer_ForNumber.GetSize(),sizeof(double)));




	cstrTemp.Format(_T("%lf"), nTemp);
	m_list.SetItemText(DE_INT_LINE_DOUBLE,1,cstrTemp );
}

void MyListCtrl::ToGBK()
{
	CString cstrTemp;
	cstrTemp.Trim();

	if (NULL == m_buffer_O.GetBuffer())
	{
		cstrTemp = _T("(N/A)");
		m_list.SetItemText(DE_INT_LINE_GBK,1,cstrTemp );
		return ;
	}
	LPTSTR p = cstrTemp.GetBuffer(m_buffer_O.GetSize() + 2);
	memset(p,0, (m_buffer_O.GetSize()+2)* sizeof(TCHAR));

	int n = 0;
#ifdef _UNICODE
	n = MultiByteToWideChar(CP_ACP,0, m_buffer_O.GetBuffer(), m_buffer_O.GetSize(), p,m_buffer_O.GetSize());
#else
	memcpy(p,m_buffer_O.GetBuffer(),m_buffer_O.GetSize());
#endif
	

	if (n <=0)
	{
		n = m_buffer_O.GetSize();
	}

	cstrTemp.ReleaseBuffer(n);



	m_list.SetItemText(DE_INT_LINE_GBK,1,cstrTemp );
}