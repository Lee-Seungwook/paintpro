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

const double PI = 3.14159265358979323846;
const float  PI_F = 3.14159265358979323846f;

// ���� ����
void IppInverse(IppRgbImage& img)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i].r = 255 - p[i].r;
		p[i].g = 255 - p[i].g;
		p[i].b = 255 - p[i].b;
	}
}

// ������׷�
void IppHistogram(IppRgbImage& img, float Rhisto[256], float Ghisto[256], float Bhisto[256])
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	// ������׷� ���
	int Rcnt[256], Gcnt[256], Bcnt[256];
	memset(Rcnt, 0, sizeof(int) * 256);
	memset(Gcnt, 0, sizeof(int) * 256);
	memset(Bcnt, 0, sizeof(int) * 256);
	for (int i = 0; i < size; i++)
	{
		// �ȼ��� ������ ���
		Rcnt[p[i].r]++;
		Gcnt[p[i].g]++;
		Bcnt[p[i].b]++;
	}

	// ������׷� ����ȭ(histogram normalization)
	for (int i = 0; i < 256; i++)
	{
		Rhisto[i] = static_cast<float>(Rcnt[i]) / size; // cnt �迭�� ����� ���� ��ü �ȼ��� ������ ������ ����ȭ�� ������׷� ���� histo �迭�� ����
		Ghisto[i] = static_cast<float>(Gcnt[i]) / size;
		Bhisto[i] = static_cast<float>(Bcnt[i]) / size;
	}
}

// ������׷� ��Ʈ��Ī
void IppHistogramStretching(IppRgbImage& img)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	// �ִ�, �ּ� �׷��̽����� �� ���
	BYTE R_max, R_min, G_max, G_min, B_max, B_min;
	R_max = R_min = p[0].r; // �ʱ�ȭ
	G_max = G_min = p[0].g;
	B_max = B_min = p[0].b;
	for (int i = 1; i < size; i++)
	{
		if (R_max < p[i].r) R_max = p[i].r;
		if (R_min > p[i].r) R_min = p[i].r;

		if (G_max < p[i].g) R_max = p[i].g;
		if (G_min > p[i].g) R_min = p[i].g;

		if (B_max < p[i].b) R_max = p[i].b;
		if (B_min > p[i].b) R_min = p[i].b;
	}

	if (R_max == R_min || G_max == G_min || B_max == B_min)
		return;

	// ������׷� ��Ʈ��Ī
	for (int i = 0; i < size; i++)
	{
		p[i].r = (p[i].r - R_min) * 255 / (R_max - R_min); // ���� ����
		p[i].g = (p[i].g - G_min) * 255 / (G_max - G_min); // ���� ����
		p[i].b = (p[i].b - B_min) * 255 / (B_max - B_min); // ���� ����
	}
}

// ������׷� �յ�ȭ
void IppHistogramEqualization(IppRgbImage& img)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	// ������׷� ���
	float Rhist[256], Ghist[256], Bhist[256];
	IppHistogram(img, Rhist, Ghist, Bhist);

	// ������׷� ���� �Լ� ���
	float Rcdf[256] = { 0, 0, };
	float Gcdf[256] = { 0, 0, };
	float Bcdf[256] = { 0, 0, };

	Rcdf[0] = Rhist[0];
	Gcdf[0] = Ghist[0];
	Bcdf[0] = Bhist[0];

	for (int i = 1; i < 256; i++)
	{
		Rcdf[i] = Rcdf[i - 1] + Rhist[i];
		Gcdf[i] = Gcdf[i - 1] + Ghist[i];
		Bcdf[i] = Bcdf[i - 1] + Bhist[i];
	}

	// ������׷� �յ�ȭ
	for (int i = 0; i < size; i++)
	{
		p[i].r = static_cast<BYTE>(limit(Rcdf[p[i].r] * 255));
		p[i].g = static_cast<BYTE>(limit(Gcdf[p[i].g] * 255));
		p[i].b = static_cast<BYTE>(limit(Bcdf[p[i].b] * 255));
	}
}

// ���� ����
bool IppAdd(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE *p1 = img1.GetPixels();
	RGBBYTE *p2 = img2.GetPixels();
	RGBBYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i].r = limit(p1[i].r + p2[i].r); // ���� ���� ����
		p3[i].g = limit(p1[i].g + p2[i].g);
		p3[i].b = limit(p1[i].b + p2[i].b);
	}

	return true;
}

// ���� ����
bool IppSub(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE *p1 = img1.GetPixels();
	RGBBYTE *p2 = img2.GetPixels();
	RGBBYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i].r = limit(p1[i].r - p2[i].r); // ���� ���� ����
		p3[i].g = limit(p1[i].g - p2[i].g);
		p3[i].b = limit(p1[i].b - p2[i].b);
	}

	return true;
}

// ��� ���� ����
bool IppAve(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE *p1 = img1.GetPixels();
	RGBBYTE *p2 = img2.GetPixels();
	RGBBYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i].r = (p1[i].r + p2[i].r) / 2;
		p3[i].g = (p1[i].g - p2[i].g) / 2;
		p3[i].b = (p1[i].b - p2[i].b) / 2;
	}

	return true;
}

