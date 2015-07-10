/*
ͨ���Ž���������

���ڽṹ��
	#32770 ͨ�������Ͻ���
		Afx:
			AfxMDIFrame42
					AfxWnd42   //�Ҳ���
						Afx
							SysTreeView32  //��Ʊ
							SysTreeView32  //����
							SysTreeView32  //ETF
							SysTreeView32  //�۹�ͨ
							SysTreeView32  //��ɫҵ��
					AfxWnd42      //   
						#32770
						#32770
						#32770
						#32770
						#32770
						#32770
						#32770
						#32770
						#32770
						#32770
*/
#include "..\stdafx.h"
#include "TDXMain.h"
#include "..\..\PublicLib\hooks\WindowHook.h"
#include "..\..\PublicLib\Utils_Wnd.h"

#define TIMERID_LEFT 0xADD      //��ʱ��ID��������������

CTDXMain* CTDXMain::WndHooker = NULL;

CTDXMain::CTDXMain(HWND hWnd): CWndHook(hWnd)
{
	m_hLeftPanel = NULL;
	m_hRightPanel = NULL;
	m_RightHook = NULL;
	m_StockSell = NULL;
	m_StockBuyDlg = NULL;

	FindChildWnds();
}


CTDXMain::~CTDXMain(void)
{
	CTDXMain::WndHooker = NULL;
}

LRESULT CTDXMain::WndPROC(HWND hwnd, UINT nCode,WPARAM wparam,LPARAM lparam)
{
	switch(nCode){
	case WM_DESTROY:
		delete CTDXMain::WndHooker;
		break;
	case MM_LOGINED:   //��¼��ɣ�ʶ����������ܲ˵�����
		InitRightWnds();
		ConnectLdTrad();  //�������س���
		if(!FindNavTreeViews()){  //������ɹ����ܵ�ԭ���ǲ˵����ڻ�û���ü����ز˵���
			SetTimer(m_hWnd, TIMERID_LEFT, 1000, NULL);  //��һ������
		}
		break;
	case WM_TIMER:  //���Բ���TreeView��ʱ
		if(wparam==TIMERID_LEFT){
			if(FindNavTreeViews()){
				KillTimer(m_hWnd, TIMERID_LEFT);
			}
		}
	}
	return CWndHook::WndPROC(hwnd, nCode, wparam, lparam);
}

BOOL CTDXMain::FindNavTreeViews()
{
	
	HWND hwnd = FindWindowEx(m_hLeftPanel, NULL, CN_SysTreeView32, NULL);

	while(hwnd!=NULL){//ȷ�Ϲ��ܲ˵�TreeView
		HTREEITEM item = TreeView_GetRoot(hwnd);
		if(item){
			PTdx_TreeItemParam param = (PTdx_TreeItemParam)TreeView_GetItemParam(hwnd, item);
			if(param){
				param = param->pParent;
			}
			if(param){
				Tdx_Tree_HWND map = {hwnd, param};
				m_NavTrees.Add(map);
			}
		}
		
		hwnd = FindWindowEx(m_hLeftPanel, hwnd, CN_SysTreeView32, NULL);
	}
	
	return TRUE;
}

class CRightPanelHook: public CWndHook
{
public:
	CTDXMain* mainWnd;

	CRightPanelHook(HWND hwnd):CWndHook(hwnd)
	{
	}

	virtual LRESULT WndPROC(HWND hwnd, UINT nCode,WPARAM wparam,LPARAM lparam)
	{
		if(nCode==WM_PARENTNOTIFY){
			TCHAR a[10] = {0};
			switch(LOWORD(wparam)){
			case WM_CREATE:  //�´��ڴ���
				for(int i=0; i<mainWnd->m_NavTrees.GetCount(); i++){
					if(IsWindowVisible(mainWnd->m_NavTrees[i].hTreeView)){
						HTREEITEM item = TreeView_GetSelection(mainWnd->m_NavTrees[i].hTreeView);
						Tdx_TreeItem_Dlg dlg = {mainWnd->m_NavTrees[i].hTreeView, item, (HWND)lparam};
						mainWnd->m_NavDialogs.Add(dlg);
					}
				}
				break;
			}
		}
		return CWndHook::WndPROC(hwnd, nCode, wparam, lparam);
	}
};

BOOL CTDXMain::InitRightWnds()
{
	if(m_hRightPanel){
		m_RightHook = new CRightPanelHook(m_hRightPanel);
		m_RightHook->mainWnd = this;
		return m_RightHook->StartHook();
	}else
		return false;
}

void CTDXMain::HookMainWnd(HWND hwnd)
{
	if(WndHooker==NULL){
		WndHooker = new CTDXMain(hwnd);
		WndHooker->StartHook();

		//OutputDebugString(L"MainWnd Hooked");
	};
}

void CTDXMain::FindChildWnds()
{
	HWND hChild = FindWindowEx(m_hWnd, NULL, NULL, NULL);
	if(hChild==NULL)  //��һ���Ӵ���
		return;
	hChild = FindWindowEx(hChild, NULL, CN_AfxMDIFrame42, NULL);
	if(hChild==NULL)
		return;

	HWND hPanel = FindWindowEx(hChild, NULL, CN_AfxWnd42, NULL);
	while(hPanel!=NULL){
		HWND childs[20] = {0};
		int count = EnumChildWnds(hPanel, childs, 20);

		if(count==1){              //�����
			m_hLeftPanel = childs[0];
		}else if(count==5){       //
			m_hRightPanel = hPanel;
		}
		hPanel = FindWindowEx(hChild, hPanel, CN_AfxWnd42, NULL);
	}
}

