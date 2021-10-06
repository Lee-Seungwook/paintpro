﻿// AddNoiseDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "AddNoiseDlg.h"
#include "afxdialogex.h"


// CAddNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(CAddNoiseDlg, CDialogEx)

CAddNoiseDlg::CAddNoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_NOISE, pParent)
	, m_nAmount(5)
	, m_nNoiseType(0)
{

}

CAddNoiseDlg::~CAddNoiseDlg()
{
}

void CAddNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Radio(pDX, IDC_NOISE_RADIO1, m_nAmount);
	//  DDV_MinMaxInt(pDX, m_nAmount, 0, 100);
	DDX_Text(pDX, IDC_NOISE_AMOUNT, m_nAmount);
	DDX_Radio(pDX, IDC_NOISE_RADIO1, m_nNoiseType);
}


BEGIN_MESSAGE_MAP(CAddNoiseDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddNoiseDlg 메시지 처리기


BOOL CAddNoiseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_AMOUNT))->SetRange(0, 100); // 스핀 버튼의 범위를 설정

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
