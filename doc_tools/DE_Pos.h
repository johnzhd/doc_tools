#pragma once

class DE_Pos
{
public:
	DE_Pos(void);
	~DE_Pos(void);
public:
	DWORD nF;
	DWORD nB;

	enum DE_POS_TYPE
	{
		POS_HEX = 0,
		POS_BUFF =1
	};
	DE_POS_TYPE nType;
public:
	DE_Pos& operator=(const DE_Pos& src)
	{
		nF = src.nF;
		nB = src.nB;
		nType = src.nType;
		return *this;
	};
};
