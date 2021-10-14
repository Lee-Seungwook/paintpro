#pragma once
#include "..\ImageTool\stdafx.h"
#include "..\ImageTool\IppImage\IppImage.h"

#ifdef _DLL_GEOMETRY_
#define DLL_GEOMETRY _declspec(dllexport)
#else		GEOMETRY
#define DLL_GEOMETRY __declspec(dllimport)
#endif // _DLL_GEOMETRY_

class DLL_GEOMETRY GeometryAPI
{
public:
	// �̵� ��ȯ
	void APITranslate(IppByteImage& imgSrc, IppByteImage& imgDst, int sx, int sy);
	void APICTranslate(IppRgbImage& imgSrc, IppRgbImage& imgDst, int sx, int sy);

	// �ֱٹ� �̿� ������
	void APIResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);

	// �缱�� ������
	void APIResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);

	// 3�� ȸ�� ������
	void APIResizeCubic(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);
	double cubic_interpolation(double v1, double v2, double v3, double v4, double d); // ���� 4���� ���� �̿��� �������� �̿��Ͽ� ���� ��ȯ


	// ������ ȸ�� ��ȯ
	void APIRotate(IppByteImage& imgSrc, IppByteImage& imgDst, double angle); // angle�� �ð���� ȸ�� ����

	// ������ 90�� ȸ�� ��ȯ
	void APIRotate90(IppByteImage& imgSrc, IppByteImage& imgDst);
	// ������ 180�� ȸ�� ��ȯ
	void APIRotate180(IppByteImage& imgSrc, IppByteImage& imgDst);
	// ������ 270�� ȸ�� ��ȯ
	void APIRotate270(IppByteImage& imgSrc, IppByteImage& imgDst);


	// ������ �¿� ����
	void APIMirror(IppByteImage& imgSrc, IppByteImage& imgDst);

	// ������ ���� ����
	void APIFlip(IppByteImage& imgSrc, IppByteImage& imgDst);
};