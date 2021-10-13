#include "..\stdafx.h"
#include "IppEnhance.h"
#include "..\pch.h"
#include "math.h"

#include "..\ChatClienLibarary\EnhanceAPI.h"
#pragma comment( lib, "ChatClienLibrary.lib" )

EnhanceAPI api;

// �׷��� ������ ���� ����
void IppInverse(IppByteImage& img)
{
	api.APIINVERSE(img);
}


// �׷��� ������ ���� ��� ����
void IppBrightness(IppByteImage& img, int n)
{
	api.APIBrightness(img, n);
}

 // Ʈ�� �÷� ���� ��� ����
void IppBrightness(IppRgbImage& img, int n)
{
	api.APICBrightness(img, n);
}

// �׷��� ������ ��Ϻ� ����
void IppContrast(IppByteImage& img, int n)
{
	api.APIContrast(img, n);
}

// Ʈ���÷� ��Ϻ� ����
void IppContrast(IppRgbImage& img, int n)
{
	api.APICContrast(img, n);
}


// �׷��� ������ ���� ���� ����
void IppGammaCorrection(IppByteImage& img, float gamma)
{
	api.APIGammaCorrection(img, gamma);
}
// pow�� ���� ������ ���� ���(���ڰ� �ŵ������� ����, ���ڰ� �ŵ����� �����ϴ� ����)

// Ʈ�� �÷� ���� ����
void IppGammaCorrection(IppRgbImage& img, float gamma)
{
	api.APICGammaCorrection(img, gamma);
}

// ������׷�
void IppHistogram(IppByteImage& img, float histo[256])
{
	api.APIHistogram(img, histo);
}

// ������׷� ��Ʈ��Ī �Լ�
void IppHistogramStretching(IppByteImage& img)
{
	api.APIHistogramStrectching(img);
}

// ������׷� �յ�ȭ
void IppHistogramEqualization(IppByteImage& img)
{
	api.APIHistogramEqualization(img);
}

// ���� ���� ���� ����
bool IppAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	api.APIAdd(img1, img2, img3);

	return true;
}

// ���� ���� ���� ����
bool IppSub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	api.APISub(img1, img2, img3);

	return true;
}

// ���� ��� ���� ����
bool IppAve(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	api.APIAve(img1, img2, img3);

	return true;
}

// ���� ���� ���� ���� (���� �״�� �������� ����Ѵ�.)
bool IppDiff(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	api.APIDiff(img1, img2, img3);

	return true;
}

// ������ AND ���� ����
bool IppAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	api.APIAND(img1, img2, img3);

	return true;
}

// ������ OR ���� ����
bool IppOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	api.APIOR(img1, img2, img3);

	return true;
}

// ��Ʈ ��� ���ϱ�
void IppBitPlane(IppByteImage& img1, IppByteImage& img2, int bit)
{
	api.APIBitPlane(img1, img2, bit);
}