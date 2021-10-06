﻿// ArithmeticLogicalDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "ArithmeticLogicalDlg.h"
#include "afxdialogex.h"
#include "ImageToolDoc.h"


// CArithmeticLogicalDlg 대화 상자

IMPLEMENT_DYNAMIC(CArithmeticLogicalDlg, CDialogEx)

CArithmeticLogicalDlg::CArithmeticLogicalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARITHMETIC_LOGICAL, pParent)
	, m_nFunction(0), m_pDoc1(NULL), m_pDoc2(NULL)
{

}

CArithmeticLogicalDlg::~CArithmeticLogicalDlg()
{
}

void CArithmeticLogicalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IMAGE1, m_comboImage1);
	DDX_Control(pDX, IDC_COMBO_IMAGE2, m_comboImage2);
	DDX_Radio(pDX, IDC_FUNCTION1, m_nFunction);
}


BEGIN_MESSAGE_MAP(CArithmeticLogicalDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CArithmeticLogicalDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CArithmeticLogicalDlg 메시지 처리기


BOOL CArithmeticLogicalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// 콤보 박스에 차일드 윈도우 창의 이름을 삽입
	int nIndex = 0;
	CString strTitle;

	CImageToolApp* pApp = (CImageToolApp*)AfxGetApp();
	POSITION pos = pApp->m_pImageDocTemplate->GetFirstDocPosition();

	while (pos != NULL) // 도큐먼트 템플릿에 연결된 모든 도큐먼트에 접근
	{
		CImageToolDoc* pDoc = (CImageToolDoc*)pApp->m_pImageDocTemplate->GetNextDoc(pos);
		if (pDoc->m_Dib.GetBitCount() != 8 && pDoc->m_Dib.GetBitCount() != 24) // 트루 컬러 영상은 콤보 박스에 추가하지 않는다.
			continue;

		strTitle = pDoc->GetTitle();

		m_comboImage1.InsertString(nIndex, strTitle);
		m_comboImage2.InsertString(nIndex, strTitle);

		m_comboImage1.SetItemDataPtr(nIndex, (void*)pDoc);
		m_comboImage2.SetItemDataPtr(nIndex, (void*)pDoc);

		nIndex++;
	}

	m_comboImage1.SetCurSel(0);
	m_comboImage2.SetCurSel(0);
	if (nIndex > 1) m_comboImage2.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CArithmeticLogicalDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDoc1 = (CImageToolDoc*)m_comboImage1.GetItemDataPtr(m_comboImage1.GetCurSel()); // 선택한 도큐먼트의 포인터를 저장
	m_pDoc2 = (CImageToolDoc*)m_comboImage2.GetItemDataPtr(m_comboImage2.GetCurSel()); // 선택한 도큐먼트의 포인터를 저장
	CDialogEx::OnOK();
}
