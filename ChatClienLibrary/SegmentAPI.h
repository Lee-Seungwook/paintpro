#pragma once
#include "..\ImageTool\stdafx.h"

#include "..\ImageTool\IppImage\IppImage.h"
#include "FeatureAPI.h"
#include "EnhanceAPI.h"
#ifdef _DLL_SEGMENT_
#define DLL_SEGMENT _declspec(dllexport)
#else		SEGMENT
#define DLL_SEGMENT __declspec(dllimport)
#endif // _DLL_SEGMENT_

class APILabelInfo
{
public:
	std::vector<APIPoint> pixels; // ��ü �ȼ� ��ǥ ���
	int cx, cy; // ��ü�� �߽� ��ǥ
	int minx, miny, maxx, maxy; // ��ü�� ���δ� �簢�� ������ �»��, ���ϱ� ���� ��ǥ

public:
	APILabelInfo() : cx(0), cy(0), minx(9999), miny(9999), maxx(0), maxy(0)
	{
		pixels.clear();
	}
};

class DLL_SEGMENT SegmentAPI
{
public:
	void APIBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold);
	int APIBinarizationIterative(IppByteImage& imgSrc);

	int APILabeling(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<APILabelInfo>& labels);

	void APIContourTracing(IppByteImage& imgSrc, int sx, int sy, std::vector<APIPoint>& cp);

	void APIMorphologyErosion(IppByteImage& imgSrc, IppByteImage& imgDst);
	void APIMorphologyDilation(IppByteImage& imgSrc, IppByteImage& imgDst);

	void APIMorphologyOpening(IppByteImage& imgSrc, IppByteImage& imgDst);
	void APIMorphologyClosing(IppByteImage& imgSrc, IppByteImage& imgDst);

	void APIMorphologyGrayErosion(IppByteImage& imgSrc, IppByteImage& imgDst);
	void APIMorphologyGrayDilation(IppByteImage& imgSrc, IppByteImage& imgDst);

	void APIMorphologyGrayOpening(IppByteImage& imgSrc, IppByteImage& imgDst);
	void APIMorphologyGrayClosing(IppByteImage& imgSrc, IppByteImage& imgDst);

	int APILabelingDot(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<APILabelInfo>& labels);
};
