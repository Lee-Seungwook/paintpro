﻿// FileNewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "FileNewDlg.h"
#include "afxdialogex.h"


// CFileNewDlg 대화 상자

IMPLEMENT_DYNAMIC(CFileNewDlg, CDialogEx)

CFileNewDlg::CFileNewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILE_NEW, pParent)
	, m_nWidth(0)
	, m_nHeight(0)
	, m_nType(0)
{

}

CFileNewDlg::~CFileNewDlg()
{
}

void CFileNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 1, 4096);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDX_CBIndex(pDX, IDC_IMAGE_TYPE, m_nType);
}


BEGIN_MESSAGE_MAP(CFileNewDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileNewDlg 메시지 처리기
