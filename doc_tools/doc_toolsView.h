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

// ����
public:
	void SetEditText( const CString& cstrText );

public:
	BOOL Data2HexString(const DE_Buffer& buf, CString& cstrOut);
	BOOL HexString2Data(const CString& cstrOut, DE_Buffer& buf);


protected:
	void CharToHex(char cIn, TCHAR& cHigh, TCHAR& cLow);
	void CharForShow( TCHAR& c )
	{
		c &= 0x0F;
		if (0 <= c && c < 10)
		{
			c = '0' + c;
		}
		else
		{
			c = 'A' + (c - 10);
		}
	}

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

