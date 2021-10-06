#pragma once
#include <afx.h>
class CMyEllipse :
	public CObject
{
	DECLARE_SERIAL(CMyEllipse)
public:
	COLORREF m_EllipseColor;
	COLORREF m_FillEllipse;
	CPoint m_start;
	CPoint m_end;
	int m_nWidth; // ���� ���� 
	int m_nStyle; // �� ��Ÿ��
	CArray<CPoint, CPoint&> m_ptArray;
public:
	CMyEllipse();
	virtual ~CMyEllipse();
	CMyEllipse(COLORREF PenColor, int PenWidth, int PenStyle, COLORREF FillColor);
	void Serialize(CArchive& ar);
	void Setend(CPoint& end);
	void Draw(CDC *pDC);
};