// ���� ���
bool IppDiff(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE *p1 = img1.GetPixels();
	RGBBYTE *p2 = img2.GetPixels();
	RGBBYTE *p3 = img3.GetPixels();

	int Rdiff, Gdiff, Bdiff;
	for (int i = 0; i < size; i++)
	{
		Rdiff = p1[i].r - p2[i].r; // ������ ���� ���� ����
		Gdiff = p1[i].g - p2[i].g; // ������ ���� ���� ����
		Bdiff = p1[i].b - p2[i].b; // ������ ���� ���� ����

		p3[i].r = static_cast<BYTE>((Rdiff >= 0) ? Rdiff : -Rdiff); // ���밪 ��ȯ
		p3[i].g = static_cast<BYTE>((Gdiff >= 0) ? Gdiff : -Gdiff); // ���밪 ��ȯ
		p3[i].b = static_cast<BYTE>((Bdiff >= 0) ? Bdiff : -Bdiff); // ���밪 ��ȯ
	}

	return true;
}

// AND ����
bool IppAND(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE *p1 = img1.GetPixels();
	RGBBYTE *p2 = img2.GetPixels();
	RGBBYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i].r = limit(p1[i].r & p2[i].r); // ���� ���� ����
		p3[i].g = limit(p1[i].g & p2[i].g);
		p3[i].b = limit(p1[i].b & p2[i].b);
	}

	return true;
}

// OR ����
bool IppOR(IppRgbImage& img1, IppRgbImage& img2, IppRgbImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	RGBBYTE *p1 = img1.GetPixels();
	RGBBYTE *p2 = img2.GetPixels();
	RGBBYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i].r = limit(p1[i].r | p2[i].r); // ���� ���� ����
		p3[i].g = limit(p1[i].g | p2[i].g);
		p3[i].b = limit(p1[i].b | p2[i].b);
	}

	return true;
}

// ��� �� ����
void IppFilterMean(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc; // ���� ������ �����ε����� Ŭ������ ���� ����, �̹��� ����

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int mask[3][3] = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1},
	};

	int i, j, m, n, Rsum, Gsum, Bsum;
	for (j = 1; j < h - 1; j++) // �ֿܰ� �ȼ��� ������� �ʴ´�.
		for (i = 1; i < w - 1; i++) // ���� �ȼ�
		{
			Rsum = 0;
			Gsum = 0;
			Bsum = 0;
			for (m = 0; m < 3; m++) // ����ũ �迭
				for (n = 0; n < 3; n++)
				{
					Rsum += (pSrc[j - 1 + m][i - 1 + n].r * mask[m][n]); // ���� �ȼ��� 1���� �����߱� ������ 1�� ���ش�.
					Gsum += (pSrc[j - 1 + m][i - 1 + n].g * mask[m][n]); // ���� �ȼ��� 1���� �����߱� ������ 1�� ���ش�.
					Bsum += (pSrc[j - 1 + m][i - 1 + n].b * mask[m][n]); // ���� �ȼ��� 1���� �����߱� ������ 1�� ���ش�.
				}

			pDst[j][i].r = static_cast<BYTE>(limit(Rsum / 9. + 0.5)); // ����ũ�� �� ������ �����ش�, 0.5�� �ݿø��ε�
			pDst[j][i].g = static_cast<BYTE>(limit(Gsum / 9. + 0.5)); // ����ũ�� �� ������ �����ش�, 0.5�� �ݿø��ε�
			pDst[j][i].b = static_cast<BYTE>(limit(Bsum / 9. + 0.5)); // ����ũ�� �� ������ �����ش�, 0.5�� �ݿø��ε�
		}
}

// ���� ��հ� ���͸�
void IppFilterWeightedMean(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc; // ���� ������ �����ε����� Ŭ������ ���� ����, �̹��� ����

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int mask[3][3] = {
		{1, 2, 1},
		{2, 4, 2},
		{1, 2, 1},
	};

	int i, j, m, n, Rsum, Gsum ,Bsum;
	for (j = 1; j < h - 1; j++) // �ֿܰ� �ȼ��� ������� �ʴ´�.
		for (i = 1; i < w - 1; i++) // ���� �ȼ�
		{
			Rsum = 0;
			Gsum = 0;
			Bsum = 0;
			for (m = 0; m < 3; m++) // ����ũ �迭
				for (n = 0; n < 3; n++)
				{
					Rsum += (pSrc[j - 1 + m][i - 1 + n].r * mask[m][n]); // ���� �ȼ��� 1���� �����߱� ������ 1�� ���ش�.
					Gsum += (pSrc[j - 1 + m][i - 1 + n].g * mask[m][n]); // ���� �ȼ��� 1���� �����߱� ������ 1�� ���ش�.
					Bsum += (pSrc[j - 1 + m][i - 1 + n].b * mask[m][n]); // ���� �ȼ��� 1���� �����߱� ������ 1�� ���ش�.
				}

			pDst[j][i].r = static_cast<BYTE>(limit(Rsum / 16. + 0.5)); // ����ũ�� �� ������ �����ش�, 0.5�� �ݿø��ε�
			pDst[j][i].g = static_cast<BYTE>(limit(Gsum / 16. + 0.5)); // ����ũ�� �� ������ �����ش�, 0.5�� �ݿø��ε�
			pDst[j][i].b = static_cast<BYTE>(limit(Bsum / 16. + 0.5)); // ����ũ�� �� ������ �����ش�, 0.5�� �ݿø��ε�
		}
}

