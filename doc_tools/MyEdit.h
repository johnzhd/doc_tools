#pragma once


// MyEdit

class MyEdit : public CEdit
{
	DECLARE_DYNAMIC(MyEdit)

public:
	MyEdit();
	virtual ~MyEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