void CTDXMain::Click_Stock_Buy()
{
	Click_TreeItemByID(Stock_Buy_ID, Stock_ID);
}

HTREEITEM CTDXMain::Find_Nav_Item( HWND& hwnd, LPCSTR szID, LPCSTR szGroup)
{
	if(!szID)
		return NULL;
	PTdx_TreeItemParam pFound = NULL;
	for(int i=0; i<m_NavTrees.GetCount()-1; i++){
		PTdx_TreeItemParam pParam = m_NavTrees[i].pItem->pNext;

		while(pParam){
			if(strcmp(szID, pParam->pData->ID)==0){
				if((!szGroup)||
					(szGroup && pParam->pParent && strcmp(pParam->pParent->pData->ID, szGroup)==0)){
					pFound = pParam;
					break;
				}					
			}

			pParam = pParam->pNext;
		}
		if(pFound){
			hwnd = m_NavTrees[i].hTreeView;
			return FindTreeItemByParam(m_NavTrees[i].hTreeView, (LPARAM)pFound);
		}
	}

	return NULL;
}

void CTDXMain::Click_NavTreeItem( HWND hwnd, HTREEITEM item )
{
	RECT r = {0};

	for(int i=0; i<m_NavTrees.GetCount(); i++)
		if(IsWindowVisible(m_NavTrees[i].hTreeView)){
			GetWindowRect(m_NavTrees[i].hTreeView, &r);
			if(m_NavTrees[i].hTreeView!=hwnd){
				//��һ���л���������ܲ˵�ʱ�����ڴ�С��0��
				ShowWindow(hwnd, SW_SHOW);
				ShowWindow(m_NavTrees[i].hTreeView, SW_HIDE);
				MapWindowPoints(NULL, m_hLeftPanel, (LPPOINT)&r, 2);
				SetWindowPos(hwnd, m_hLeftPanel, r.left, r.top, r.right-r.left, r.bottom-r.top, SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_SHOWWINDOW);
			}
			break;
		}

	SetFocus(hwnd);
	HTREEITEM hParent = TreeView_GetParent(hwnd, item);
	while(hParent){
		TreeView_Expand(hwnd, hParent, TVE_EXPAND);
		hParent = TreeView_GetParent(hwnd, hParent);
	}

	//ʹItem�ɼ����������ָ���ƶ�����Ŀ��
	TreeView_SelectItem(hwnd, item);
	TreeView_SelectSetFirstVisible(hwnd, item);
	TreeView_GetItemRect(hwnd, item, &r, TRUE);
	POINT p = {r.left, r.top};
	ClientToScreen(hwnd, &p);
	SetCursorPos(p.x+5, p.y+5);
	//����Ϣ
	PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(p.x+5, p.y+5));
	PostMessage(hwnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(p.x+5, p.y+5));
}

HWND CTDXMain::Find_Dialog( LPCSTR szID, LPCSTR szGroup /*= NULL*/ )
{
	HWND result = NULL;
	for(int i=0; i<m_NavDialogs.GetCount(); i++){
		PTdx_TreeItemParam pParam = (PTdx_TreeItemParam)TreeView_GetItemParam(m_NavDialogs[i].hTreeView, m_NavDialogs[i].hItem);
		if(!pParam)
			continue;
		if(strcmp(szID, pParam->pData->ID)==0 &&
			((!szGroup) || strcmp(szGroup, pParam->pParent->pData->ID)==0)){
				result = m_NavDialogs[i].hDialog;
				break;
		}
	}
	return result;
}

CTDXStockBuy* CTDXMain::GetStockBuyDlg()
{
	if(m_StockBuyDlg==NULL){
		HWND hwnd = Find_Dialog(Stock_Buy_ID, Stock_ID);
		if(hwnd){
			m_StockBuyDlg = new CTDXStockBuy(hwnd);
			m_StockBuyDlg->StartHook();
		}
	}

	return m_StockBuyDlg;
}

CTDXStockSell* CTDXMain::GetStockSellDlg()
{
	if(m_StockSellDlg==NULL){
		HWND hwnd = Find_Dialog(Stock_Sell_ID, Stock_ID);
		if(hwnd){
			m_StockSellDlg = new CTDXStockSell(hwnd);
			m_StockSellDlg->StartHook();
		}
	}

	return m_StockSellDlg;
}

HTREEITEM CTDXMain::FindTreeItemByParam(HWND hwnd, LPARAM param, HTREEITEM hItem)
{
	if(hItem==NULL)
		hItem = TreeView_GetRoot(hwnd);
	while(hItem){
		LPARAM p = TreeView_GetItemParam(hwnd, hItem);
		if(p==param)
			return hItem;
		HTREEITEM hChild = TreeView_GetNextItem(hwnd, hItem, TVGN_CHILD);
		if(hChild){
			HTREEITEM result = FindTreeItemByParam(hwnd, param, hChild);
			if(result)
				return result;
		}
		hItem = TreeView_GetNextItem(hwnd, hItem, TVGN_NEXT);
	}
	return NULL;
}

void CTDXMain::Click_TreeItemByID(LPCSTR szID, LPCSTR szGroup /*= NULL*/)
{
	HWND hwnd = NULL;
	HTREEITEM item = Find_Nav_Item(hwnd, szID, szGroup);
	if(item)
		Click_NavTreeItem(hwnd, item);
}

void CTDXMain::ConnectLdTrad()
{
	;
}