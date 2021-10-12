#include "pch.h"
#include "ListenSocket.h"
#include "ChildSocket.h"
#include "ChattingServerDlg.h"

#include "ChatClienLibarary/ServerListenAPI.h"
#pragma comment( lib, "ChatClienLibrary.lib" )

void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CChildSocket* pChild = new CChildSocket;

	BOOL check = Accept(*pChild);

	if (check == FALSE) {
		delete pChild;
		AfxMessageBox(_T("����������"));
		return;
	}

	pChild->SetListenSocket(this);
	m_ptrChildSocketList.AddTail(pChild);

	CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();

	pMain->m_ListServer.AddString(_T("���� ���� ���"));
	pMain->m_ListServer.SetCurSel(pMain->m_ListServer.GetCount() - 1);
	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	POSITION pos;
	pos = m_ptrChildSocketList.Find(pChild);
	if (pos != NULL) {
		pChild->ShutDown();
		pChild->Close();
	}
	m_ptrChildSocketList.RemoveAt(pos);
	delete pChild;
	//CServerListenAPI API;
	//API.APICloseClientSocket(pChild, m_ptrChildSocketList);
}


void CListenSocket::BroadCast(char* pszBuffer, int len)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;

	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos);
		if (pChild != NULL)
			pChild->Send(pszBuffer, len * 2);
	}
	/*CServerListenAPI APIL;
	APIL.APIBroadCast(pszBuffer, len, m_ptrChildSocketList);*/
}