// ���ö�þ� ����
void IppFilterLaplacian(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h); // ��� ������ ���� ���������ν� ��� �ȼ� ���� 0���� �ʱ�ȭ

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j, Rsum, Gsum, Bsum;
	for (j = 1; j < h - 1; j++) // 4���⿡ ���� �ȼ� ���� ���� �����Ͽ� ��� �ȼ� ���� ���
		for (i = 1; i < w - 1; i++) // �ֿܰ� �ȼ��� ���꿡�� ����
		{
			Rsum = pSrc[j - 1][i].r + pSrc[j][i - 1].r + pSrc[j + 1][i].r + pSrc[j][i + 1].r - 4 * pSrc[j][i].r;
			Gsum = pSrc[j - 1][i].g + pSrc[j][i - 1].g + pSrc[j + 1][i].g + pSrc[j][i + 1].g - 4 * pSrc[j][i].g;
			Bsum = pSrc[j - 1][i].b + pSrc[j][i - 1].b + pSrc[j + 1][i].b + pSrc[j][i + 1].b - 4 * pSrc[j][i].b;

			pDst[j][i].r = static_cast<BYTE>(limit(Rsum + 128));
			pDst[j][i].g = static_cast<BYTE>(limit(Gsum + 128));
			pDst[j][i].b = static_cast<BYTE>(limit(Bsum + 128));
		}
}

// ����� ����ũ ����
void IppFilterUnsharpMask(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j, Rsum, Gsum, Bsum;
	for (j = 1; j < h - 1; j++) // 4���⿡ ���� �ȼ� ���� ���� �����Ͽ� ��� �ȼ� ���� ���
		for (i = 1; i < w - 1; i++)
		{
			Rsum = 5 * pSrc[j][i].r - pSrc[j - 1][i].r - pSrc[j][i - 1].r - pSrc[j + 1][i].r - pSrc[j][i + 1].r;
			Gsum = 5 * pSrc[j][i].g - pSrc[j - 1][i].g - pSrc[j][i - 1].g - pSrc[j + 1][i].g - pSrc[j][i + 1].g;
			Bsum = 5 * pSrc[j][i].b - pSrc[j - 1][i].b - pSrc[j][i - 1].b - pSrc[j + 1][i].b - pSrc[j][i + 1].b;

			pDst[j][i].r = static_cast<BYTE>(limit(Rsum));
			pDst[j][i].g = static_cast<BYTE>(limit(Gsum));
			pDst[j][i].b = static_cast<BYTE>(limit(Bsum));
		}
}

// ���̺ν�Ʈ ����
void IppFilterHighboost(IppRgbImage& imgSrc, IppRgbImage& imgDst, float alpha)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	float Rsum, Gsum, Bsum;

	for (j = 1; j < h - 1; j++) // 4���⿡ ���� �ȼ� ���� ���� �����Ͽ� ��� �ȼ� ���� ���
		for (i = 1; i < w - 1; i++)
		{
			Rsum = (4 + alpha) * pSrc[j][i].r - pSrc[j - 1][i].r - pSrc[j][i - 1].r - pSrc[j + 1][i].r - pSrc[j][i + 1].r; // alpha ������ ��Ϻ� �����Ѵ�.
			Gsum = (4 + alpha) * pSrc[j][i].g - pSrc[j - 1][i].g - pSrc[j][i - 1].g - pSrc[j + 1][i].g - pSrc[j][i + 1].g; // alpha ������ ��Ϻ� �����Ѵ�.
			Bsum = (4 + alpha) * pSrc[j][i].b - pSrc[j - 1][i].b - pSrc[j][i - 1].b - pSrc[j + 1][i].b - pSrc[j][i + 1].b; // alpha ������ ��Ϻ� �����Ѵ�.
			pDst[j][i].r = static_cast<BYTE>(limit(Rsum + 0.5f)); // �ݿø��Ͽ� ���������� ��ȯ�Ѵ�.
			pDst[j][i].g = static_cast<BYTE>(limit(Gsum + 0.5f)); // �ݿø��Ͽ� ���������� ��ȯ�Ѵ�.
			pDst[j][i].b = static_cast<BYTE>(limit(Bsum + 0.5f)); // �ݿø��Ͽ� ���������� ��ȯ�Ѵ�.
		}
}

// ����þ� ���� ���� ����
void IppNoiseGaussian(IppRgbImage& imgSrc, IppRgbImage& imgDst, int amount)
{
	int size = imgSrc.GetSize();

	imgDst = imgSrc;
	RGBBYTE* pDst = imgDst.GetPixels();

	unsigned int seed = static_cast<unsigned int>(time(NULL)); //  �ý��� �ð��� �� ������ �ҷ��� �õ� ������ ���
	std::default_random_engine generator(seed); // 
	std::normal_distribution<double> distribution(0.0, 1.0); // ����þ� ����(���� ���� ����),

	double rn;
	for (int i = 0; i < size; i++)
	{
		rn = distribution(generator) * 255 * amount / 100;
		pDst[i].r = static_cast<BYTE>(limit(pDst[i].r + rn));
		pDst[i].g = static_cast<BYTE>(limit(pDst[i].g + rn));
		pDst[i].b = static_cast<BYTE>(limit(pDst[i].b + rn));
	}
}

// �ұ�& ���� ���� ����
void IppNoiseSaltNPepper(IppRgbImage& imgSrc, IppRgbImage& imgDst, int amount)
{
	int size = imgSrc.GetSize();

	imgDst = imgSrc;
	RGBBYTE* pDst = imgDst.GetPixels();

	unsigned int seed = static_cast<unsigned int>(time(NULL));
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(0, size - 1); // �ұ� ���� ���� ������ ���� ����

	int num = size * amount / 100; // ������ �߰��� �ȼ��� ������ ����
	for (int i = 0; i < num; i++)
	{
		pDst[distribution(generator)] = (i & 0x01) * 255; // ������ �߰��� ��ǥ
	}
}

