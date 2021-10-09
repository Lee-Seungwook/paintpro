#pragma once
#include "stdafx.h"



class CUIThread :
	public CWinThread
{
public:
	DECLARE_DYNCREATE(CUIThread)

	virtual BOOL InitInstance();
};

