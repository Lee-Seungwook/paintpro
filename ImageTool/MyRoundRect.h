#pragma once
#include <afx.h>
class CMyRoundRect :
	public CObject
{
	DECLARE_SERIAL(CMyRoundRect)
public:
	COLORREF m_RoundRectColor;
	COLORREF m_FillRoundRect;
	CPoint m_start;
	CPoint m_end;
	int m_nWidth; // ���� ���� 
	int m_nStyle; // �� ��Ÿ��
	CArray<CPoint, CPoint&> m_ptArray;
public:
	CMyRoundRect();
	virtual ~CMyRoundRect();
	CMyRoundRect(COLORREF PenColor, int PenWidth, int PenStyle, COLORREF FillColor);
	void Serialize(CArchive& ar);
	void Setend(CPoint& end);
	void Draw(CDC *pDC);
};

