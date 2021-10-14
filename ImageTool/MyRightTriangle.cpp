#include "pch.h"
#include "MyRightTriangle.h"

IMPLEMENT_SERIAL(CMyRightTriangle, CObject, 1)

CMyRightTriangle::CMyRightTriangle(void)
{
	m_TriangleColor = RGB(0, 0, 0);
	m_FillTriangle = RGB(255, 255, 255);
	m_nStyle = 0;
	m_nWidth = 5;
}

CMyRightTriangle::~CMyRightTriangle(void)
{

}

CMyRightTriangle::CMyRightTriangle(COLORREF PenColor, int PenWidth, int PenStyle, COLORREF Fillcolor)
{
	m_TriangleColor = PenColor;
	m_FillTriangle = Fillcolor;
	m_nWidth = PenWidth;
	m_nStyle = PenStyle;
}

void CMyRightTriangle::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << m_TriangleColor << m_nWidth << m_nStyle << m_FillTriangle;
		m_ptArray.Serialize(ar);
	}
	else {
		ar >> m_TriangleColor >> m_nWidth >> m_nStyle >> m_FillTriangle;
		m_ptArray.Serialize(ar);
	}
}

void CMyRightTriangle::Setend(CPoint& end) // �̰ŷ� �׷��ִ� ���� ������ ���̶� �Ǵܵ�
{
	m_end = end;
}

void CMyRightTriangle::Draw(CDC *pDC)
{
	LOGBRUSH lbr;
	lbr.lbStyle = BS_SOLID;
	lbr.lbColor = m_TriangleColor;
	lbr.lbHatch = 0;

	CPen pen(PS_GEOMETRIC | m_nStyle, m_nWidth, &lbr, 0, 0); // ���� ����
	CPen *pOldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(m_FillTriangle);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	int m_nend = m_ptArray.GetSize() - 1;

	pDC->BeginPath(); // ��Ŷ�
	pDC->MoveTo(m_ptArray[0]);
	pDC->LineTo(m_ptArray[m_nend]);
	pDC->LineTo(m_ptArray[0].x, m_ptArray[m_nend].y);
	pDC->LineTo(m_ptArray[0]);
	pDC->EndPath(); // �̰Ŷ�
	pDC->StrokeAndFillPath(); // �� ģ���� ������ �������� �׷����� �ʴ´�. ������ ������ �������� �׷����� �����̴�.
	
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(oldBrush);
}