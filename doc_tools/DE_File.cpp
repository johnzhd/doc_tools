#include "StdAfx.h"
#include "DE_File.h"

DE_File::DE_File(void)
{
}

DE_File::~DE_File(void)
{
}

BOOL DE_File::GetFileData( LPCTSTR pFileName, DE_Buffer& bufOut )
{
	HANDLE hF = CreateFile(pFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,NULL,NULL);
	if (hF == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	DWORD dwSize,dwHigh = 0;
	dwSize = GetFileSize(hF,&dwHigh);
	if (dwHigh != 0)
	{
		CloseHandle(hF);
		return FALSE;// too long for show
	}

	char * p = bufOut.NewBuffer(dwSize);

	DWORD dwStep,dwOffest = 0;

	while ( dwOffest < dwSize 
		&& TRUE == ReadFile(hF,p + dwOffest,dwSize - dwOffest, &dwStep,NULL))
	{
		dwOffest += dwStep;
	}


	bufOut.SetSize(dwOffest);

	CloseHandle(hF);
	hF = NULL;

	return TRUE;
}