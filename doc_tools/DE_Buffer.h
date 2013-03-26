#pragma once

class DE_Buffer
{
public:
	DE_Buffer(void);
	~DE_Buffer(void);
public:
	char * m_pData;
	DWORD m_nSize;
public:
	char * NewBuffer(DWORD n)
	{
		clear();
		m_pData = new char[n];
		m_nSize = n;
		return m_pData;
	}
	char * GetBuffer() const {
		return m_pData;
	};
	void SetBuffer(char * p){
		m_pData = p;
	};
	DWORD GetSize() const {
		return m_nSize;
	};
	void SetSize(DWORD n){
		m_nSize = n;
	};
public:
	void clear(){
		if (m_pData != NULL)
		{
			delete[] m_pData;
			m_pData = NULL;
		}
		m_nSize = 0;
	};
};
