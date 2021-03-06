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

// doc_toolsView.cpp : Cdoc_toolsView 类的实现
//

#include "stdafx.h"
#include "doc_tools.h"

#include "doc_toolsDoc.h"
#include "doc_toolsView.h"


#include "MainFrm.h"

#include "DE_File.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdoc_toolsView

IMPLEMENT_DYNCREATE(Cdoc_toolsView, CView)

BEGIN_MESSAGE_MAP(Cdoc_toolsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cdoc_toolsView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// Cdoc_toolsView 构造/析构

Cdoc_toolsView::Cdoc_toolsView()
{
	// TODO: 在此处添加构造代码

}

Cdoc_toolsView::~Cdoc_toolsView()
{
}

BOOL Cdoc_toolsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cdoc_toolsView 绘制

void Cdoc_toolsView::OnDraw(CDC* /*pDC*/)
{
	Cdoc_toolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// Cdoc_toolsView 打印


void Cdoc_toolsView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL Cdoc_toolsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cdoc_toolsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cdoc_toolsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Cdoc_toolsView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cdoc_toolsView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// Cdoc_toolsView 诊断

#ifdef _DEBUG
void Cdoc_toolsView::AssertValid() const
{
	CView::AssertValid();
}

void Cdoc_toolsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cdoc_toolsDoc* Cdoc_toolsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdoc_toolsDoc)));
	return (Cdoc_toolsDoc*)m_pDocument;
}
#endif //_DEBUG


// Cdoc_toolsView 消息处理程序

int Cdoc_toolsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rect;
	GetClientRect(&rect);

	m_edit.Create(ES_MULTILINE | WS_CHILD |WS_VISIBLE |WS_VSCROLL |ES_NOHIDESEL | ES_WANTRETURN | EM_SETEVENTMASK,rect,this,IDC_EDIT1);

	m_edit.ShowWindow(SW_SHOW);

	m_edit.SetFont(GetFont());

	return 0;
}

void Cdoc_toolsView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect);

	m_edit.MoveWindow(rect);
}

void Cdoc_toolsView::SetEditText( const CString& cstrText )
{
	m_cstrHexString = cstrText;
	m_edit.SetWindowText(cstrText);
}

void Cdoc_toolsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值



	

	CView::OnLButtonUp(nFlags, point);
}

void Cdoc_toolsView::OpenNewFileByName( CString cstrFile )
{
	DE_File de;
	if (FALSE == de.GetFileData(cstrFile,m_bufferOriginal))
	{
		return ;
	}

	if (FALSE == Data2HexString(m_bufferOriginal,m_cstrHexString))
	{
		return ;
	}
	
	SetEditText(m_cstrHexString);
}


void Cdoc_toolsView::CharToHex( char cIn, TCHAR& cHigh, TCHAR& cLow )
{
	cHigh = cIn >> 4;
	cLow = cIn;
	CharForShow(cHigh);
	CharForShow(cLow);
}

void Cdoc_toolsView::HexToChar( TCHAR cHigh, TCHAR cLow, char& cOut )
{
	CharClearShow(cHigh);
	CharClearShow(cLow);
	cOut = 0xFF & (((cHigh<<4)&0xF0) | (cLow&0x0F));
}


BOOL Cdoc_toolsView::Data2HexString( const DE_Buffer& buf, CString& cstrOut )
{
	LPTSTR pOut = cstrOut.GetBuffer(buf.GetSize() * 4);
	char * p = buf.GetBuffer();
	for (DWORD i = 0; i < buf.GetSize(); ++i)
	{
		CharToHex(p[i], pOut[3*i],pOut[3*i+1]);
		pOut[3*i + 2] = _T(' ');
	}
	cstrOut.ReleaseBuffer(3*buf.GetSize());

	return TRUE;
}

BOOL Cdoc_toolsView::HexString2Data( const CString& cstrIn, DE_Buffer& buf, TCHAR pSpace )
{
	CString cstrTemp;
	cstrTemp = cstrIn;

	cstrTemp.MakeUpper();
	cstrTemp.Remove(pSpace);
	char * p = buf.NewBuffer((cstrTemp.GetLength()+1)/2);
	LPCTSTR pWork = cstrTemp;

	TCHAR cH,cL;
	for (DWORD i = 0; i < buf.GetSize(); ++i)
	{
		cH = *pWork++;
		cL = *pWork++;
		HexToChar(cH,cL, *p++);
	}
	return TRUE;
}