// �̵�� ����
void IppFilterMedian(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	BYTE mR[9], mG[9], mB[9];

	for (j = 1; j < h - 1; j++) // ���� ���� ����ϱ� ���� �ݺ��� �� sort �Լ� ����
		for (i = 1; i < w - 1; i++)
		{
			mR[0] = pSrc[j - 1][i - 1].r; mR[1] = pSrc[j - 1][i].r; mR[2] = pSrc[j - 1][i + 1].r;
			mR[3] = pSrc[j][i - 1].r; mR[4] = pSrc[j][i].r; mR[5] = pSrc[j][i + 1].r;
			mR[6] = pSrc[j + 1][i - 1].r; mR[7] = pSrc[j + 1][i].r; mR[8] = pSrc[j + 1][i + 1].r;

			mG[0] = pSrc[j - 1][i - 1].g; mG[1] = pSrc[j - 1][i].g; mG[2] = pSrc[j - 1][i + 1].g;
			mG[3] = pSrc[j][i - 1].g; mG[4] = pSrc[j][i].g; mG[5] = pSrc[j][i + 1].g;
			mG[6] = pSrc[j + 1][i - 1].g; mG[7] = pSrc[j + 1][i].g; mG[8] = pSrc[j + 1][i + 1].g;

			mB[0] = pSrc[j - 1][i - 1].b; mB[1] = pSrc[j - 1][i].b; mB[2] = pSrc[j - 1][i + 1].b;
			mB[3] = pSrc[j][i - 1].b; mB[4] = pSrc[j][i].b; mB[5] = pSrc[j][i + 1].b;
			mB[6] = pSrc[j + 1][i - 1].b; mB[7] = pSrc[j + 1][i].b; mB[8] = pSrc[j + 1][i + 1].b;

			std::sort(mR, mR + 9); // �ּҸ� �Ű������� ����ϱ� ������ �迭�� �ּҸ� �Ѱ��ش�.
			std::sort(mG, mG + 9); // �ּҸ� �Ű������� ����ϱ� ������ �迭�� �ּҸ� �Ѱ��ش�.
			std::sort(mB, mB + 9); // �ּҸ� �Ű������� ����ϱ� ������ �迭�� �ּҸ� �Ѱ��ش�.

			pDst[j][i].r = mR[4];
			pDst[j][i].g = mG[4];
			pDst[j][i].b = mB[4];
		}
}

// �ι��� ���� ����
void IppEdgeRoberts(IppRgbImage& img, IppRgbImage& imgEdge)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	imgEdge.CreateImage(w, h);

	RGBBYTE** p1 = img.GetPixels2D();
	RGBBYTE** p2 = imgEdge.GetPixels2D();

	int i, j, Rh1, Rh2, Gh1, Gh2, Bh1, Bh2;
	double Rhval, Ghval, Bhval;
	for (j = 1; j < h; j++)
		for (i = 1; i < w - 1; i++)
		{
			Rh1 = p1[j][i].r - p1[j - 1][i - 1].r;
			Rh2 = p1[j][i].r - p1[j - 1][i + 1].r;

			Gh1 = p1[j][i].g - p1[j - 1][i - 1].g;
			Gh2 = p1[j][i].g - p1[j - 1][i + 1].g;

			Bh1 = p1[j][i].b - p1[j - 1][i - 1].b;
			Bh2 = p1[j][i].b - p1[j - 1][i + 1].b;

			Rhval = sqrt(static_cast<double>(Rh1 * Rh1 + Rh2 * Rh2));
			Ghval = sqrt(static_cast<double>(Gh1 * Gh1 + Gh2 * Gh2));
			Bhval = sqrt(static_cast<double>(Bh1 * Bh1 + Bh2 * Bh2));

			p2[j][i].r = static_cast<BYTE>(limit(Rhval + 0.5));
			p2[j][i].g = static_cast<BYTE>(limit(Ghval + 0.5));
			p2[j][i].b = static_cast<BYTE>(limit(Bhval + 0.5));
		}
}

