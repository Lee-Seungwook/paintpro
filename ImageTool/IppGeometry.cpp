#include "stdafx.h"
#include "IppGeometry.h"
#include "math.h"

const double PI = 3.14159265358979323846;

#include "ChatClienLibarary/GeometryAPI.h"
#pragma comment( lib, "ChatClienLibrary.lib" )

GeometryAPI api;

// �̵� ��ȯ �Լ� ����
void IppTranslate(IppByteImage& imgSrc, IppByteImage& imgDst, int sx, int sy)
{
	
	api.APITranslate(imgSrc, imgDst, sx, sy);
}

// �̵� ��ȯ �Լ� Ʈ���÷� ����
void IppTranslate(IppRgbImage& imgSrc, IppRgbImage& imgDst, int sx, int sy)
{
	
	api.APICTranslate(imgSrc, imgDst, sx, sy);
}


// �ֱٹ� �̿� ������ ����
void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	
	api.APIResizeNearest(imgSrc, imgDst, nw, nh);
}


void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	
	api.APIResizeBilinear(imgSrc, imgDst, nw, nh);
}


// 3�� ȸ�� �������� �̿��� ũ�� ��ȯ ����
void IppResizeCubic(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	
	api.APIResizeCubic(imgSrc, imgDst, nw, nh);
}

// �� ���� 4���� ���� �̿��Ͽ� ���� ���Ѵ�.
double cubic_interpolation(double v1, double v2, double v3, double v4, double d)
{
	double v, p1, p2, p3, p4;

	// �������� ����
	p1 = 2 * v2;
	p2 = -v1 + v3;
	p3 = 2 * v1 - 5 * v2 + 4 * v3 - v4;
	p4 = -v1 + 3 * v2 - 3 * v3 + v4;

	v = (p1 + d * (p2 + d * (p3 + d * p4))) / 2.;

	return v;
}


// ������ ȸ�� ��ȯ ����
void IppRotate(IppByteImage& imgSrc, IppByteImage& imgDst, double angle)
{
	
	api.APIRotate(imgSrc, imgDst, angle);
}


// ������ 90�� ȸ�� ��ȯ
void IppRotate90(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	
	api.APIRotate90(imgSrc, imgDst);
}

// ������ 180�� ȸ�� ��ȯ
void IppRotate180(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	
	api.APIRotate180(imgSrc, imgDst);
}

// ������ 270�� ȸ�� ��ȯ
void IppRotate270(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	
	api.APIRotate270(imgSrc, imgDst);
}


// ������ �¿� ���� ����
void IppMirror(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	
	api.APIMirror(imgSrc, imgDst);
}

// ������ ���� ���� ����
void IppFlip(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	
	api.APIFlip(imgSrc, imgDst);
}