void Cdoc_toolsView::PosChange( DE_Pos dpSrc, IN OUT DE_Pos& dpDst )
{
	if (dpDst.nType == dpSrc.nType)
	{
		dpDst = dpSrc;
	}

	DE_Pos dpTemp;
	dpTemp.nType = DE_Pos::POS_BUFF;

	switch (dpSrc.nType)
	{
	case DE_Pos::POS_BUFF:
		dpTemp = dpSrc;
		break;
	case DE_Pos::POS_HEX:
		dpTemp.nF = dpSrc.nF/3;
		dpTemp.nB = dpSrc.nB/3;
		break;
	default:
		break;
	}


	switch(dpDst.nType)
	{
	case DE_Pos::POS_BUFF:
		dpDst = dpTemp;
		break;
	case DE_Pos::POS_HEX:
		dpDst.nF = dpTemp.nF*3;
		dpDst.nB = dpTemp.nB*3;
		break;
	default:
		break;
	}

}

void Cdoc_toolsView::LengthChange( int& l, DE_Pos::DE_POS_TYPE typeIn, DE_Pos::DE_POS_TYPE typeOut /*= DE_Pos::POS_BUFF*/ )
{
	if (typeIn == typeOut)
	{
		return ;
	}
	int nTemp;
	switch (typeIn)
	{
	case DE_Pos::POS_BUFF:
		nTemp = l;
		break;
	case DE_Pos::POS_HEX:
		nTemp = l/3;
		break;
	default:
		break;
	}


	switch(typeOut)
	{
	case DE_Pos::POS_BUFF:
		l = nTemp;
		break;
	case DE_Pos::POS_HEX:
		l = nTemp*3;
		break;
	default:
		break;
	}
}

BOOL Cdoc_toolsView::SearchBuffer( const char * pMark, const DWORD nSize, int nStart, int& nF, BOOL bSel /*= TRUE*/ )
{
	char * pSrc =  m_bufferOriginal.GetBuffer();
	DWORD nTotal = m_bufferOriginal.GetSize();
	if (pMark == NULL
		|| nSize == 0
		|| pSrc == NULL
		|| nTotal == 0
		|| nTotal < nSize)
	{
		return FALSE;
	}

	if (nStart<0 || nStart + nSize > nTotal)
	{
		nStart = 0;
	}

	for (DWORD pos = nStart,check = 0,next_pos = 0; pos < nTotal; )
	{
		// no enough bytes left...
		if (pos + nSize > nTotal)
		{
			break;
		}

		//march main loop
		for (check = 0, next_pos = 0; check < nSize; ++check)
		{
			//march each byte
			if (pSrc[pos + check] != pMark[check])
			{
				break;
			}

			//prepare for next loop, try to find the first byte marched
			if (next_pos == 0 && check != 0 && pMark[0] == pSrc[pos + check])
			{
				next_pos = pos + check;
			}
		}

		//march whole size! should be marched!
		if (check == nSize)
		{
			// Found!
			nF = pos;
			if (bSel == TRUE)
			{
				DE_Pos dp;
				dp.nType = DE_Pos::POS_BUFF;
				dp.nF = nF;
				dp.nB = nF + nSize;
				SetEditCulSel(dp);
			}
			return TRUE;
		}

		//prepare for next loop, try to find the first byte marched
		// use the prepared pos
		if (next_pos != 0)
		{
			pos = next_pos;
		}
		else
		{
			//find next pos, or push the pos over
			for ( ++pos; pos < nTotal; ++pos)
			{
				if (pSrc[pos] == pMark[0])
				{
					break;
				}
			}
		}


	}
	return FALSE;
}

void Cdoc_toolsView::SetEditCulSel( const DE_Pos& dp )
{
	DE_Pos dpText;
	dpText.nType = DE_Pos::POS_HEX;
	PosChange(dp,dpText);
	m_edit.SetSel((int)dpText.nF, (int)dpText.nB, TRUE);
}

void Cdoc_toolsView::GetCulSel( int* nF, int* nB )
{
	int nf,nb;
	m_edit.GetSel(nf,nb);
	if (nF != NULL)
	{
		*nF = nf;
	}
	if (nB != NULL)
	{
		*nB = nb;
	}
}