// �Һ� ���� ����
void IppEdgeSobel(IppRgbImage& img, IppRgbImage& imgEdge)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	imgEdge.CreateImage(w, h);

	RGBBYTE** p1 = img.GetPixels2D();
	RGBBYTE** p2 = imgEdge.GetPixels2D();

	int i, j, Rh1, Rh2, Gh1, Gh2, Bh1, Bh2;
	double Rhval, Ghval, Bhval;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			Rh1 = -p1[j - 1][i - 1].r - 2 * p1[j - 1][i].r - p1[j - 1][i + 1].r
				+ p1[j + 1][i - 1].r + 2 * p1[j + 1][i].r + p1[j + 1][i + 1].r;
			Rh2 = -p1[j - 1][i - 1].r - 2 * p1[j][i - 1].r - p1[j + 1][i - 1].r
				+ p1[j - 1][i + 1].r + 2 * p1[j][i + 1].r + p1[j + 1][i + 1].r;

			Gh1 = -p1[j - 1][i - 1].g - 2 * p1[j - 1][i].g - p1[j - 1][i + 1].g
				+ p1[j + 1][i - 1].g + 2 * p1[j + 1][i].g + p1[j + 1][i + 1].g;
			Gh2 = -p1[j - 1][i - 1].g - 2 * p1[j][i - 1].g - p1[j + 1][i - 1].g
				+ p1[j - 1][i + 1].g + 2 * p1[j][i + 1].g + p1[j + 1][i + 1].g;

			Bh1 = -p1[j - 1][i - 1].b - 2 * p1[j - 1][i].b - p1[j - 1][i + 1].b
				+ p1[j + 1][i - 1].b + 2 * p1[j + 1][i].b + p1[j + 1][i + 1].b;
			Bh2 = -p1[j - 1][i - 1].b - 2 * p1[j][i - 1].b - p1[j + 1][i - 1].b
				+ p1[j - 1][i + 1].b + 2 * p1[j][i + 1].b + p1[j + 1][i + 1].b;

			Rhval = sqrt(static_cast<double>(Rh1 * Rh1 + Rh2 * Rh2));
			Ghval = sqrt(static_cast<double>(Gh1 * Gh1 + Gh2 * Gh2));
			Bhval = sqrt(static_cast<double>(Bh1 * Bh1 + Bh2 * Bh2));

			p2[j][i].r = static_cast<BYTE>(limit(Rhval + 0.5));
			p2[j][i].g = static_cast<BYTE>(limit(Ghval + 0.5));
			p2[j][i].b = static_cast<BYTE>(limit(Bhval + 0.5));

		}
}

void IppResizeNearest(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j, x, y;
	double rx, ry;
	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			rx = static_cast<double>(w - 1) * i / (nw - 1); // Ȯ�� ������ ��������
			ry = static_cast<double>(h - 1) * j / (nh - 1);
			x = static_cast<int>(rx + 0.5); // ���� �� ��ȯ (�ݿø� �Ͽ�), ������ ���� ���� ��ǥ 
			y = static_cast<int>(ry + 0.5);

			if (x >= w) x = w - 1;
			if (y >= h) y = h - 1;

			pDst[j][i].r = pSrc[y][x].r;
			pDst[j][i].g = pSrc[y][x].g;
			pDst[j][i].b = pSrc[y][x].b;
		}
}

void IppResizeBilinear(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j, x1, y1, x2, y2;
	double rx, ry, p, q, Rvalue, Gvalue, Bvalue;

	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			rx = static_cast<double>(w - 1) * i / (nw - 1); // Ȯ�� ������ ��������
			ry = static_cast<double>(h - 1) * j / (nh - 1);

			x1 = static_cast<int>(rx); // rx, ry ��ǥ��
			y1 = static_cast<int>(ry);

			x2 = x1 + 1; if (x2 == w) x2 = w - 1; // ���� ��쿡�� �� �����ڸ��� �ȼ� ���� �����ϵ��� �Ѵ�.
			y2 = y1 + 1; if (y2 == h) y2 = h - 1; // �ѷ��� 4���� �ȼ� ��ǥ�� ��Ÿ��

			p = rx - x1;
			q = ry - y1;

			Rvalue = (1. - p) * (1. - q) * pSrc[y1][x1].r + p * (1. - q) * pSrc[y1][x2].r
				+ (1. - p) * q * pSrc[y2][x1].r + p * q * pSrc[y2][x2].r; // �缱�� �������� �����Ͽ� �ȼ� ���� ����

			Gvalue = (1. - p) * (1. - q) * pSrc[y1][x1].g + p * (1. - q) * pSrc[y1][x2].g
				+ (1. - p) * q * pSrc[y2][x1].g + p * q * pSrc[y2][x2].g; // �缱�� �������� �����Ͽ� �ȼ� ���� ����

			Bvalue = (1. - p) * (1. - q) * pSrc[y1][x1].b + p * (1. - q) * pSrc[y1][x2].b
				+ (1. - p) * q * pSrc[y2][x1].b + p * q * pSrc[y2][x2].b; // �缱�� �������� �����Ͽ� �ȼ� ���� ����

			pDst[j][i].r = static_cast<BYTE>(limit(Rvalue + .5)); // �ݿø��Ͽ� �ȼ� ������ ����
			pDst[j][i].g = static_cast<BYTE>(limit(Gvalue + .5)); // �ݿø��Ͽ� �ȼ� ������ ����
			pDst[j][i].b = static_cast<BYTE>(limit(Bvalue + .5)); // �ݿø��Ͽ� �ȼ� ������ ����
		}
}

// �������� ����
void IppMorphologyColorErosion(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	int i, j, m, n, x, y, Rpmin, Gpmin, Bpmin;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	RGBBYTE** pDst = imgDst.GetPixels2D();
	RGBBYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			Rpmin = 255;
			Gpmin = 255;
			Bpmin = 255;

			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;

					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						if (pSrc[y][x].r < Rpmin)
							Rpmin = pSrc[y][x].r;

						if (pSrc[y][x].g < Gpmin)
							Gpmin = pSrc[y][x].g;

						if (pSrc[y][x].b < Bpmin)
							Bpmin = pSrc[y][x].b;
					}
				}

			pDst[j][i].r = Rpmin;
			pDst[j][i].g = Gpmin;
			pDst[j][i].b = Bpmin;
		}
}

// �������� ��â
void IppMorphologyColorDilation(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	int i, j, m, n, x, y, Rpmax, Gpmax, Bpmax;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	RGBBYTE** pDst = imgDst.GetPixels2D();
	RGBBYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			Rpmax = 0;
			Gpmax = 0;
			Bpmax = 0;

			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;

					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						if (pSrc[y][x].r > Rpmax)
							Rpmax = pSrc[y][x].r;

						if (pSrc[y][x].g > Gpmax)
							Gpmax = pSrc[y][x].g;

						if (pSrc[y][x].b > Bpmax)
							Bpmax = pSrc[y][x].b;
					}
				}

			pDst[j][i].r = Rpmax;
			pDst[j][i].g = Gpmax;
			pDst[j][i].b = Bpmax;
		}
}

