#include "pch.h"
#include "IppFilter.h"
#include "stdafx.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <algorithm>

#include "..\ChatClienLibrary\FilterAPI.h"
#pragma comment( lib, "ChatClienLibrary.lib" )

const double PI = 3.14159265358979323846;
const float  PI_F = 3.14159265358979323846f;

FilterAPI api;

// ��հ� ����
void IppFilterMean(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIFilterMean(imgSrc, imgDst);
}

// ���� ��հ� ����
void IppFilterWeightedMean(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIFilterWeightedMean(imgSrc, imgDst);
}


// ����þ� ���� ����
void IppFilterGaussian(IppByteImage& imgSrc, IppFloatImage& imgDst, float sigma)
{
	api.APIFilterGaussian(imgSrc, imgDst, sigma);
}


// ���ö�þ� ���� ����
void IppFilterLaplacian(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIFilterLaplacian(imgSrc, imgDst);
}


 // ����� ����ũ ���͸�
void IppFilterUnsharpMask(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIFilterUnsharpMask(imgSrc, imgDst);
}


// ���̺ν�Ʈ ����
void IppFilterHighboost(IppByteImage& imgSrc, IppByteImage& imgDst, float alpha)
{
	api.APIFilterHighboost(imgSrc, imgDst, alpha);
}



// ����þ� ���� ���� ���� 
void IppNoiseGaussian(IppByteImage& imgSrc, IppByteImage& imgDst, int amount)
{
	api.APINoiseGaussian(imgSrc, imgDst, amount);
}


// �ұ� ���� ���� ����
void IppNoiseSaltNPepper(IppByteImage& imgSrc, IppByteImage& imgDst, int amount) // amount�� �ұ� ���� ������ �߰��� �ȼ��� ���� �����ϴ� ����
{
	api.APINoiseSaltNPepper(imgSrc, imgDst, amount);
}


// �̵�� ���� ����
void IppFilterMedian(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIFilterMedian(imgSrc, imgDst);
}

// ���漺 Ȯ�� ���� ����
void IppFilterDiffusion(IppByteImage& imgSrc, IppFloatImage& imgDst, float lambda, float k, int iter)
{
	api.APIFilterDiffusion(imgSrc, imgDst, lambda, k, iter);
}