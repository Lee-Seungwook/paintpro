#pragma once

#include "IppImage/IppImage.h"

// �̵� ��ȯ
void IppTranslate(IppByteImage& imgSrc, IppByteImage& imgDst, int sx, int sy);
void IppTranslate(IppRgbImage& imgSrc, IppRgbImage& imgDst, int sx, int sy);

// �ֱٹ� �̿� ������
void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);

// �缱�� ������
void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);

// 3�� ȸ�� ������
void IppResizeCubic(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);
double cubic_interpolation(double v1, double v2, double v3, double v4, double d); // ���� 4���� ���� �̿��� �������� �̿��Ͽ� ���� ��ȯ


// ������ ȸ�� ��ȯ
void IppRotate(IppByteImage& imgSrc, IppByteImage& imgDst, double angle); // angle�� �ð���� ȸ�� ����

// ������ 90�� ȸ�� ��ȯ
void IppRotate90(IppByteImage& imgSrc, IppByteImage& imgDst);
// ������ 180�� ȸ�� ��ȯ
void IppRotate180(IppByteImage& imgSrc, IppByteImage& imgDst);
// ������ 270�� ȸ�� ��ȯ
void IppRotate270(IppByteImage& imgSrc, IppByteImage& imgDst);


// ������ �¿� ����
void IppMirror(IppByteImage& imgSrc, IppByteImage& imgDst);

// ������ ���� ����
void IppFlip(IppByteImage& imgSrc, IppByteImage& imgDst);
