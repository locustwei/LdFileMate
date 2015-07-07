/**
ϵͳ�����Ϸ�һ��ICON
**/ 
#pragma once

#include "..\stdafx.h"
#include <ShellAPI.h>

#define NOTIFYICON_MESSAGE WM_USER+0x894A

class CNotifyIcon;

struct INotifyIconListener{
	CNotifyIcon* m_Icon;
	virtual void OnRightClick(POINT pos) = 0;
	virtual void OnLeftClick(POINT pos) = 0;
	virtual void OnDbClick() = 0;
	virtual HICON GetIcon() = 0;
	virtual LPCTSTR GetTipText() = 0;
	virtual void OnMenuClick(int menuid) = 0;
};

///////////////////////////////////////////////////////////////////////////// 
// CNotifyIcon window 
class CNotifyIcon {
// Construction/destruction 
public: 
	CNotifyIcon(INotifyIconListener* listener); 
	virtual ~CNotifyIcon(); 
// Operations 
public: 
	BOOL IsVisible() { return !m_bShowing; } 

	BOOL ShowIcon(); 
	void HideIcon(); 
	void PopupMenu(HMENU hmenu, POINT pos);
protected: 
	//����ϵͳͼ�� 

	BOOL m_bShowing; //�Ƿ�����ͼ�� 
	HWND m_hWnd;  //������Ϣ����
	NOTIFYICONDATA m_tnd; //���ݽṹ����ο����߰��� 
	INotifyIconListener* m_Listener;

	LRESULT OnIconNotification(HWND hwnd, UINT wParam, LONG lParam);
	void NotifyMenuItemClicked(int menuId);

private:
	HWND CreateNotifyWindow();
	static LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wparam,LPARAM lparam);
};
