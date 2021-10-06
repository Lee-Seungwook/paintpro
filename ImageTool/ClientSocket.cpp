#include "pch.h"
#include "ClientSocket.h"
#include "ChattingClientDlg.h"
#include <Windows.h>



void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR : Disconnected from server!"));
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	// szBuffer는 문제 없이 넘어옴, 핸들러를 만들어주는 것이 잘못된것 같음
	if (Receive(szBuffer, 1024) > 0)
	{
		CChattingClientDlg* pMain;
		pMain->m_List.AddString(_T("jaebal"));
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

		tmp.Format(_T("%s"), szBuffer);
		AfxMessageBox(tmp);

	}
	CSocket::OnReceive(nErrorCode);
}