// ������ ����
void IppMorphologyColorOpening(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	IppRgbImage imgTmp;
	IppMorphologyColorErosion(imgSrc, imgTmp);
	IppMorphologyColorDilation(imgTmp, imgDst);
}

// ������ �ݱ�
void IppMorphologyColorClosing(IppRgbImage& imgSrc, IppRgbImage& imgDst)
{
	IppRgbImage imgTmp;
	IppMorphologyColorDilation(imgSrc, imgTmp);
	IppMorphologyColorErosion(imgTmp, imgDst);
}

void IppResizeCubic(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j, x1, x2, x3, x4, y1, y2, y3, y4; // �� ���� 4���� �� �� 16���� ���� ��ǥ�� ������ x1 ~ y4
	double Rv1, Rv2, Rv3, Rv4, Rv;
	double Gv1, Gv2, Gv3, Gv4, Gv;
	double Bv1, Bv2, Bv3, Bv4, Bv;
	double rx, ry, p, q;

	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			rx = static_cast<double>(w - 1) * i / (nw - 1); // Ȯ�� ������ ��������
			ry = static_cast<double>(h - 1) * j / (nh - 1);

			x2 = static_cast<int>(rx);
			x1 = x2 - 1; if (x1 < 0) x1 = 0;
			x3 = x2 + 1; if (x3 >= w) x3 = w - 1;
			x4 = x2 + 2; if (x4 >= w) x4 = w - 1;
			p = rx - x2;

			y2 = static_cast<int>(ry);
			y1 = y2 - 1; if (y1 < 0) y1 = 0;
			y3 = y2 + 1; if (y3 >= h) y3 = h - 1;
			y4 = y2 + 2; if (y4 >= h) y4 = h - 1;
			q = ry - y2;

			// �� ���� ���� ��ǥ�� ����Ͽ� �� ���� �� v... �� ����
			Rv1 = cubic_interpolation(pSrc[y1][x1].r, pSrc[y1][x2].r, pSrc[y1][x3].r, pSrc[y1][x4].r, p);
			Rv2 = cubic_interpolation(pSrc[y2][x1].r, pSrc[y2][x2].r, pSrc[y2][x3].r, pSrc[y2][x4].r, p);
			Rv3 = cubic_interpolation(pSrc[y3][x1].r, pSrc[y3][x2].r, pSrc[y3][x3].r, pSrc[y3][x4].r, p);
			Rv4 = cubic_interpolation(pSrc[y4][x1].r, pSrc[y4][x2].r, pSrc[y4][x3].r, pSrc[y4][x4].r, p);

			Gv1 = cubic_interpolation(pSrc[y1][x1].g, pSrc[y1][x2].g, pSrc[y1][x3].g, pSrc[y1][x4].g, p);
			Gv2 = cubic_interpolation(pSrc[y2][x1].g, pSrc[y2][x2].g, pSrc[y2][x3].g, pSrc[y2][x4].g, p);
			Gv3 = cubic_interpolation(pSrc[y3][x1].g, pSrc[y3][x2].g, pSrc[y3][x3].g, pSrc[y3][x4].g, p);
			Gv4 = cubic_interpolation(pSrc[y4][x1].g, pSrc[y4][x2].g, pSrc[y4][x3].g, pSrc[y4][x4].g, p);

			Bv1 = cubic_interpolation(pSrc[y1][x1].b, pSrc[y1][x2].b, pSrc[y1][x3].b, pSrc[y1][x4].b, p);
			Bv2 = cubic_interpolation(pSrc[y2][x1].b, pSrc[y2][x2].b, pSrc[y2][x3].b, pSrc[y2][x4].b, p);
			Bv3 = cubic_interpolation(pSrc[y3][x1].b, pSrc[y3][x2].b, pSrc[y3][x3].b, pSrc[y3][x4].b, p);
			Bv4 = cubic_interpolation(pSrc[y4][x1].b, pSrc[y4][x2].b, pSrc[y4][x3].b, pSrc[y4][x4].b, p);

			Rv = cubic_interpolation(Rv1, Rv2, Rv3, Rv4, q); // �� ���� ������ ������ �ٽ� �����Ͽ� ���������� ������ ���� ���Ѵ�.
			Gv = cubic_interpolation(Gv1, Gv2, Gv3, Gv4, q); // �� ���� ������ ������ �ٽ� �����Ͽ� ���������� ������ ���� ���Ѵ�.
			Bv = cubic_interpolation(Bv1, Bv2, Bv3, Bv4, q); // �� ���� ������ ������ �ٽ� �����Ͽ� ���������� ������ ���� ���Ѵ�.

			pDst[j][i].r = static_cast<BYTE>(limit(Rv + 0.5)); // �ݿø��Ͽ� �������� ��ȯ�Ͽ� �ȼ������� ����
			pDst[j][i].g = static_cast<BYTE>(limit(Gv + 0.5)); // �ݿø��Ͽ� �������� ��ȯ�Ͽ� �ȼ������� ����
			pDst[j][i].b = static_cast<BYTE>(limit(Bv + 0.5)); // �ݿø��Ͽ� �������� ��ȯ�Ͽ� �ȼ������� ����
		}
}

