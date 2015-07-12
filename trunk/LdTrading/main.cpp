// Test.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ui\MainDlg.h"
#include "..\StockDataAPI\web\HttpStockData.h"
#define MAX_LOADSTRING 100

// �˴���ģ���а����ĺ�����ǰ������:

HINSTANCE hInstance;
ITradInterface* TradClient;
CScriptEng* ScriptEng;
IDataInterface* DateInterface;

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

	return 0;
}

