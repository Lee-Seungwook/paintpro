﻿// BinarizationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "BinarizationDlg.h"
#include "afxdialogex.h"

#include "IppImage/IppImage.h"
#include "IppImage/IppConvert.h"
#include "IppGeometry.h"
#include "IppSegment.h"


// CBinarizationDlg 대화 상자

IMPLEMENT_DYNAMIC(CBinarizationDlg, CDialogEx)

CBinarizationDlg::CBinarizationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BINARIZATION, pParent)
	, m_nThreshold(0)
{

}

CBinarizationDlg::~CBinarizationDlg()
{
}

void CBinarizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THRESHOLD_SLIDER, m_SliderThreshold);
	DDX_Text(pDX, IDC_THRESHOLD_EDIT, m_nThreshold);
	DDV_MinMaxInt(pDX, m_nThreshold, 0, 255);
}


BEGIN_MESSAGE_MAP(CBinarizationDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_THRESHOLD_EDIT, &CBinarizationDlg::OnChangeThresholdEdit)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBinarizationDlg 메시지 처리기

// 이미지 복사 및 초기 임계값 설정
void CBinarizationDlg::SetImage(IppDib& dib)
{
	m_DibSrc = dib;

	if (m_DibSrc.IsValid() != NULL)
		AfxMessageBox(_T("빵"));

	// 반복적 이진화 방법을 이용한 (초기) 임계값 설정
	IppByteImage imgSrc;
	IppDibToImage(m_DibSrc, imgSrc);
	m_nThreshold = IppBinarizationIterative(imgSrc);
}

// 미리보기 이미지 생성
void CBinarizationDlg::MakePreviewImage()
{
	// 현재 임계값을 이용하여 이진화된 미리보기 영상 생성
	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppBinarization(imgSrc, imgDst, m_nThreshold);
	IppImageToDib(imgDst, m_DibRes);
}


BOOL CBinarizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
		

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_SliderThreshold.SetRange(0, 255);
	m_SliderThreshold.SetTicFreq(32);
	m_SliderThreshold.SetPageSize(32);
	m_SliderThreshold.SetPos(m_nThreshold);

	// 픽쳐 컨트롤의 크기를 구함
	CRect rect;
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE_PREVIEW);
	pImageWnd->GetClientRect(rect);

	// 픽쳐 컨트롤의 크기에 맞게 입력 영상의 복사본의 크기를 조절
	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppResizeNearest(imgSrc, imgDst, rect.Width(), rect.Height());
	IppImageToDib(imgDst, m_DibSrc);

	// 초기 임계값에 의한 미리보기 이진화 영상 만들기
	MakePreviewImage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CBinarizationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	// 픽처 컨트롤에 영상 출력
	CPaintDC dcPreview(GetDlgItem(IDC_IMAGE_PREVIEW));
	m_DibRes.Draw(dcPreview.m_hDC, 0, 0);
}

void CBinarizationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 슬라이드바에서 발생한 WM_HSCROLL 메시지인 경우 처리
	if (m_SliderThreshold.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_SliderThreshold.GetPos();
		m_nThreshold = nPos;
		UpdateData(FALSE);

		// 현재 설정된 임계값을 이용하여 미리보기 영상의 이진화를 수행
		MakePreviewImage();
		Invalidate(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBinarizationDlg::OnChangeThresholdEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_SliderThreshold.SetPos(m_nThreshold);

	// 현재 설정된 임계값을 이용하여 미리보기 영상의 이진화를 수행
	MakePreviewImage();
	Invalidate(FALSE);
}



