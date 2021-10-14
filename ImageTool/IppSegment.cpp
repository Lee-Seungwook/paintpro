#include "stdafx.h"
#include "IppSegment.h"
#include "IppImage/IppEnhance.h"

SegmentAPI api;

// 영상 이진화 함수
// 입력 영상, 결과 영상, 임계값(임계값 보다 같거나 작으면 0, 크면 255로 픽셀 값 설정)
void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold)
{
	api.APIBinarization(imgSrc, imgDst, threshold);
}

// 임계값 결정 함수
int IppBinarizationIterative(IppByteImage& imgSrc)
{
	return api.APIBinarizationIterative(imgSrc);
}

// 고전적 레이블링 기법을 수행하는 함수
// 입력 영상, 레이블링이 수행된 후 레이블 맵이 저장될 정수형 영상, 검출된 객체들의 레이블 정보를 담을 컨테이너
int IppLabeling(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<APILabelInfo>& labels)
{
	return api.APILabeling(imgSrc, imgDst, labels);
}

//외곽선 검출
// 입력 영상, sx, sy는 외곽선 추적을 시작할 객체의 시작 좌표, 외곽선 픽셀 좌표를 저장할 컨테이너
void IppContourTracing(IppByteImage& imgSrc, int sx, int sy, std::vector<APIPoint>& cp)
{
	api.APIContourTracing(imgSrc, sx, sy, cp);
}

// 모폴로지 침식 연산
void IppMorphologyErosion(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyErosion(imgSrc, imgDst);
}

// 모폴로지 팽창 연산
void IppMorphologyDilation(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyDilation(imgSrc, imgDst);
}

// 모폴로지 열기 연산
void IppMorphologyOpening(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyOpening(imgSrc, imgDst);
}

// 모폴로지 닫기 연산
void IppMorphologyClosing(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyClosing(imgSrc, imgDst);
}

// 그레이 스케일 모폴로지 침식
void IppMorphologyGrayErosion(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyGrayErosion(imgSrc, imgDst);
}

// 그레이 스케일 모폴로지 팽창
void IppMorphologyGrayDilation(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyGrayDilation(imgSrc, imgDst);
}

// 그레이스케일 영상 열기
void IppMorphologyGrayOpening(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyGrayOpening(imgSrc, imgDst);
}

// 그레이스케일 영상 닫기
void IppMorphologyGrayClosing(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	api.APIMorphologyGrayClosing(imgSrc, imgDst);
}

int LabelingDot(IppByteImage& imgSrc, IppIntImage& imgDst, std::vector<APILabelInfo>& labels)
{
	return api.APILabelingDot(imgSrc, imgDst, labels);
}