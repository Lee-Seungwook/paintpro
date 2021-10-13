#include "pch.h"
#include "..\ImageTool\stdafx.h"
#include "math.h"

#ifndef _DLL_ENHANCE_
#define _DLL_ENHANCE_
#endif // !_DLL_ENHANCE_

#include "EnhanceAPI.h"

void EnhanceAPI::APIINVERSE(IppByteImage& img)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels(); // ������ �ȼ��� ������ 1���� �迭

	for (int i = 0; i < size; i++) // ���� ������ ��ŭ �ݺ�
	{
		p[i] = 255 - p[i]; // ���� ���� 
	}
}

void EnhanceAPI::APIBrightness(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = limit(p[i] + n); // 0 �Ǵ� 256���� Ŀ���°��� �����Ѵ�.
	}
}

void EnhanceAPI::APICBrightness(IppRgbImage& img, int n)
{
	int size = img.GetSize() * 3; // Ʈ�� �÷� ������ ��Ʈ���� 3�� ���Ƽ� �����־���.
	RGBBYTE *p = img.GetPixels(); // �̹����� 1�������� �����Ѵ�. (Ʈ�� �÷� �����̱� �����̴�.)
	BYTE *b = &p->b; // ������ �ȼ� ���� �´� 1���� �迭 ����
	BYTE *g = &p->g;
	BYTE *r = &p->r;

	for (int i = 0; i < size; i++)
	{
		b[i] = limit(b[i] + n);
		g[i] = limit(g[i] + n);
		r[i] = limit(r[i] + n);
	}
}

void EnhanceAPI::APIContrast(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit(p[i] + (p[i] - 128) * n / 100));
	}
}

void EnhanceAPI::APICContrast(IppRgbImage& img, int n)
{
	int size = img.GetSize() * 3; // Ʈ�� �÷� ������ ��Ʈ���� 3�� ���Ƽ� �����־���.
	RGBBYTE *p = img.GetPixels(); // �̹����� 1�������� �����Ѵ�. (Ʈ�� �÷� �����̱� �����̴�.)
	BYTE *b = &p->b; // ������ �ȼ� ���� �´� 1���� �迭 ����
	BYTE *g = &p->g;
	BYTE *r = &p->r;

	for (int i = 0; i < size; i++)
	{
		b[i] = static_cast<BYTE>(limit(b[i] + (b[i] - 128) * n / 100));
		g[i] = static_cast<BYTE>(limit(g[i] + (g[i] - 128) * n / 100));
		r[i] = static_cast<BYTE>(limit(r[i] + (r[i] - 128) * n / 100));
	}
}

void EnhanceAPI::APIGammaCorrection(IppByteImage& img, float gamma)
{
	float inv_gamma = 1.f / gamma; // ����� �Ǽ��� ���ü� �ֱ� ������ �Ǽ��� ���ڸ� ���, ��ũ�ѹ� ���������� ������.

	float gamma_table[256]; // ��� ���̺� ����
	for (int i = 0; i < 256; i++)
		gamma_table[i] = pow((i / 255.f), inv_gamma); // ����, pow������ �ð� �� ������ �Ҹ� ũ�ٰ� �Ѵ�.

	int size = img.GetSize();
	BYTE*p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit(gamma_table[p[i]] * 255 + 0.5f)); // ���� ����, ������ �Ǽ��� ���ϴ� ���� �ݿø� �ϱ� ���ؼ� �̴�.
	}
}

void EnhanceAPI::APICGammaCorrection(IppRgbImage& img, float gamma)
{
	float inv_gamma = 1.f / gamma; // ����� �Ǽ��� ���ü� �ֱ� ������ �Ǽ��� ���ڸ� ���, ��ũ�ѹ� ���������� ������.

	float gamma_table[256]; // ��� ���̺� ����
	for (int i = 0; i < 256; i++)
		gamma_table[i] = pow((i / 255.f), inv_gamma); // ����, pow������ �ð� �� ������ �Ҹ� ũ�ٰ� �Ѵ�.

	int size = img.GetSize() * 3;

	RGBBYTE*p = img.GetPixels();
	BYTE *b = &p->b; // ������ �ȼ� ���� �´� 1���� �迭 ����
	BYTE *g = &p->g;
	BYTE *r = &p->r;

	for (int i = 0; i < size; i++)
	{
		b[i] = static_cast<BYTE>(limit(gamma_table[b[i]] * 255 + 0.5f)); // ���� ����, ������ �Ǽ��� ���ϴ� ���� �ݿ�fla �ϱ� ���ؼ� �̴�.
		g[i] = static_cast<BYTE>(limit(gamma_table[g[i]] * 255 + 0.5f));
		r[i] = static_cast<BYTE>(limit(gamma_table[r[i]] * 255 + 0.5f));
	}
}