//-------------------------------------------------------------------------
// R, G, B, H, S, I �� ������ [0, 1]
//-------------------------------------------------------------------------
void RGB_TO_HSI(double R, double G, double B, double& H, double& S, double& I)
{
	I = (R + G + B) / 3;

	if ((R == G) && (G == B)) // �׷��̽������� ���
	{
		S = 0;
		H = 0;
	}
	else
	{
		double min_rgb;
		double temp;

		min_rgb = min(min(R, G), B);
		S = 1 - (min_rgb / I);
		temp = ((R - G) + (R - B)) / (2 * sqrt((R - G)*(R - G) + (R - B) * (G - B)));

		H = acos(temp) * 180 / PI;

		if (B > G)
			H = 360 - H;

		H /= 360;
	}
}

//-------------------------------------------------------------------------
// R, G, B, H, S, I �� ������ [0, 1]
//-------------------------------------------------------------------------
void HSI_TO_RGB(double H, double S, double I, double& R, double& G, double& B)
{
	if (I == 0.0) // ������
	{
		R = 0.0;
		G = 0.0;
		B = 0.0;
		return;
	}

	if (S == 0.0) // �׷��̽�����
	{
		R = I;
		G = I;
		B = I;
		return;
	}

	H *= 360; // [0, 1] ������ [0, 360] ���� ������ ����

	if (H <= 120)
	{
		B = I * (1 - S);
		R = I * (1 + S * cos(H * PI / 180) / cos((60 - H) * PI / 180));
		R = limit(R, 0., 1.);
		G = 3 * I - (R + B);
	}
	else if (H <= 240)
	{
		H -= 120;

		R = I * (1 - S);
		G = I * (1 + S * cos(H * PI / 180) / cos((60 - H) * PI / 180));
		G = limit(G, 0., 1.);
		B = 3 * I - (R + G);
	}
	else
	{
		H -= 240;

		G = I * (1 - S);
		B = I * (1 + S * cos(H * PI / 180) / cos((60 - H) * PI / 180));
		B = limit(B, 0., 1.);
		R = 3 * I - (G + B);
	}


}

//-------------------------------------------------------------------------
// R, G, B, Y, U, V �� ������ [0, 255]
//-------------------------------------------------------------------------
void RGB_TO_YUV(BYTE R, BYTE G, BYTE B, BYTE& Y, BYTE& U, BYTE& V)
{
	Y = static_cast<BYTE>(limit(0.299*R + 0.587*G + 0.114*B + 0.5));
	U = static_cast<BYTE>(limit(-0.169*R - 0.331*G + 0.500*B + 128 + 0.5));
	V = static_cast<BYTE>(limit(0.500*R - 0.419*G - 0.081*B + 128 + 0.5));
}

//-------------------------------------------------------------------------
// R, G, B, Y, U, V �� ������ [0, 255]
//-------------------------------------------------------------------------
void YUV_TO_RGB(BYTE Y, BYTE U, BYTE V, BYTE& R, BYTE& G, BYTE& B)
{
	R = static_cast<BYTE>(limit(Y + 1.4075*(V - 128) + 0.5));
	G = static_cast<BYTE>(limit(Y - 0.3455*(U - 128) - 0.7169*(V - 128) + 0.5));
	B = static_cast<BYTE>(limit(Y + 1.7790*(U - 128) + 0.5));
}

// RGB ���� ��� ������
void IppColorSplitRGB(IppRgbImage& imgColor, IppByteImage& imgR, IppByteImage& imgG, IppByteImage& imgB)
{
	int w = imgColor.GetWidth();
	int h = imgColor.GetHeight();
	int size = imgColor.GetSize();

	imgR.CreateImage(w, h);
	imgG.CreateImage(w, h);
	imgB.CreateImage(w, h);

	RGBBYTE* pColor = imgColor.GetPixels();
	BYTE* pR = imgR.GetPixels();
	BYTE* pG = imgG.GetPixels();
	BYTE* pB = imgB.GetPixels();

	for (int i = 0; i < size; i++)
	{
		pR[i] = pColor[i].r;
		pG[i] = pColor[i].g;
		pB[i] = pColor[i].b;
	}
}

// HSI ���� ��� ������
void IppColorSplitHSI(IppRgbImage& imgColor, IppByteImage& imgH, IppByteImage& imgS, IppByteImage& imgI)
{
	int w = imgColor.GetWidth();
	int h = imgColor.GetHeight();
	int size = imgColor.GetSize();

	imgH.CreateImage(w, h);
	imgS.CreateImage(w, h);
	imgI.CreateImage(w, h);

	RGBBYTE* pColor = imgColor.GetPixels();
	BYTE* pH = imgH.GetPixels();
	BYTE* pS = imgS.GetPixels();
	BYTE* pI = imgI.GetPixels();

	double r, g, b, hh, ss, ii;
	for (int i = 0; i < size; i++)
	{
		// HSI ������ ���� ���� 0, 1 �����Ǿ� �ֱ� ������ 255 �������ش�.
		r = pColor[i].r / 255.;
		g = pColor[i].g / 255.;
		b = pColor[i].b / 255.;

		RGB_TO_HSI(r, g, b, hh, ss, ii);

		pH[i] = static_cast<BYTE>(limit(hh * 255 + 0.5));
		pS[i] = static_cast<BYTE>(limit(ss * 255 + 0.5));
		pI[i] = static_cast<BYTE>(limit(ii * 255 + 0.5));
	}
}

