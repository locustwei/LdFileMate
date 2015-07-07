#pragma once
#include "..\PublicLib\hooks\WindowHook.h"
#include "..\PublicLib\comps\LdList.h"
#include "TDXDataStruct.h"
#include <commctrl.h>
#include "TDXStockBuy.h"
#include "TDXStockSell.h"


class CTDXMain :public CWndHook
{
	friend class CRightPanelHook;
public:
	CTDXMain(HWND hWnd);
	~CTDXMain(void);

	static CTDXMain* WndHooker;
	static void HookMainWnd(HWND hwnd);

	void Click_Stock_Buy(); //�����Ʊ����
	void Click_TreeItemByID(LPCSTR szID, LPCSTR szGroup = NULL);
	CTDXStockBuy* GetStockBuyDlg();
	CTDXStockSell* GetStockSellDlg();
protected:
	virtual LRESULT WndPROC(HWND hwnd, UINT nCode,WPARAM wparam,LPARAM lparam);
private:
	HWND m_hLeftPanel;
	HWND m_hRightPanel;
	CRightPanelHook* m_RightHook;         //�Ҳ�����������Hook���ز������ڴ�����Ϣ
	CTDXStockBuy* m_StockBuyDlg;
	CTDXStockSell* m_StockSell;

	BOOL FindNavTreeViews();             //�ҵ������˵�TreeView��
	BOOL InitRightWnds();                //�ڲ��������������Hook��
	void FindChildWnds();                //�ҵ������˵����������������
	CLdList<Tdx_Tree_HWND> m_NavTrees;   //���ܲ˵���TreeView���飨�Ӱ汾��ͬ���ܰ�������Ʊ������������������ETF���������۹�ͨ�������ȣ�
	CLdList<Tdx_TreeItem_Dlg> m_NavDialogs;                                      //���ܲ˵����������Dialog���飨�磺��Ʊ���봰�ڡ���Ʊ�������ڵȣ�
	CTDXStockSell* m_StockSellDlg;
	void Click_NavTreeItem( HWND hwnd, HTREEITEM item );                        //ģ���û�������ܲ˵����ϵ�һ���ڵ㡣
	HWND Find_Dialog( LPCSTR szID, LPCSTR szGroup = NULL);                      //����szID�ҵ���������
	HTREEITEM Find_Nav_Item( HWND& hwnd, LPCSTR szID, LPCSTR szGroup = NULL );  //����szID��TcOem.xml�ж��壩�ҵ�TreeView�е�Item��
	HTREEITEM FindTreeItemByParam(HWND hwnd,  LPARAM param, HTREEITEM hItem = NULL);
};
