#pragma once
#include <vector>
#include "IppImage/IppImage.h"
#include "IppFeature.h"
#include "IppImage/IppEnhance.h"
#include "ChatClienLibarary/SegmentAPI.h"
#pragma comment( lib, "ChatClienLibrary.lib")

class IppLabelInfo
{
public:
	std::vector<APIPoint> pixels; // ��ü �ȼ� ��ǥ ���
	int cx, cy; // ��ü�� �߽� ��ǥ
	int minx, miny, maxx, maxy; // ��ü�� ���δ� �簢�� ������ �»��, ���ϱ� ���� ��ǥ

public:
	IppLabelInfo() : cx(0), cy(0), minx(9999), miny(9999), maxx(0), maxy(0)
	{
		pixels.clear();
	}
};

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold);
int IppBinarizationIterative(IppByteImage& imgSrc);

int IppLabeling(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<APILabelInfo>& labels);

void IppContourTracing(IppByteImage& imgSrc, int sx, int sy, std::vector<APIPoint>& cp);

void IppMorphologyErosion(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyDilation(IppByteImage& imgSrc, IppByteImage& imgDst);

void IppMorphologyOpening(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyClosing(IppByteImage& imgSrc, IppByteImage& imgDst);

void IppMorphologyGrayErosion(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyGrayDilation(IppByteImage& imgSrc, IppByteImage& imgDst);

void IppMorphologyGrayOpening(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyGrayClosing(IppByteImage& imgSrc, IppByteImage& imgDst);

int LabelingDot(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<APILabelInfo>& labels);
