#include "stdafx.h"

#include "IppColor.h"
#include "IppFeature.h"
#include "IppGeometry.h"
#include "IppImage/IppEnhance.h"
#include "IppFilter.h"
#include "IppSegment.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <algorithm>

#include "ChatClienLibarary/ColorAPI.h"
#pragma comment( lib, "ChatClienLibrary.lib" )

const double PI = 3.14159265358979323846;
const float  PI_F = 3.14159265358979323846f;

ColorAPI api;

// ���� ����
void IppInverse(IppRgbImage& img)
{
	api.APIInverse(img);
}

// ������׷�
void IppHistogram(IppRgbImage& img, float Rhisto[256], float Ghisto[256], float Bhisto[256])
{
	api.APIHistogram(img, Rhisto, Ghisto, Bhisto);
}

// ������׷� ��Ʈ��Ī
void IppHistogramStretching(IppRgbImage& img)
{
	api.APIHistogramStretching(img);
}

// ������׷� �յ�ȭ
void IppHistogramEqualization(IppRgbImage& img)
{
	api.APIHistogramEqualization(img);
}

// ���� ����
bool IppAdd(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	return api.APIAdd(img1, img2, img3);
}

// ���� ����
bool IppSub(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	return api.APISub(img1, img2, img3);
}

// ��� ���� ����
bool IppAve(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	return api.APIAve(img1, img2, img3);
}

// ���� ���
bool IppDiff(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	return api.APIDiff(img1, img2, img3);
}

// AND ����
bool IppAND(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	return api.APIAND(img1, img2, img3);
}

// OR ����
bool IppOR(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	return api.APIOR(img1, img2, img3);
}

// ��� �� ����
void IppFilterMean(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIFilterMean(imgSrc, imgDst);
}

// ���� ��հ� ���͸�
void IppFilterWeightedMean(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIFilterWeightedMean(imgSrc, imgDst);
}

// ���ö�þ� ����
void IppFilterLaplacian(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIFilterLaplacian(imgSrc, imgDst);
}

// ����� ����ũ ����
void IppFilterUnsharpMask(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIFilterUnsharpMask(imgSrc, imgDst);
}

// ���̺ν�Ʈ ����
void IppFilterHighboost(IppRgbImage& imgSrc, IppRgbImage& imgDst, float alpha)
{
	api.APIFilterHighboost(imgSrc, imgDst, alpha);
}

// ����þ� ���� ���� ����
void IppNoiseGaussian(IppRgbImage& imgSrc, IppRgbImage& imgDst, int amount)
{
	api.APINoiseGaussian(imgSrc, imgDst, amount);
}

// �ұ�& ���� ���� ����
void IppNoiseSaltNPepper(IppRgbImage& imgSrc, IppRgbImage& imgDst, int amount)
{
	api.APINoiseSaltNPepper(imgSrc, imgDst, amount);
}

// �̵�� ����
void IppFilterMedian(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIFilterMedian(imgSrc, imgDst);
}

// �ι��� ���� ����
void IppEdgeRoberts(IppRgbImage& img, IppRgbImage& imgEdge)
{
	api.APIEdgeRoberts(img, imgEdge);
}

// �Һ� ���� ����
void IppEdgeSobel(IppRgbImage& img, IppRgbImage& imgEdge)
{
	api.APIEdgeSobel(img, imgEdge);
}

void IppResizeNearest(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh)
{
	api.APIResizeNearest(imgSrc, imgDst, nw, nh);
}

void IppResizeBilinear(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh)
{
	api.APIResizeBilinear(imgSrc, imgDst, nw, nh);
}

// �������� ����
void IppMorphologyColorErosion(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIMorphologyColorErosion(imgSrc, imgDst);
}

// �������� ��â
void IppMorphologyColorDilation(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIMorphologyColorDilation(imgSrc, imgDst);
}

// ������ ����
void IppMorphologyColorOpening(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIMorphologyColorOpening(imgSrc, imgDst);
}

// ������ �ݱ�
void IppMorphologyColorClosing(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	api.APIMorphologyColorClosing(imgSrc, imgDst);
}

void IppResizeCubic(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh)
{
	api.APIResizeCubic(imgSrc, imgDst, nw, nh);
}

//-------------------------------------------------------------------------
// R, G, B, H, S, I �� ������ [0, 1]
//-------------------------------------------------------------------------
void RGB_TO_HSI(double R, double G, double B, double& H, double& S, double& I)
{
	api.APIRGB_TO_HSI(R, G, B, H, S, I);
}

//-------------------------------------------------------------------------
// R, G, B, H, S, I �� ������ [0, 1]
//-------------------------------------------------------------------------
void HSI_TO_RGB(double H, double S, double I, double& R, double& G, double& B)
{
	api.APIHSI_TO_RGB(H, S, I, R, G, B);

}

//-------------------------------------------------------------------------
// R, G, B, Y, U, V �� ������ [0, 255]
//-------------------------------------------------------------------------
void RGB_TO_YUV(BYTE R, BYTE G, BYTE B, BYTE& Y, BYTE& U, BYTE& V)
{
	api.APIRGB_TO_YUV(R, G, B, Y, U, V);
}

//-------------------------------------------------------------------------
// R, G, B, Y, U, V �� ������ [0, 255]
//-------------------------------------------------------------------------
void YUV_TO_RGB(BYTE Y, BYTE U, BYTE V, BYTE& R, BYTE& G, BYTE& B)
{
	api.APIYUV_TO_RGB(Y, U, V, R, G, B);
}

// RGB ���� ��� ������
void IppColorSplitRGB(IppRgbImage& imgColor, IppByteImage& imgR, IppByteImage& imgG, IppByteImage& imgB)
{
	api.APIColorSplitRGB(imgColor, imgR, imgG, imgB);
}

// HSI ���� ��� ������
void IppColorSplitHSI(IppRgbImage& imgColor, IppByteImage& imgH, IppByteImage& imgS, IppByteImage& imgI)
{
	api.APIColorSplitHSI(imgColor, imgH, imgS, imgI);
}

// YUV ���� ��� ������
void IppColorSplitYUV(IppRgbImage& imgColor, IppByteImage& imgY, IppByteImage& imgU, IppByteImage& imgV)
{
	api.APIColorSplitYUV(imgColor, imgY, imgU, imgV);
} 

// RGB ���� ��� ��ġ��
bool IppColorCombineRGB(IppByteImage& imgR, IppByteImage& imgG, IppByteImage& imgB, IppRgbImage& imgColor)
{
	return api.APIColorCombineRGB(imgR, imgG, imgB, imgColor);
}

// HSI ���� ��� ��ġ��
bool IppColorCombineHSI(IppByteImage& imgH, IppByteImage& imgS, IppByteImage& imgI, IppRgbImage& imgColor)
{
	return api.APIColorCombineHSI(imgH, imgS, imgI, imgColor);
}

// YUV ���� ��� ��ġ��
bool IppColorCombineYUV(IppByteImage& imgY, IppByteImage& imgU, IppByteImage& imgV, IppRgbImage& imgColor)
{
	return api.APIColorCombineYUV(imgY, imgU, imgV, imgColor);
}

void IppColorEdge(IppRgbImage& imgSrc, IppByteImage& imgEdge)
{
	api.APIColorEdge(imgSrc, imgEdge);
}

