// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// doc_toolsView.h : Cdoc_toolsView 类的接口
//


#pragma once

#include "MyEdit.h"
#include "DE_Buffer.h"
#include "DE_Pos.h"

class Cdoc_toolsDoc;


class Cdoc_toolsView : public CView
{
protected: // 仅从序列化创建
	Cdoc_toolsView();
	DECLARE_DYNCREATE(Cdoc_toolsView)

// 属性
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



// 操作
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


// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Cdoc_toolsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // doc_toolsView.cpp 中的调试版本
inline Cdoc_toolsDoc* Cdoc_toolsView::GetDocument() const
   { return reinterpret_cast<Cdoc_toolsDoc*>(m_pDocument); }
#endif

