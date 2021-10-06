#pragma once
#include "ClientSocket.h"

// CChattingClientDlg 대화 상자

class CChattingClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChattingClientDlg)

public:
	CChattingClientDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CChattingClientDlg();
	CClientSocket m_Client;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_CLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	CString m_strData;
	CButton m_ButtonSend;
	CButton m_ButtonConnect;
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonSend();
};
