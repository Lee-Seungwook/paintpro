#include "stdafx.h"
#include "IppSegment.h"
#include "IppImage/IppEnhance.h"

SegmentAPI api;

// ���� ����ȭ �Լ�
// �Է� ����, ��� ����, �Ӱ谪(�Ӱ谪 ���� ���ų� ������ 0, ũ�� 255�� �ȼ� �� ����)
void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold)
{
	api.APIBinarization(imgSrc, imgDst, threshold);
}

// �Ӱ谪 ���� �Լ�
int IppBinarizationIterative(IppByteImage& imgSrc)
{
	return api.APIBinarizationIterative(imgSrc);
}

// ������ ���̺� ����� �����ϴ� �Լ�
// �Է� ����, ���̺��� ����� �� ���̺� ���� ����� ������ ����, ����� ��ü���� ���̺� ������ ���� �����̳�
int IppLabeling(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<APILabelInfo>& labels)
{
	return api.APILabeling(imgSrc, imgDst, labels);
}

//�ܰ��� ����
// �Է� ����, sx, sy�� �ܰ��� ������ ������ ��ü�� ���� ��ǥ, �ܰ��� �ȼ� ��ǥ�� ������ �����̳�
void IppContourTracing(IppByteImage& imgSrc, int sx, int sy, std::vector<APIPoint>& cp)
{
	api.APIContourTracing(imgSrc, sx, sy, cp);
}

// �������� ħ�� ����
void IppMorphologyErosion(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyErosion(imgSrc, imgDst);
}

// �������� ��â ����
void IppMorphologyDilation(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyDilation(imgSrc, imgDst);
}

// �������� ���� ����
void IppMorphologyOpening(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyOpening(imgSrc, imgDst);
}

// �������� �ݱ� ����
void IppMorphologyClosing(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyClosing(imgSrc, imgDst);
}

// �׷��� ������ �������� ħ��
void IppMorphologyGrayErosion(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyGrayErosion(imgSrc, imgDst);
}

// �׷��� ������ �������� ��â
void IppMorphologyGrayDilation(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyGrayDilation(imgSrc, imgDst);
}

// �׷��̽����� ���� ����
void IppMorphologyGrayOpening(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyGrayOpening(imgSrc, imgDst);
}

// �׷��̽����� ���� �ݱ�
void IppMorphologyGrayClosing(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyGrayClosing(imgSrc, imgDst);
}

int LabelingDot(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<APILabelInfo>& labels)
{
	return api.APILabelingDot(imgSrc, imgDst, labels);
}