#include "UIServerThread.h"
#include "ChattingServerDlg.h"

IMPLEMENT_DYNCREATE(CUIServerThread, CWinThread)


BOOL CUIServerThread::InitInstance()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CChattingServerDlg* dlg = new CChattingServerDlg();
	m_pMainWnd = dlg;
	INT_PTR nResult = dlg->DoModal();
	return TRUE;
}
