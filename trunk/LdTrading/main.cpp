// Test.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ui\MainDlg.h"
#include "..\StockDataAPI\web\HttpStockData.h"
#include <commctrl.h>
#define MAX_LOADSTRING 100

#pragma comment(lib,"Comctl32.lib")

// �˴���ģ���а����ĺ�����ǰ������:

HINSTANCE hInstance;
ITradInterface* TradClient = NULL;
CScriptEng* ScriptEng = NULL;
IDataInterface* DateInterface = NULL;

//���ӽ��������Ŀǰֻ֧��ͨ���ţ�
ITradInterface* ConnectTradClient()
{
	return new CTdxTrading();
}

BOOL InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInst,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	hInstance = hInst;

	InitInstance();

	CMainDlg dlg;
	dlg.ShowDialog(MAKEINTRESOURCE(IDD_DIALOG_MAIN));
	
	ScriptEng = new CScriptEng();
	DateInterface = new CHttpStockData();
	TradClient = ConnectTradClient();
	ScriptEng->SetDataInterface(DateInterface);
	ScriptEng->SetTradInterface(TradClient);

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

	if(ScriptEng)
		delete ScriptEng;
	if(TradClient)
		delete TradClient;
	if(DateInterface)
		delete DateInterface;

	return 0;
}

