#pragma once
#include <afx.h>
class CMyData :
	public CObject
{
	DECLARE_SERIAL(CMyData)
public:
	COLORREF m_PenColor;
	int m_nWidth; // ���� ���� 
	//int m_nStyle; // �� ��Ÿ��
	CArray<CPoint, CPoint&> m_ptArray;
public:
	CMyData();
	virtual ~CMyData();
	CMyData(COLORREF PenColor, int PenWidth);
	void Serialize(CArchive& ar);
	void Draw(CDC *pDC);
};

