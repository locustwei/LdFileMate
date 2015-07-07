/************************************************************************/
/* ͨ�������ݽṹ
��ȫ�����ݡ�
*/
/************************************************************************/

#pragma once
#include "stdafx.h"
#include <commctrl.h>

#define PLUG_FILENAME L"TdxPlugin.dll"

#define Stock_ID "��Ʊ" //FeatureID "group.stock" HomeFeatureID "" Title "��Ʊ">
#define Stock_Buy_ID "Stock.Buy" //FeatureID "Stock.Buy" Title "����" Image "1"/>
#define Stock_Sell_ID "Stock.Sell" //FeatureID "Stock.Sell" Title "����" Image "2"/>
#define Stock_marketBuy_ID "Stock.marketBuy" //FeatureID "Stock.marketBuy" Title "�м�����" Image "1"/>
#define Stock_marketsell_ID "Stock.marketsell" //FeatureID "Stock.marketsell" Title "�м�����" Image "2"/>
#define Stock_SingleBuylots_ID "Stock.SingleBuylots" //FeatureID "Stock.SingleBuylots" Title "���ʻ���������" Image "1"/>
#define Stock_SingleSellLots_ID "Stock.SingleSellLots" //FeatureID "Stock.SingleSellLots" Title "���ʻ���������" Image "2"/>
#define query_ID "query" //FeatureID "AlwaysOn" Title "��ѯ" Image "5">
#define Stock_zjgf_ID "Stock.zjgf" //FeatureID "Stock.zjgf" Title "�ʽ�ɷ�"/>
#define Stock_lscjcx_ID "Stock.lscjcx" //FeatureID "Stock.lscjcx" Title "��ʷ�ɽ�"/>
#define Stock_dzd_ID "Stock.dzd" //FeatureID "Stock.dzd" Title "�ʽ���ϸ"/>
#define Stock_zjls_ID "Stock.zjls" //FeatureID "Stock.zjls" Title "�ʽ���ϸ"/>
#define Stock_cjhzcx_id "Stock.cjhzcx" //FeatureID "Stock.cjhzcx" Title "���ճɽ����ܲ�ѯ"/>
#define Stock_wthzcx_ID "Stock.wthzcx" //FeatureID "Stock.wthzcx" Title "����ί�л��ܲ�ѯ"/>
#define Stock_lscjhzcx_ID "Stock.lscjhzcx" //FeatureID "Stock.lscjhzcx" Title "��ʷ�ɽ����ܲ�ѯ"/>		

#define YXJY_ID "YXJY" //FeatureID "AlwaysOn" Title "�ɷݱ���ת��">
#define Stock_yxmr_ID "Stock.yxmr" //FeatureID "Stock.yxmr" Title "��������"/>
#define Stock_yxmc_ID "Stock.yxmc" //FeatureID "Stock.yxmc" Title "��������"/>
#define Stock_djmr_ID "Stock.djmr" //FeatureID "Stock.djmr" Title "��������"/>
#define Stock_djmc_ID "Stock.djmc" //FeatureID "Stock.djmc" Title "��������"/>
#define Stock_cjqrmr_ID "Stock.cjqrmr" //FeatureID "Stock.cjqrmr" Title "�ɽ�ȷ������"/>	
#define Stock_cjqrmc_ID "Stock.cjqrmc" //FeatureID "Stock.cjqrmc" Title "�ɽ�ȷ������"/>		
#define Stock_yxhqcx_ID "Stock.yxhqcx" //FeatureID "Stock.yxhqcx" Title "���������ѯ"/>					

//#define lof_ID "lof" FeatureID "AlwaysOn" Title "����ί��" Image "5">
#define Stock_ymd_ID "Stock.ymd" //FeatureID "Stock.ymd" Title "Ԥ��" Image "4"/>
#define Stock_yjwt_ID "Stock.yjwt" //FeatureID "Stock.yjwt" Title "Ԥ��ί��" Image "7"/>

//�������������ṹ(TcOem.xml�ļ�)
typedef struct _Nav_Tree
{
	//ID "��Ʊ" FeatureID "group.stock" HomeFeatureID "" Title "��Ʊ"
	LPTSTR ID;
	LPTSTR FeatureID;
	LPTSTR Title;
	LPTSTR HomeFeatureID;
	LPTSTR HotKeytc;
	int count;
	_Nav_Tree* Items;
}Nav_Tree, *PNav_Tree;

//TDX����ʱTreeItem Param�����ж�ӦTcOem.xml�ļ������ݽṹ
typedef struct _Tdx_TreeItemData
{
	_Tdx_TreeItemData* pID;
	_Tdx_TreeItemData* pFeatureID;
	CHAR ID[0x40];
	CHAR FeatureID[0x40];
}Tdx_TreeItemData, *PTdx_TreeItemData;

//TDX������TreeItem Param�Ľṹ(TreeView_GetItemParam)
typedef struct _Tdx_TreeItemParam
{
	_Tdx_TreeItemParam* pNext;
	_Tdx_TreeItemParam* pPrev;
	DWORD unknow_1;
	_Tdx_TreeItemParam* pParent;
	DWORD unknow_2;
	DWORD unknow_3;
	PTdx_TreeItemData pData;
}Tdx_TreeItemParam, *PTdx_TreeItemParam;

//ͨ���ŵ����˵�����TreeView���ڶ�Ӧ
typedef struct _Tdx_Tree_HWND
{
	HWND hTreeView;
	PTdx_TreeItemParam pItem;
}Tdx_Tree_HWND, *PTdx_Tree_HWND;

//ͨ���ŵ����˵���Ŀ��DialogBox��Ӧ
typedef struct _Tdx_TreeItem_Dlg
{
	HWND hTreeView;
	HTREEITEM hItem;
	HWND hDialog;
}Tdx_TreeItem_Dlg, *PTdx_TreeItem_Dlg;

//BOOL InitNavTree();
//int GetNavTreeItemCount(PNav_Tree treeitem);

//extern Nav_Tree NavTree;  //�������������������ݴ�TcOem.xml�ļ��л�ȡ��