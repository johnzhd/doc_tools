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

// doc_toolsDoc.cpp : Cdoc_toolsDoc ���ʵ��
//

#include "stdafx.h"
#include "doc_tools.h"

#include "doc_toolsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdoc_toolsDoc

IMPLEMENT_DYNCREATE(Cdoc_toolsDoc, CDocument)

BEGIN_MESSAGE_MAP(Cdoc_toolsDoc, CDocument)
END_MESSAGE_MAP()


// Cdoc_toolsDoc ����/����

Cdoc_toolsDoc::Cdoc_toolsDoc()
{
	// TODO: �ڴ����һ���Թ������

}

Cdoc_toolsDoc::~Cdoc_toolsDoc()
{
}

BOOL Cdoc_toolsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// Cdoc_toolsDoc ���л�

void Cdoc_toolsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// Cdoc_toolsDoc ���

#ifdef _DEBUG
void Cdoc_toolsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cdoc_toolsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cdoc_toolsDoc ����
