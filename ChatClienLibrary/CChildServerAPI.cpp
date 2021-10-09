#include "pch.h"
#include "afxdialogex.h"


#ifndef _DLL_CHILD_
#define _DLL_CHILD_
#endif // !_DLL_SERVER_

#include "CChildServerAPI.h"

void CChildServerAPI::APIReceive(char *szBuffer, CString& tmp, CString& strIPAddress, int len)
{
	/*CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetApp()->GetMainWnd();
	pMain->m_Server.AddString(tmp);
	pMain->m_Server.SetCurSel(pMain->m_List.GetCount() - 1);*/

	tmp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);
}