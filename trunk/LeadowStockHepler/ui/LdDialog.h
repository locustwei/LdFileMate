/********************************************************************
	created:	2013/12/07
	created:	7:12:2013   23:54
	author:		����
	
	purpose:	��չCDialogExʵ��û����ԴID�ķ�ʽ�����������ڣ�ȥ��Dialog���ԣ�
*********************************************************************/
#pragma once
#include <afxdialogex.h>
#include "..\Resource.h"

typedef struct _DLGITEM_MAP
{
	int ItemId;
	CWnd* wnd;
}DLGITEM_MAP, *PDLGITEM_MAP;

class CLdDialog: public CDialogEx
{ 
	DECLARE_DYNAMIC(CLdDialog)

public: 
	CLdDialog();
	virtual ~CLdDialog();
	virtual BOOL Create( CWnd* pParentWnd = NULL );

protected: 
	int m_nResId;
	virtual void OnOK();
	virtual void OnCancel();
}; 

