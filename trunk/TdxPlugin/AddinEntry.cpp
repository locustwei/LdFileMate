#include "AddinEntry.h"
#include "TDXLogin.h"
#include "..\publiclib\Utils_Wnd.h"
#include "TDXMain.h"
#include "..\publiclib\comps\NotifyIcon.h"
#include "..\publiclib\comps\LdList.h"
#include "TDXDataStruct.h"
#include <stdio.h>

HWND hWndLogin = NULL, hWndMain = NULL;


BOOL CALLBACK EnumThreadWndProc(HWND hwnd, LPARAM lparam)
{
	if(WndClassNameIs(hwnd, CN_Dialog)){
		DWORD style = GetWindowLong(hwnd, GWL_STYLE);
		if(style==0x94000044){
			hWndLogin = hwnd;
		}else if(style==0x0CCF0044)
			hWndMain = hwnd;
	}
	return hWndLogin == NULL || hWndMain == NULL;
}

WNDPROC oldProc;

//����ʱ��ʱʹ�ù��ӣ�����ע�����������߳�
LRESULT WINAPI TempWndPROC(HWND hwnd, UINT nCode,WPARAM wparam,LPARAM lparam)
{
	if(nCode==MM_RUNONMAINTHREAD){
		(WNDPROC)SetWindowLongPtr(hWndLogin, GW_WNDPROC, (LONG)oldProc); //����ʹ����ɻ�ԭ����
		((RUNONPROC)wparam)(lparam);
	}
	return CallWindowProc(oldProc, hwnd, nCode, wparam, lparam);
}

void CopyTreeItemParam(HWND hTreeView, HTREEITEM hitem, FILE* f)
{
	int length = 0x40;
	int k = 0;
	while(hitem){
		LPARAM param = TreeView_GetItemParam(hTreeView, hitem);
		if(param){
			//fwrite(&k, 1, 4, f);
	 		//fwrite((PCHAR)param, 1, length, f);

			//fwrite((PCHAR)(&param), 1, 4, f);
			fwrite((PCHAR)(*(PDWORD)(param+24)), 4, length, f);
		}
		k++;
		HTREEITEM hChild = TreeView_GetChild(hTreeView, hitem);
		if(hChild)
			CopyTreeItemParam(hTreeView, hChild, f);
		hitem = TreeView_GetNextSibling(hTreeView, hitem);
	}
}

void CopyTreeViewParam(LPCSTR file, HWND hTreeView)
{
	FILE* f = NULL;
	fopen_s(&f, file, "w");
	if(!f)
		return;

	HTREEITEM hitem = TreeView_GetRoot(hTreeView);
	CopyTreeItemParam(hTreeView, hitem, f);
 	fclose(f);
}

//�����̳߳���ʼ����
int InitOnMainThread(LPARAM param)
{
// 	if(!InitNavTree())
// 		return 0;

	if(hWndLogin!=NULL){
		CTDXLogin::WndHooker = new CTDXLogin(hWndLogin);
		CTDXLogin::WndHooker->StartHook();
	}

	if(hWndMain!=NULL){
		CTDXMain::WndHooker = new CTDXMain(hWndMain);
		CTDXMain::WndHooker->StartHook();
	}

	return 0;
}

BOOL InstallHooks(DWORD tid)
{
	EnumThreadWindows(tid, &EnumThreadWndProc, 0);
	if(hWndLogin!=NULL){
		if(tid == GetCurrentThreadId())
			InitOnMainThread(0);
		else{
			/*��ǰ�̲߳������̣߳����������߳����������ڵȶ�����������߳�ͬ�����⡣
			�������ҵ���¼����������Ϣ���ӣ�Ȼ������Ϣ�����߳�ִ�г�ʼ������*/

			oldProc = (WNDPROC)SetWindowLongPtr(hWndLogin, GW_WNDPROC, (LONG)&TempWndPROC);
			SendMessage(hWndLogin, MM_RUNONMAINTHREAD, (WPARAM)&InitOnMainThread, 0);
		}
		return TRUE;
	}else
		return FALSE;
}

void UnInstallHooks()
{
}