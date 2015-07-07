/********************************************************************
	created:	2014/01/08
	author:		����
	
	purpose:	Virtual ListCtrl��������ListView�ؼ���ʹ�ÿؼ���ҪInsert��or Add��
	            �κ����ݡ�ֻ��ҪSetItemCount��Ex�����߿ؼ������ж����м��ɡ�����
				����ʾ�������ݶ��������ˢ�����ѣ���ȻҲ�����鷳����ÿ��Draw����Ҫ
				����OnBeforeItemDraw���CListCtrlItem��Ϣ��
*********************************************************************/
#pragma once
#include "LdListItem.h"
#include "LdWnd.h"
#include <Commctrl.h>
#include "..\PublicLib\comps\LdList.h"

class CListCtrlItem: public CLdListItem
{
public:
	class CSubItem
	{
	public:
		CString Caption;
		CRect rcItem;
	};
public:
	DWORD dwId;
	CLdList<CSubItem> SubItems;
private:
};

// CLdListView ��ͼ

class CLdListCtrl : public CLdWnd
{

public:
	CLdListCtrl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLdListCtrl();
	virtual void Create(HWND pParent);
public:
	BOOL m_ShowIcon;                   //��ͼ��
	BOOL m_MuiltSelect;                //�Ƿ��ѡ(Ĭ��true)
	int m_nFixLeftPix;                 //��߿ռ������ؿ�ʼ����Ĭ��2���أ���
	BOOL m_DrawItemLine;               //�Ƿ�Item��ķָ�д
	CSize m_IconSize;                  //ͼ���С��Ĭ��16*16��

	IDrawEvent* OnBeforeItemDraw;          //����ItemDraw�¼�
	IDrawEvent* OnAfterItemDraw;           //	
	IItemMouseEvent* OnWndMouseMove;       //��������ƶ��¼���item����Ϊ�գ�
	INotifyEvent* OnEnter;          //�����������¼�
	INotifyEvent* OnLeave;          //��������뿪�¼�
	IItemMouseEvent* OnClick;          //�������item����Ϊ�գ�
	IItemMouseEvent* OnItemChecked;    //Item��CheckBox����¼�

	BOOL IsCheckBoxesVisible();
	void GetCheckBoxRect( CRect* crBound, CRect& crCheck );
	int GetColumnCount();
	int InsertColumn(int nCol, LPCTSTR szHead, int nFormat, int nWidth=-1, int nSubItem=-1);
protected:
	virtual BOOL OnChildNotify(WPARAM, LPARAM, LRESULT*);
	BOOL CustomDrawItem(LPNMLVCUSTOMDRAW nmcd, LRESULT* result);
	void OnSize(UINT nType, int cx, int cy);
private:
	CListCtrlItem* m_drawItem;                    //�洢��ǰҪ��Item����Ϣ��OnBeforeItemDraw�ص���
	HIMAGELIST m_ImageList;                      //���List���ڸı�ItemHeight
	void GetDispInfo( NMLVDISPINFO* plvdi );
	int OdFinditem(LPNMLVFINDITEM pFindInfo);

	void DoDrawItem( DWORD dwItemId, HDC pDc, RECT cr );

	virtual LRESULT WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};


