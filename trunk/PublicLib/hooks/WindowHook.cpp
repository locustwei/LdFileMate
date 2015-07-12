
#include "..\stdafx.h"
#include "WindowHook.h"

CWndHook::CWndHook(HWND hWind)
{
	ZeroMemory(m_ClassName, MAX_PATH*sizeof(TCHAR));
	GetClassName(hWind, m_ClassName, MAX_PATH);
	ZeroMemory(m_Text, MAX_PATH*sizeof(TCHAR));
	GetWindowText(hWind, m_Text, MAX_PATH);
	m_nextHook=NULL;
	m_hWnd=hWind;
}

CWndHook::~CWndHook()
{
	StopHook();
}

BOOL CWndHook::StopHook()
{
    BOOL bResult = FALSE;
    if (m_nextHook){
        bResult = SetWindowLongPtr(m_hWnd, GW_WNDPROC, (LONG)m_nextHook);
		SetWindowLong(m_hWnd, GW_HOOKPOINT, NULL);
        if (bResult){
            m_nextHook = NULL;
        }
    }
    return bResult;
}

LRESULT WINAPI WndHookPROC(HWND hwnd, UINT nCode,WPARAM wparam,LPARAM lparam)
{
	CWndHook* m_this = (CWndHook*)GetWindowLong(hwnd, GW_HOOKPOINT);
	if(m_this!=NULL)
		return m_this->WndPROC(hwnd, nCode, wparam, lparam);
	else
		return DefWindowProc(hwnd,nCode,wparam,lparam);
}

BOOL CWndHook::StartHook()
{
    if(!IsWindow(m_hWnd)) 
		return false; //Window ��Ч
	if(m_nextHook) 
		return false; //�Ѿ��й�����
	
	SetWindowLong(m_hWnd, GW_HOOKPOINT, (LONG)this);
	if(wcscmp(m_ClassName, CN_Dialog)==0)
		m_nextHook = (WNDPROC)SetWindowLongPtr(m_hWnd, DWLP_DLGPROC, (LONG)&WndHookPROC);
	else
		m_nextHook = (WNDPROC)SetWindowLongPtr(m_hWnd, GW_WNDPROC,  (LONG)&WndHookPROC);

	return !m_nextHook;
}

LRESULT CWndHook::WndPROC(HWND hwnd, UINT nCode,WPARAM wparam,LPARAM lparam)
{
	LRESULT result = CallWindowProc(m_nextHook, hwnd, nCode, wparam, lparam);

	if(nCode==WM_DESTROY){
		StopHook();
	}

	return result;
}