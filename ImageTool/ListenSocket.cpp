#include "pch.h"
#include "ListenSocket.h"
#include "ChildSocket.h"
#include "ChattingServerDlg.h"

#include "ChatClienLibarary/ServerListenAPI.h"
#pragma comment( lib, "Debug/ChatClienLibrary.lib" )

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

	CServerListenAPI API;
	API.APIAccept();
	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	CServerListenAPI API;
	API.APICloseClientSocket(pChild, m_ptrChildSocketList);
}


void CListenSocket::BroadCast(char* pszBuffer, int len)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	CServerListenAPI APIL;
	APIL.APIBroadCast(pszBuffer, len, m_ptrChildSocketList);
}