void EnhanceAPI::APIHistogram(IppByteImage& img, float histo[256])
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	// ������׷� ���
	int cnt[256];
	memset(cnt, 0, sizeof(int) * 256);
	for (int i = 0; i < size; i++) // �ȼ��� ������ ���
		cnt[p[i]]++;

	// ������׷� ����ȭ(histogram normalization)
	for (int i = 0; i < 256; i++)
	{
		histo[i] = static_cast<float>(cnt[i]) / size; // cnt �迭�� ����� ���� ��ü �ȼ��� ������ ������ ����ȭ�� ������׷� ���� histo �迭�� ����
	}
}

void EnhanceAPI::APIHistogramStrectching(IppByteImage& img)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	// �ִ�, �ּ� �׷��̽����� �� ���
	BYTE gray_max, gray_min;
	gray_max = gray_min = p[0]; // �ʱ�ȭ
	for (int i = 1; i < size; i++)
	{
		if (gray_max < p[i]) gray_max = p[i];
		if (gray_min > p[i]) gray_min = p[i];
	}

	if (gray_max == gray_min)
		return;

	// ������׷� ��Ʈ��Ī
	for (int i = 0; i < size; i++)
	{
		p[i] = (p[i] - gray_min) * 255 / (gray_max - gray_min); // ���� ����
	}
}

void EnhanceAPI::APIHistogramEqualization(IppByteImage& img)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	// ������׷� ���
	float hist[256];
	APIHistogram(img, hist);

	// ������׷� ���� �Լ� ���
	float cdf[256] = { 0, 0, };
	cdf[0] = hist[0];
	for (int i = 1; i < 256; i++)
		cdf[i] = cdf[i - 1] + hist[i];

	// ������׷� �յ�ȭ
	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit(cdf[p[i]] * 255));
	}
}

bool EnhanceAPI::APIAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE *p1 = img1.GetPixels();
	BYTE *p2 = img2.GetPixels();
	BYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i] = limit(p1[i] + p2[i]); // ���� ���� ����
	}
}

bool EnhanceAPI::APISub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE *p1 = img1.GetPixels();
	BYTE *p2 = img2.GetPixels();
	BYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i] = limit(p1[i] - p2[i]); // ���� ���� ����
	}
}

bool EnhanceAPI::APIAve(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE *p1 = img1.GetPixels();
	BYTE *p2 = img2.GetPixels();
	BYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i] = (p1[i] + p2[i]) / 2; // ��� ���� ���� ( ��� ������ 0 ~ 255 ������ ����� ��µǱ⿡ ���� ������ ���� limit�Լ��� ����)
	}
}

bool EnhanceAPI::APIDiff(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE *p1 = img1.GetPixels();
	BYTE *p2 = img2.GetPixels();
	BYTE *p3 = img3.GetPixels();

	int diff;
	for (int i = 0; i < size; i++)
	{
		diff = p1[i] - p2[i]; // ������ ���� ���� ����
		p3[i] = static_cast<BYTE>((diff >= 0) ? diff : -diff); // ���밪 ��ȯ
	}
}

bool EnhanceAPI::APIAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE *p1 = img1.GetPixels();
	BYTE *p2 = img2.GetPixels();
	BYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i] = static_cast<BYTE>(p1[i] & p2[i]); // AND ���� ����
	}
}

bool EnhanceAPI::APIOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3)
{
	int w = img1.GetWidth();
	int h = img1.GetHeight();

	if (w != img2.GetWidth() || h != img2.GetHeight()) // �Է¹��� ������ ���� ���� ũ�Ⱑ �����ؾ� ������ ����
		return false;

	img3.CreateImage(w, h);

	int size = img3.GetSize();
	BYTE *p1 = img1.GetPixels();
	BYTE *p2 = img2.GetPixels();
	BYTE *p3 = img3.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p3[i] = static_cast<BYTE>(p1[i] | p2[i]); // OR ���� ����
	}
}

void EnhanceAPI::APIBitPlane(IppByteImage& img1, IppByteImage& img2, int bit)
{
	img2.CreateImage(img1.GetWidth(), img1.GetHeight());

	int size = img1.GetSize();
	BYTE* p1 = img1.GetPixels();
	BYTE* p2 = img2.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p2[i] = (p1[i] & (1 << bit)) ? 255 : 0; // ����Ʈ ���� �����Ͽ� �� ��ġ�� ��Ʈ���� ��
	}
}


