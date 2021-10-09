#include "pch.h"
#include "afxdialogex.h"

#ifndef  _DLL_CLIENT_
#define _DLL_CLIENT_
#endif // ! _DLL_CLIENT_

#include "ClientAPI.h"

void ClientAPI::APIClose(int nErrorCode)
{
	ShutDown();
	Close();
	AfxMessageBox(_T("ERROR : Disconnected from server!"));
}

void ClientAPI::APIReceive(char *szBuffer, CString& tmp, CChattingClientDlg* (&handle))
{
	// szBuffer�� ���� ���� �Ѿ��, �ڵ鷯�� ������ִ� ���� �߸��Ȱ� ����
	tmp.Format(_T("%s"), szBuffer);
	
	
	handle->m_List.AddString(tmp);
	handle->m_List.SetCurSel(handle->m_List.GetCount() - 1);

	AfxMessageBox(_T("����Ʈ �߰� Ȯ��"));
}