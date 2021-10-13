#include "UIThread.h"
#include "ChattingClientDlg.h"
#include "..\ImageTool\IppImage\IppDib.h"

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)

CCriticalSection g_cs;


BOOL CUIThread::InitInstance()
{

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	g_cs.Lock();
	CChattingClientDlg* dlg = new CChattingClientDlg();
	m_pMainWnd = dlg;
	INT_PTR nResult = dlg->DoModal();
	g_cs.Unlock();
	/*CChattingClientDlg dlg;
	dlg.DoModal(); */
	return TRUE;
	
}


