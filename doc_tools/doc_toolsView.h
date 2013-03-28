// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// doc_toolsView.h : Cdoc_toolsView ��Ľӿ�
//


#pragma once

#include "MyEdit.h"
#include "DE_Buffer.h"
#include "DE_Pos.h"

class Cdoc_toolsDoc;


class Cdoc_toolsView : public CView
{
protected: // �������л�����
	Cdoc_toolsView();
	DECLARE_DYNCREATE(Cdoc_toolsView)

// ����
public:
	Cdoc_toolsDoc* GetDocument() const;

	MyEdit m_edit;

	void OpenNewFileByName(CString cstrFile);
	void SetNewBuffer(const DE_Buffer& buffer);
	CString m_cstrHexString;
	DE_Buffer m_bufferOriginal;


	void PosChange(DE_Pos dpSrc, IN OUT DE_Pos& dpDst);// should set dpDst.nType
	void LengthChange(int& l, DE_Pos::DE_POS_TYPE typeIn, DE_Pos::DE_POS_TYPE typeOut = DE_Pos::POS_BUFF);

	BOOL SearchBuffer(const char * pMark, const DWORD nSize, int nStart, int& nF, BOOL bSel = TRUE);

	void SetEditCulSel(const DE_Pos& dp);



// ����
public:
	void SetEditText( const CString& cstrText );

	void GetCulSel(int* nF, int* nB);

public:
	BOOL Data2HexString(const DE_Buffer& buf, CString& cstrOut);
	BOOL HexString2Data(const CString& cstrIn, DE_Buffer& buf, TCHAR pSpace = _T(' '));


protected:
	void CharToHex(char cIn, TCHAR& cHigh, TCHAR& cLow);
	void CharForShow( TCHAR& c )
	{
		c &= 0x0F;
		if (0 <= c && c < 10)
		{
			c = _T('0') + c;
		}
		else
		{
			c = _T('A') + (c - 10);
		}
	}

	void CharClearShow( TCHAR&c)
	{
		if (_T('0')<=c && c <= _T('9'))
		{
			c -= _T('0');
		}
		else if (_T('A') <= c && c <= _T('Z'))
		{
			c = c - _T('A') + 10;
		}
		else if (_T('a') <= c && c <= _T('z'))
		{
			c = c - _T('a') + 10;
		}
		else
		{
			ASSERT(FALSE);
			c = 0;
		}
	}
	void HexToChar(TCHAR cHigh, TCHAR cLow, char& cOut);


// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~Cdoc_toolsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // doc_toolsView.cpp �еĵ��԰汾
inline Cdoc_toolsDoc* Cdoc_toolsView::GetDocument() const
   { return reinterpret_cast<Cdoc_toolsDoc*>(m_pDocument); }
#endif

