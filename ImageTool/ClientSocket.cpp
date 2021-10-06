#include "pch.h"
#include "ClientSocket.h"
#include "ChattingClientDlg.h"
#include <Windows.h>



void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR : Disconnected from server!"));
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	// szBuffer�� ���� ���� �Ѿ��, �ڵ鷯�� ������ִ� ���� �߸��Ȱ� ����
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
