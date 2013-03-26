#include "StdAfx.h"
#include "DE_Buffer.h"

DE_Buffer::DE_Buffer(void)
:m_pData(NULL)
,m_nSize(0)
{
}

DE_Buffer::~DE_Buffer(void)
{
	clear();
}
