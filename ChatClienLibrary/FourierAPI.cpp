#include "pch.h"
#include <math.h>
#include <algorithm>

#ifndef _DLL_FOURIER_
#define _DLL_FOURIER_
#endif // !_DLL_FOURIER_

#include "FourierAPI.h"

const double PI = 3.14159265358979323846;
FourierAPI api;

APIFourier::APIFourier()
	: width(0), height(0)
{
}

// width, height ��� �������� �����ϰ�, �Է� ������ real ���� �����Ѵ�. image ������ 0���� �ʱ�ȭ
void APIFourier::APISetImage(IppByteImage& img)
{
	width = img.GetWidth();
	height = img.GetHeight();

	real.Convert(img);               // �Ǽ��ο� ������ �׷��̽����� �� ����
	imag.CreateImage(width, height); // ����δ� 0���� �ʱ�ȭ
}

// real ������ IppByteimage Ÿ���� ���� img�� ����
void APIFourier::APIGetImage(IppByteImage& img)
{
	// �Է� ������ �����Ǿ� �ִ��� �˻�
	if (!real.IsValid())
		return;

	// �Ǽ��θ� �̿��Ͽ� ��� ������ ����
	img.CreateImage(width, height);

	double* pRe = real.GetPixels();
	BYTE* ptr = img.GetPixels();

	int size = real.GetSize();
	for (int i = 0; i < size; i++)
		ptr[i] = static_cast<BYTE>(limit(pRe[i] + 0.5));
}

// Ǫ���� ��ȯ �� ȣ��Ǿ�, Ǫ���� ����Ʈ�� ������ ����
void APIFourier::APIGetSpectrumImage(IppByteImage& img)
{
	register int i, j;

	img.CreateImage(width, height);
	BYTE** ptr = img.GetPixels2D();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	// ����Ʈ�� ���� ������ �ӽ� ����
	IppDoubleImage spectrum(width, height);
	double** pSpec = spectrum.GetPixels2D();

	//-------------------------------------------------------------------------
	// ���Ҽ� ���� ���밪�� �α� ��ȯ�Ͽ� ����. 
	// ����ȭ�� ��� �̹��� ������ ���Ͽ� ����Ʈ���� �ִ밪 ���.
	//-------------------------------------------------------------------------

	double mag, max_value = 0;
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			mag = sqrt(pRe[j][i] * pRe[j][i] + pIm[j][i] * pIm[j][i]);
			pSpec[j][i] = log(mag + 1);

			if (pSpec[j][i] > max_value)
				max_value = pSpec[j][i];
		}

	//-------------------------------------------------------------------------
	// ��� ���� ����. Ǫ���� ��ȯ ����� SHIFT �ϰ�, 
	// ��� ������ �ִ밪�� 255�� �ǵ��� �׷��̽����� ���� ����ȭ.
	//-------------------------------------------------------------------------

	int x, y;
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			x = i + width / 2;
			y = j + height / 2;

			if (x >= width) x -= width;
			if (y >= height) y -= height;

			ptr[j][i] = static_cast<BYTE>(limit(pSpec[y][x] * 255 / max_value));
		}
}

// Ǫ���� ��ȯ �� ȣ��Ǿ�, ���� ������ ����
void APIFourier::APIGetPhaseImage(IppByteImage& img)
{
	register int i, j;

	img.CreateImage(width, height);
	BYTE** ptr = img.GetPixels2D();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	// ������ ������ �ӽ� ����
	IppDoubleImage phase(width, height);
	double** pPhase = phase.GetPixels2D();

	//-------------------------------------------------------------------------
	// ���Ҽ� ���� ������ ����. atan2 �Լ��� ��ȯ ���� -PI ~ PI �̴�.
	//-------------------------------------------------------------------------

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			pPhase[j][i] = atan2(pIm[j][i], pRe[j][i]); // ����� ����
		}

	//-------------------------------------------------------------------------
	// ��� ���� ����. Ǫ���� ��ȯ ����� SHIFT �ϰ�, 
	// ��� ������ �ִ밪�� 255�� �ǵ��� �׷��̽����� ���� ����ȭ.
	//-------------------------------------------------------------------------

	int x, y;
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			x = i + width / 2;
			y = j + height / 2;

			if (x >= width) x -= width;
			if (y >= height) y -= height;

			ptr[j][i] = static_cast<BYTE>(limit(pPhase[y][x] * 128 / PI + 128));
		}
}

