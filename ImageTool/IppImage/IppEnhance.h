#pragma once

#include "IppImage.h"

// ���� ����
void IppInverse(IppByteImage& img);
//void IppInverse(IppRgbImage& img);


// ��� ��ȭ
void IppBrightness(IppByteImage& img, int n);
void IppBrightness(IppRgbImage& img, int n);


// ��Ϻ� ��ȭ
void IppContrast(IppByteImage& img, int n);
void IppContrast(IppRgbImage& img, int n);


// ���� ����
void IppGammaCorrection(IppByteImage& img, float gamma);
void IppGammaCorrection(IppRgbImage& img, float gamma);

// ������׷�
void IppHistogram(IppByteImage& img, float histo[256]);

// ������׷� ��Ʈ��Ī
void IppHistogramStretching(IppByteImage& img);

// ������׷� �յ�ȭ
void IppHistogramEqualization(IppByteImage& img);

// ������ ���� ���� ����
bool IppAdd(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

// ������ ���� ���� ����
bool IppSub(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

// ������ ��� ���� ����
bool IppAve(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

// ������ ���� ���� ����
bool IppDiff(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

// ������ AND ���� ����
bool IppAND(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);

// ������ OR ���� ����
bool IppOR(IppByteImage& img1, IppByteImage& img2, IppByteImage& img3);


// ��Ʈ ��� ���ϴ� ���� ����
void IppBitPlane(IppByteImage& img1, IppByteImage& img2, int bit);