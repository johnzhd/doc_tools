#pragma once

#include "DE_Buffer.h"
// MyListCtrl

class MyListCtrl : public CWnd
{
	DECLARE_DYNAMIC(MyListCtrl)

public:
	MyListCtrl();
	virtual ~MyListCtrl();

public:
	CListCtrl m_list;

	void SetHexString(const CString& cstrHexString);


protected:
#define DE_INT_LINE_O	(0)
#define DE_INT_LINE_INT	(1)
#define DE_INT_LINE_UN_INT	(2)
#define DE_INT_LINE_DOUBLE	(3)
#define DE_INT_LINE_GBK	(4)
	CString m_cstrOriginal;
	void ToBuffer();
	void ToInt();
	void ToUnsigned();
	void ToDouble();
	void ToGBK();
	DE_Buffer m_buffer_ForNumber;
	DE_Buffer m_buffer_O;

protected:
	char HexToChar(TCHAR cHigh, TCHAR cLow);




public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


