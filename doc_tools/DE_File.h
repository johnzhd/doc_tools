#pragma once

#include "DE_Buffer.h"

class DE_File
{
public:
	DE_File(void);
	~DE_File(void);
public:

	BOOL GetFileData(LPCTSTR pFileName, DE_Buffer& bufOut);


};
