#pragma once

#include "IppImage.h"
#include "IppDib.h"

void IppDibToImage(IppDib& dib, IppByteImage& img); // IppDib Ŭ������ IppImage Ŭ������ ��ȯ
void IppDibToImage(IppDib& dib, IppRgbImage& img); // IppDib ��ü�� ǰ�� �ִ� DIB ������ �׷��̽����� �����̸� IppByte image ���, Ʈ���÷��̸� IppRgbImage�� ���
void IppImageToDib(IppByteImage& img, IppDib& dib);  // IppImage Ŭ������ IppDib Ŭ������ ��ȯ
void IppImageToDib(IppFloatImage& img, IppDib& dib); // ������ ������ ������ �ʿ䰡 �ְų�, �Ǽ��� �������� �����Ǵ� ��찡 �ֱ� �����̴�.
void IppImageToDib(IppRgbImage& img, IppDib& dib);
