#include "UIThread.h"
#include "ChattingClientDlg.h"
#include "..\ImageTool\IppImage\IppDib.h"

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)




BOOL CUIThread::InitInstance()
{

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	
	CChattingClientDlg* dlg = new CChattingClientDlg();
	m_pMainWnd = dlg;
	INT_PTR nResult = dlg->DoModal();
	return TRUE;
	
}