// YUV ���� ��� ������
void IppColorSplitYUV(IppRgbImage& imgColor, IppByteImage& imgY, IppByteImage& imgU, IppByteImage& imgV)
{
	int w = imgColor.GetWidth();
	int h = imgColor.GetHeight();
	int size = imgColor.GetSize();

	imgY.CreateImage(w, h);
	imgU.CreateImage(w, h);
	imgV.CreateImage(w, h);

	RGBBYTE* pColor = imgColor.GetPixels();
	BYTE* pY = imgY.GetPixels();
	BYTE* pU = imgU.GetPixels();
	BYTE* pV = imgV.GetPixels();

	for (int i = 0; i < size; i++)
	{
		RGB_TO_YUV(pColor[i].r, pColor[i].g, pColor[i].b, pY[i], pU[i], pV[i]);
	}
} 

// RGB ���� ��� ��ġ��
bool IppColorCombineRGB(IppByteImage& imgR, IppByteImage& imgG, IppByteImage& imgB, IppRgbImage& imgColor)
{
	int w = imgR.GetWidth();
	int h = imgR.GetHeight();
	int size = imgR.GetSize();

	// ���� �׸��� �ƴҰ�� FALSE�� ��ȯ
	if (imgG.GetWidth() != w || imgG.GetHeight() != h ||
		imgB.GetWidth() != w || imgB.GetHeight() != h)
		return FALSE;

	imgColor.CreateImage(w, h);

	BYTE* pR = imgR.GetPixels();
	BYTE* pG = imgG.GetPixels();
	BYTE* pB = imgB.GetPixels();
	RGBBYTE* pColor = imgColor.GetPixels();

	for (int i = 0; i < size; i++)
	{
		pColor[i].r = pR[i];
		pColor[i].g = pG[i];
		pColor[i].b = pB[i];
	}

	return true;
}

// HSI ���� ��� ��ġ��
bool IppColorCombineHSI(IppByteImage& imgH, IppByteImage& imgS, IppByteImage& imgI, IppRgbImage& imgColor)
{
	int w = imgH.GetWidth();
	int h = imgH.GetHeight();
	int size = imgH.GetSize();

	if (imgS.GetWidth() != w || imgS.GetHeight() != h ||
		imgI.GetWidth() != w || imgI.GetHeight() != h)
		return false;

	imgColor.CreateImage(w, h);

	BYTE* pH = imgH.GetPixels();
	BYTE* pS = imgS.GetPixels();
	BYTE* pI = imgI.GetPixels();
	RGBBYTE* pColor = imgColor.GetPixels();

	double r, g, b, hh, ss, ii;
	for (int i = 0; i < size; i++)
	{
		hh = pH[i] / 255.;
		ss = pS[i] / 255.;
		ii = pI[i] / 255.;

		HSI_TO_RGB(hh, ss, ii, r, g, b); // Ʈ�� �÷� �������� ����ؾ� �ϱ� ������ ��ȯ���ش�.

		pColor[i].r = static_cast<BYTE>(limit(r * 255 + 0.5)); 
		pColor[i].g = static_cast<BYTE>(limit(g * 255 + 0.5));
		pColor[i].b = static_cast<BYTE>(limit(b * 255 + 0.5));
	}

	return true;
}

// YUV ���� ��� ��ġ��
bool IppColorCombineYUV(IppByteImage& imgY, IppByteImage& imgU, IppByteImage& imgV, IppRgbImage& imgColor)
{
	int w = imgY.GetWidth();
	int h = imgY.GetHeight();
	int size = imgY.GetSize();

	if (imgU.GetWidth() != w || imgU.GetHeight() != h ||
		imgV.GetWidth() != w || imgV.GetHeight() != h)
		return false;

	imgColor.CreateImage(w, h);

	BYTE* pY = imgY.GetPixels();
	BYTE* pU = imgU.GetPixels();
	BYTE* pV = imgV.GetPixels();
	RGBBYTE* pColor = imgColor.GetPixels();

	for (int i = 0; i < size; i++)
	{
		YUV_TO_RGB(pY[i], pU[i], pV[i], pColor[i].r, pColor[i].g, pColor[i].b);
	}

	return true;
}

void IppColorEdge(IppRgbImage& imgSrc, IppByteImage& imgEdge)
{
	IppByteImage imgY, imgU, imgV;
	IppColorSplitYUV(imgSrc, imgY, imgU, imgV);

	IppByteImage edgeY, edgeU, edgeV;
	// ������ ���� ����
	IppEdgePrewitt(imgY, edgeY);
	IppEdgePrewitt(imgU, edgeU);
	IppEdgePrewitt(imgV, edgeV);

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();
	int size = imgSrc.GetSize();

	imgEdge.CreateImage(w, h);
	BYTE* pEdge = imgEdge.GetPixels();

	BYTE* pY = edgeY.GetPixels();
	BYTE* pU = edgeU.GetPixels();
	BYTE* pV = edgeV.GetPixels();

	// ��Ŭ���� �Ÿ� ���ϱ�, 0.5�� ����ġ�� �ο�
	double dist;
	for (int i = 0; i < size; i++)
	{
		dist = (pY[i] * pY[i]) +
			(0.5 * pU[i]) * (0.5 * pU[i]) +
			(0.5 * pV[i]) * (0.5 * pV[i]);
		pEdge[i] = static_cast<BYTE>(limit(sqrt(dist)));
	}
	
}