// ������ �̻� Ǫ���� ��ȯ �Ǵ� ����ȯ�� ����. dir ���� 1�̸� ������, -1�̸� ������ ��ȯ ����
void APIFourier::APIDFT(int dir)
{
	if (!real.IsValid())
		return;

	//-------------------------------------------------------------------------
	// real, imag ���纻 ����
	//-------------------------------------------------------------------------

	IppDoubleImage real_cpy = real;
	IppDoubleImage imag_cpy = imag;

	// 2���� �迭 ����
	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	double** pReCpy = real_cpy.GetPixels2D();
	double** pImCpy = imag_cpy.GetPixels2D();

	//-------------------------------------------------------------------------
	// �̻� Ǫ���� ��ȯ (�Ǵ� ����ȯ)
	//-------------------------------------------------------------------------

	register int i, j, x, y;
	double sum_re, sum_im, temp;

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			sum_re = sum_im = 0;

			for (y = 0; y < height; y++)
				for (x = 0; x < width; x++)
				{
					temp = 2 * dir * PI * (static_cast<double>(i) * x / width + static_cast<double>(j) * y / height);
					sum_re += (pReCpy[y][x] * cos(temp) - pImCpy[y][x] * sin(temp));
					sum_im += (pReCpy[y][x] * sin(temp) + pImCpy[y][x] * sin(temp));
				}

			pRe[j][i] = sum_re;
			pIm[j][i] = sum_im;

			if (dir == -1) // ����ȯ�� ���
			{
				pRe[j][i] /= (width * height);
				pIm[j][i] /= (width * height);
			}
		}
}

// ������ ��� ���� �и��Ͽ� ������ �̻� Ǫ���� ��ȯ �Ǵ� ����ȯ�� ���� (���� ���� �и��Ͽ� ������ ����� �� ���� ��µȴ�.)
void APIFourier::APIDFTRC(int dir)
{
	if (!real.IsValid())
		return;

	//-------------------------------------------------------------------------
	// ��(Row) ���� �̻� Ǫ���� ��ȯ (�Ǵ� ����ȯ)
	//-------------------------------------------------------------------------

	IppDoubleImage real_tmp, imag_tmp;

	real_tmp.CreateImage(width, 1);
	imag_tmp.CreateImage(width, 1);

	double* re = real_tmp.GetPixels();
	double* im = imag_tmp.GetPixels();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	register int i, j;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			re[i] = pRe[j][i];
			im[i] = pIm[j][i];
		}

		api.APIDFT1d(re, im, width, dir);

		for (i = 0; i < width; i++)
		{
			pRe[j][i] = re[i];
			pIm[j][i] = im[i];
		}
	}

	//-------------------------------------------------------------------------
	// ��(Column) ���� �̻� Ǫ���� ��ȯ (�Ǵ� ����ȯ)
	//-------------------------------------------------------------------------

	real_tmp.CreateImage(height, 1);
	imag_tmp.CreateImage(height, 1);

	re = real_tmp.GetPixels();
	im = imag_tmp.GetPixels();

	memset(re, 0, sizeof(double) * height);
	memset(im, 0, sizeof(double) * height);

	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			re[j] = pRe[j][i];
			im[j] = pIm[j][i];
		}

		api.APIDFT1d(re, im, height, dir);

		for (j = 0; j < height; j++)
		{
			pRe[j][i] = re[j];
			pIm[j][i] = im[j];
		}
	}
}

