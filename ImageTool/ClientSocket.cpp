#include "pch.h"
#include "ClientSocket.h"
#include "ChattingClientDlg.h"
#include <Windows.h>

#include "..\ChatClienLibrary\ClientAPI.h"
#pragma comment( lib, "ChatClienLibrary.lib")

void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	ClientAPI APIC;
	APIC.APIClose(nErrorCode);
	CSocket::OnClose(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	if (Receive(szBuffer, 1024) > 0)
	{
		// tmp.Format(_T("%s"), szBuffer);
		ClientAPI APIR;
		APIR.APIReceive(szBuffer, tmp);
	}
	CSocket::OnReceive(nErrorCode);
}
