#include "pch.h"
#include "ChattingServerDlg.h"
#include "ChildSocket.h"
#include "ListenSocket.h"

void CChildSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	// TODO: 여기에 구현 코드 추가.
	m_pListenSocket = pSocket;
}


void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CListenSocket* pServerSocket = (CListenSocket *)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	tmp = _T("");
	CString strIPAddress = _T("");
	UINT uPortNumber = 0;
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	GetPeerName(strIPAddress, uPortNumber);

	int len;
	if ((len = Receive(szBuffer, 1024)) > 0)
	{
		/*CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetApp()->GetMainWnd();
		pMain->m_ListServer.AddString(tmp);
		pMain->m_ListServer.SetCurSel(pMain->m_ListServer.GetCount() - 1);*/

		tmp.Format(_T("%s"), szBuffer);
		input = tmp;
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->BroadCast(szBuffer, len);
		AfxMessageBox(tmp);
	}
	
	CSocket::OnReceive(nErrorCode);
}