// ������ ��� �̻� Ǫ���� ��ȯ �Ǵ� ����ȯ�� ����
void APIFourier::APIFFT(int dir)
{
	if (!real.IsValid())
		return;

	// �Է� �������� ����, ���� ũ�Ⱑ 2�� �¼������� Ȯ�� (��� �̻� Ǫ���� ��ȯ�� �Է� ������ ����, ���� ũ�Ⱑ 2�� �¼����� �����ϱ� �����̴�.
	if (!api.APIIsPowerOf2(width) || !api.APIIsPowerOf2(height))
		return;

	//-------------------------------------------------------------------------
	// ��(Row) ���� �̻� Ǫ���� ��ȯ (�Ǵ� ����ȯ)
	//-------------------------------------------------------------------------

	IppDoubleImage real_tmp, imag_tmp;

	real_tmp.CreateImage(width, 1);
	imag_tmp.CreateImage(width, 1);

	double* re = real_tmp.GetPixels();
	double* im = imag_tmp.GetPixels();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	register int i, j;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			re[i] = pRe[j][i];
			im[i] = pIm[j][i];
		}

		api.APIFFT1d(re, im, width, dir);

		for (i = 0; i < width; i++)
		{
			pRe[j][i] = re[i];
			pIm[j][i] = im[i];
		}
	}

	//-------------------------------------------------------------------------
	// ��(Column) ���� �̻� Ǫ���� ��ȯ (�Ǵ� ����ȯ)
	//-------------------------------------------------------------------------

	real_tmp.CreateImage(height, 1);
	imag_tmp.CreateImage(height, 1);

	re = real_tmp.GetPixels();
	im = imag_tmp.GetPixels();

	memset(re, 0, sizeof(double) * height);
	memset(im, 0, sizeof(double) * height);

	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			re[j] = pRe[j][i];
			im[j] = pIm[j][i];
		}

		api.APIFFT1d(re, im, height, dir);

		for (j = 0; j < height; j++)
		{
			pRe[j][i] = re[j];
			pIm[j][i] = im[j];
		}
	}
}

// ���ļ� ���������� �̻��� ���� ��� ���͸� ���� (1 ���� 0���� ����)
void APIFourier::APILowPassIdeal(int cutoff) // cutoff�� ���� ���ļ��� ũ��
{
	register int i, j, x, y;

	int cx = width / 2; // �Ǽ��θ� �̷���� �Լ��� Ǫ���� ��ȯ�ϸ� �Է� ������ ũ���� ���ݿ� �ش��ϴ� ��ȣ�� ��Ī������ ���� ����
	int cy = height / 2;

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			x = i + cx;
			y = j + cy;

			if (x >= width)  x -= width;
			if (y >= height) y -= height;

			// ���͸��� ���� (��Ŭ���� �Ÿ��� ������ �������ļ��� �������� ��)
			if ((x - cx)*(x - cx) + (y - cy)*(y - cy) > (cutoff * cutoff))
				pRe[j][i] = pIm[j][i] = 0.;
		}
}

// ���ļ� �������� �̻��� �� ��� ���͸� ���� 
void APIFourier::APIHighPassIdeal(int cutoff)
{
	register int i, j, x, y;

	int cx = width / 2;
	int cy = height / 2;

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			x = i + cx;
			y = j + cy;

			if (x >= width) x -= width;
			if (y >= height) y -= height;

			if ((x - cx)*(x - cx) + (y - cy)*(y - cy) < (cutoff * cutoff))
				pRe[j][i] = pIm[j][i] = 0;
		}
}

// ���ļ� �������� ����þ� ���� ��� ���͸� ���� ( ���� �߾ӿ��� 1�� ���� ������ �ֺ����� ������ ������ ���� �۾���)
void APIFourier::APILowPassGaussian(int cutoff)
{
	register int i, j, x, y;
	double dist2, hval;

	int cx = width / 2;
	int cy = height / 2;

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			x = i + cx;
			y = j + cy;

			if (x >= width) x -= width;
			if (y >= height) y -= height;

			dist2 = static_cast<double>((x - cx)*(x - cx) + (y - cy)*(y - cy));

			hval = exp(-dist2 / (2 * cutoff * cutoff));

			pRe[j][i] *= hval;
			pIm[j][i] *= hval;
		}
}

// ���ļ� �������� ����þ� �� ��� ���� ����
void APIFourier::APIHighPassGaussian(int cutoff)
{
	register int i, j, x, y;
	double dist2, hval;

	int cx = width / 2;
	int cy = height / 2;

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			x = i + cx;
			y = j + cy;

			if (x >= width) x -= width;
			if (y >= height) y -= height;

			dist2 = static_cast<double>((x - cx)*(x - cx) + (y - cy)*(y - cy));

			hval = 1.0 - exp(-dist2 / (2 * cutoff * cutoff));

			pRe[j][i] *= hval;
			pIm[j][i] *= hval;
		}
}

