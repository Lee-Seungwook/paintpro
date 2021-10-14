#pragma once
#include "..\ImageTool\stdafx.h"
#include "..\ImageTool\IppImage\IppImage.h"

#ifdef _DLL_ENHANCE_
#define DLL_ENHANCE _declspec(dllexport)
#else
#define DLL_ENHANCE __declspec(dllimport)
#endif // _DLL_ENHANCE_

class DLL_ENHANCE EnhanceAPI
{
public:
	void APIINVERSE(IppByteImage& img);

	void APIBrightness(IppByteImage& img, int n);

	void APICBrightness(IppRgbImage& img, int n);

	void APIContrast(IppByteImage& img, int n);

	void APICContrast(IppRgbImage& img, int n);

	void APIGammaCorrection(IppByteImage& img, float gamma);

	void APICGammaCorrection(IppRgbImage& img, float gamma);

	void APIHistogram(IppByteImage& img, float histo[256]);

	void APIHistogramStrectching(IppByteImage& img);

	// ������׷� �յ�ȭ
	void APIHistogramEqualization(IppByteImage& img);

	// ������ ���� ���� ����
	bool APIAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

	// ������ ���� ���� ����
	bool APISub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

	// ������ ��� ���� ����
	bool APIAve(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

	// ������ ���� ���� ����
	bool APIDiff(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

	// ������ AND ���� ����
	bool APIAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

	// ������ OR ���� ����
	bool APIOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);


	// ��Ʈ ��� ���ϴ� ���� ����
	void APIBitPlane(IppByteImage& img1, IppByteImage& img2, int bit);
};
