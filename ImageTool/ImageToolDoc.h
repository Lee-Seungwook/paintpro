﻿
// ImageToolDoc.h: CImageToolDoc 클래스의 인터페이스
//


#pragma once
#include ".\IppImage\IppDib.h" // 상대경로 지정


class CMyData;
class CMyStick;
class CMyEllipse;
class CMyRect;
class CMyRoundRect;
class CMyTriangle;
class CMyRightTriangle;
class CMyRhombus;
class CMyPentagon;
class CMyErase;
class CMyColorFill;

class CImageToolDoc : public CDocument
{
public: // serialization에서만 만들어집니다.
	CImageToolDoc() noexcept;
	DECLARE_DYNCREATE(CImageToolDoc)

// 특성입니다.
public:
	CTypedPtrList<CObList, CMyData*> m_MyDataList;
	CTypedPtrList<CObList, CMyStick*> m_MyStickList;
	CTypedPtrList<CObList, CMyEllipse*> m_MyEllipseList;
	CTypedPtrList<CObList, CMyRect*> m_MyRectList;
	CTypedPtrList<CObList, CMyRoundRect*> m_MyRoundRectList;
	CTypedPtrList<CObList, CMyTriangle*> m_MyTriangleList;
	CTypedPtrList<CObList, CMyRightTriangle*> m_MyRightTriangleList;
	CTypedPtrList<CObList, CMyRhombus*> m_MyRhombusList;
	CTypedPtrList<CObList, CMyPentagon*> m_MyPentagonList;
	CTypedPtrList<CObList, CMyErase*> m_MyEraseList;
	CTypedPtrList<CObList, CMyColorFill*> m_MyColorFillList;
// 작업입니다.
public:
	CWinThread *pThread1;
	BYTE* ThreadP;
	
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// 비트맵 객체
	IppDib m_Dib; // 클래스 형식의 멤버변수
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
	afx_msg void OnImageInverse();
	afx_msg void OnUpdateImageInverse(CCmdUI *pCmdUI);
	afx_msg void OnColorimageInverse();
	afx_msg void OnUpdateColorimageInverse(CCmdUI *pCmdUI);
	afx_msg void OnBrightnessContrast();
	afx_msg void OnUpdateBrightnessContrast(CCmdUI *pCmdUI);
	afx_msg void OnColorbrightnessContrast();
	afx_msg void OnUpdateColorbrightnessContrast(CCmdUI *pCmdUI);
	afx_msg void OnGammaCorrection();
	afx_msg void OnViewHistogram();
	afx_msg void OnHistoStretching();
	afx_msg void OnHistoEqualization();
	afx_msg void OnArithmeticLogical();
	afx_msg void OnBitplaneSlicing();
	afx_msg void OnFilterMean();
	afx_msg void OnFilterWeightedMean();
	afx_msg void OnFilterGaussian();
	afx_msg void OnFilterLaplacian();
	afx_msg void OnFilterUnsharpMask();
	afx_msg void OnFilterHighboost();
	afx_msg void OnAddNoise();
	afx_msg void OnFilterMedian();
	afx_msg void OnFilterDiffusion();
	afx_msg void OnImageTranslation();
	afx_msg void OnImageResize();
	afx_msg void OnImageRotate();
	afx_msg void OnImageMirror();
	afx_msg void OnImageFlip();
	virtual void DeleteContents();
	afx_msg void OnFourierDft();
	afx_msg void OnFourierDftrc();
	afx_msg void OnFourierFft();
	afx_msg void OnFreqFiltering();
	afx_msg void OnEdgeRoberts();
	afx_msg void OnEdgePrewitt();
	afx_msg void OnEdgeSobel();
	afx_msg void OnEdgeCanny();
	afx_msg void OnHoughLine();
	afx_msg void OnHarrisCorner();
	afx_msg void OnColorGrayscale();
	afx_msg void OnUpdateColorGrayscale(CCmdUI *pCmdUI);
	afx_msg void OnColorSplitRgb();
	afx_msg void OnUpdateColorSplitRgb(CCmdUI *pCmdUI);
	afx_msg void OnColorSplitHsi();
	afx_msg void OnUpdateColorSplitHsi(CCmdUI *pCmdUI);
	afx_msg void OnColorSplitYuv();
	afx_msg void OnUpdateColorSplitYuv(CCmdUI *pCmdUI);
	afx_msg void OnColorCombineRgb();
	afx_msg void OnColorCombineHsi();
	afx_msg void OnColorCombineYuv();
	afx_msg void OnColorEdge();
	afx_msg void OnUpdateColorEdge(CCmdUI *pCmdUI);
	afx_msg void OnColorHisto();
	afx_msg void OnUpdateColorHisto(CCmdUI *pCmdUI);
	afx_msg void OnSegmentBinarization();
	afx_msg void OnSegmentLabeling();
	afx_msg void OnContourTacing();
	afx_msg void OnMorpologyErosion();
	afx_msg void OnMorpologyDilation();
	afx_msg void OnMorpologyOpening();
	afx_msg void OnMorpologyClosing();
	afx_msg void OnGraymorphErosion();
	afx_msg void OnGraymorphDilation();
	afx_msg void OnGraymorphOpening();
	afx_msg void OnGraymorphClosing();
	afx_msg void OnUpdateFilterGaussian(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFilterDiffusion(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFreqFiltering(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFourierDft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFourierDftrc(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFourierFft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHoughLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSegmentLabeling(CCmdUI *pCmdUI);
	afx_msg void OnUpdateContourTacing(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMorpologyClosing(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMorpologyDilation(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMorpologyErosion(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMorpologyOpening(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGraymorphClosing(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGraymorphDilation(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGraymorphErosion(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGraymorphOpening(CCmdUI *pCmdUI);
	afx_msg void OnTruecolorErosion();
	afx_msg void OnTruecolorDilation();
	afx_msg void OnTruecolorOpening();
	afx_msg void OnTruecolorClosing();
	afx_msg void OnUpdateTruecolorErosion(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTruecolorDilation(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTruecolorOpening(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTruecolorClosing(CCmdUI *pCmdUI);
	afx_msg void OnSearchDot();
	afx_msg void OnSearchNoise();
	afx_msg void OnUpdateBitplaneSlicing(CCmdUI *pCmdUI);
};