//-------------------------------------------------------------------------
// ���� �Լ� ����
//-------------------------------------------------------------------------

// re�� im �迭�� ����� ���� �̿��Ͽ� �̻� Ǫ���� ��ȯ �Ǵ� ����ȯ�� �����Ѵ�. 
// N�� �迭�� ũ�⸦ ��Ÿ����. dir ���� 1�̸� ������ ��ȯ, -1�̸� ������ ��ȯ�� �����Ѵ�. Ǫ���� ��ȯ ����� �ٽ� re�� im �迭�� ����ȴ�.
void FourierAPI::APIDFT1d(double* re, double* im, int N, int dir)
{
	double* tr = new double[N];
	double* ti = new double[N];

	memcpy(tr, re, sizeof(double) * N);
	memcpy(ti, im, sizeof(double) * N);

	register int i, x;
	double sum_re, sum_im, temp;
	for (i = 0; i < N; i++)
	{
		sum_re = sum_im = 0;

		// Ǫ���� ��ȯ ����
		for (x = 0; x < N; x++)
		{
			temp = 2 * dir * PI * i * x / N;

			sum_re += (tr[x] * cos(temp) + ti[x] * sin(temp));
			sum_im += (ti[x] * cos(temp) - tr[x] * sin(temp));
		}

		re[i] = sum_re;
		im[i] = sum_im;
	}

	if (dir == -1) // IDFT
	{
		for (i = 0; i < N; i++)
		{
			re[i] /= static_cast<double>(N);
			im[i] /= static_cast<double>(N);
		}
	}

	delete[] tr;
	delete[] ti;
}

// ��� �̻� Ǫ���� ��ȯ �Ǵ� ����ȯ�� ����. 
void FourierAPI::APIFFT1d(double* re, double* im, int N, int dir)
{
	register int i, j, k;

	//-------------------------------------------------------------------------
	// �Է� ������ ���� �ٲٱ�
	//-------------------------------------------------------------------------

	int n2 = N >> 1;
	int nb = 0;

	while (N != (1 << nb))
		nb++;

	for (i = 0, j = 0; i < N - 1; i++)
	{
		if (i < j)
		{
			std::swap(re[i], re[j]);
			std::swap(im[i], im[j]);
		}

		k = n2;

		while (k <= j)
		{
			j -= k;
			k >>= 1;
		}

		j += k;
	}

	//-------------------------------------------------------------------------
	// �����ö���(Butterfly) �˰���
	//-------------------------------------------------------------------------

	int i1, l, l1, l2;
	double c1, c2, t1, t2, u1, u2, z;

	c1 = -1.0;
	c2 = 0.0;
	l2 = 1;

	for (l = 0; l < nb; l++)
	{
		l1 = l2;
		l2 <<= 1;
		u1 = 1.0;
		u2 = 0.0;

		for (j = 0; j < l1; j++)
		{
			for (i = j; i < N; i += l2)
			{
				i1 = i + l1;
				t1 = u1 * re[i1] - u2 * im[i1];
				t2 = u1 * im[i1] + u2 * re[i1];
				re[i1] = re[i] - t1;
				im[i1] = im[i] - t2;
				re[i] += t1;
				im[i] += t2;
			}

			z = u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		}

		c2 = sqrt((1.0 - c1) / 2.0);

		if (dir == 1) // Forward
			c2 = -c2;

		c1 = sqrt((1.0 + c1) / 2.0);
	}

	if (dir == -1) // IDFT
	{
		for (i = 0; i < N; i++)
		{
			re[i] /= static_cast<double>(N);
			im[i] /= static_cast<double>(N);
		}
	}
}

// n�� 2�� �¼��� ǥ���Ǵ� ���̸� true�� ��ȯ�ϰ�, �ƴϸ� false �� ��ȯ.
bool FourierAPI::APIIsPowerOf2(int n)
{
	int ref = 1;

	while (ref < n)
		ref <<= 1;

	if (ref == n)
		return true;
	else
		return false;
}