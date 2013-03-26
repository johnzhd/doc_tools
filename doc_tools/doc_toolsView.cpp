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

// doc_toolsView.cpp : Cdoc_toolsView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cdoc_toolsView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// Cdoc_toolsView ����/����

Cdoc_toolsView::Cdoc_toolsView()
{
	// TODO: �ڴ˴���ӹ������

}

Cdoc_toolsView::~Cdoc_toolsView()
{
}

BOOL Cdoc_toolsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// Cdoc_toolsView ����

void Cdoc_toolsView::OnDraw(CDC* /*pDC*/)
{
	Cdoc_toolsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// Cdoc_toolsView ��ӡ


void Cdoc_toolsView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL Cdoc_toolsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Cdoc_toolsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void Cdoc_toolsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// Cdoc_toolsView ���

#ifdef _DEBUG
void Cdoc_toolsView::AssertValid() const
{
	CView::AssertValid();
}

void Cdoc_toolsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cdoc_toolsDoc* Cdoc_toolsView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdoc_toolsDoc)));
	return (Cdoc_toolsDoc*)m_pDocument;
}
#endif //_DEBUG


// Cdoc_toolsView ��Ϣ�������

int Cdoc_toolsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ



	

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
