// Test.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ui\MainDlg.h"
#include "ITradInterface.h"
#include "interface\TdxTrading.h"

#define MAX_LOADSTRING 100

// �˴���ģ���а����ĺ�����ǰ������:

HINSTANCE hInstance;
ITradInterface* TradClient;

//���ӽ��������Ŀǰֻ֧��ͨ���ţ�
ITradInterface* ConnectTradClient()
{
	return new CTdxTrading();
}

int APIENTRY _tWinMain(HINSTANCE hInst,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	hInstance = hInst;

	CMainDlg dlg;
	dlg.ShowDialog(MAKEINTRESOURCE(IDD_DIALOG_MAIN));
	
	TradClient = ConnectTradClient();

	MSG msg;
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

