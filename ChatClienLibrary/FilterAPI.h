#pragma once
#include "..\ImageTool\stdafx.h"
#include "..\ImageTool\IppImage\IppImage.h"

#ifdef _DLL_FILTER_
#define DLL_FILTER _declspec(dllexport)
#else		
#define DLL_FILTER __declspec(dllimport)
#endif // _DLL_FILTER_

class DLL_FILTER FilterAPI
{
public:
	// ���� ����
// ��� �� ���� ����
	void APIFilterMean(IppByteImage& imgSrc, IppByteImage& imgDst); // imgSrc ���� 3 x 3 ũ���� ����ũ�� �̿��� ��հ� ���͸��� ����, imgDst�� ����

	// ���� ��� �� ���͸� ����
	void APIFilterWeightedMean(IppByteImage& imgSrc, IppByteImage& imgDst); // imgSrc ���� 3 x 3 ũ���� ����ũ�� �̿��� ���� ��հ� ���͸��� ����, imgDst�� ����

	// ����þ� ���� ����
	void APIFilterGaussian(IppByteImage& imgSrc, IppFloatImage& imgDst, float sigma); // imgsrc ���� ǥ�� ������ sigma�� ����þ� ���͸��� ����, imgDst�� ����

	// ���ö�þ� ����
	void APIFilterLaplacian(IppByteImage& imgSrc, IppByteImage& imgDst);

	// ����� ����ũ ����
	void APIFilterUnsharpMask(IppByteImage& imgSrc, IppByteImage& imgDst);

	// ���̺ν�Ʈ ����
	void APIFilterHighboost(IppByteImage& imgSrc, IppByteImage& imgDst, float alpha);

	// ���� �߰�
	// ����þ� ���� �߰�
	void APINoiseGaussian(IppByteImage& imgSrc, IppByteImage& imgDst, int amount);

	// �ұ�, ���� ���� �߰�
	void APINoiseSaltNPepper(IppByteImage& imgSrc, IppByteImage& imgDst, int amount);


	// ���� ���� 
	// �̵�� ���͸� �Լ� �߰� 
	void APIFilterMedian(IppByteImage& imgSrc, IppByteImage& imgDst);

	// ���漺 Ȯ�� ���� �Լ� �߰�
	void APIFilterDiffusion(IppByteImage& imgSrc, IppFloatImage& imgDst, float lambda, float k, int iter);
};