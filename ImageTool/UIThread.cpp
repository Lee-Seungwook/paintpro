#include "UIThread.h"
#include "ChattingClientDlg.h"
#include "..\ImageTool\IppImage\IppDib.h"

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)

CCriticalSection g_cs;


BOOL CUIThread::InitInstance()
{

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	g_cs.Lock();
	CChattingClientDlg* dlg = new CChattingClientDlg();
	m_pMainWnd = dlg;
	INT_PTR nResult = dlg->DoModal();
	g_cs.Unlock();
	/*CChattingClientDlg dlg;
	dlg.DoModal(); */
	return TRUE;
	
}


