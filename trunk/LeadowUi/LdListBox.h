#pragma once
#include "LdImage.h"
#include "LdWnd.h"
#include "LdListItem.h"
#include "..\PublicLib\comps\LdList.h"

class CLdListBoxItem: public CLdListItem
{
};
// CLdListBox

class CLdListBox : public CLdWnd
{
public:
	CLdListBox();
	virtual ~CLdListBox();

	CLdListBoxItem* AddString(LPCTSTR lpszItem);                       //�滻CListBox����
	CLdListBoxItem* InsertString(int nIndex, LPCTSTR lpszItem);         
	CLdListBoxItem* InsertItem(int nIndex=-1);                                         //�����Ŀ(nIndex=-1Ϊappend��
	int InsertItem(CLdListBoxItem* pItem, int nIndex);                       
	CLdListBoxItem* GetItem(int nIdx);                               
	int DeleteString(UINT nIndex);                               
	void CheckItem(UINT nIndex, BOOL bCheck);                    //��ѡItem
	void CheckItem(CLdListBoxItem* item, BOOL bCheck);
	int GetCheckedItems(CLdList<CLdListBoxItem*>& items);                         //��ȡ�ѹ�ѡ����Ŀ���顣���ظ�����Item Append��items��
	int GetCount();
	int GetCurSel();
	int GetItemHeight( int nidx );

	BOOL m_ShowIcon;                  //��ͼ��
	BOOL m_ShowCheckBox;              //��ѡ��򣬵���ѡʱΪcheckbox�� ��ѡʱΪradiobox
	BOOL m_MuiltSelect;               //�Ƿ��ѡ(Ĭ��true)
	int m_nFixLeftPix;                 //��߿ռ������ؿ�ʼ����Ĭ��2���أ���
	BOOL m_DrawItemLine;               //�Ƿ�Item��ķָ�д
	BOOL m_IsComboBoxList;             //�Ƿ�ؼ�����ΪComboBox������ListBox��������ǳ�Mouse�¼�����Щ��ͬ��

	IDrawEvent* OnBeforeItemDraw;          //����ItemDraw�¼�
	IDrawEvent* OnAfterItemDraw;           //	
	IItemMouseEvent* OnWndMouseMove;       //��������ƶ��¼���item����Ϊ�գ�
	INotifyEvent* OnEnter;          //�����������¼�
	INotifyEvent* OnLeave;          //��������뿪�¼�
	IItemMouseEvent* OnClick;          //�������item����Ϊ�գ�
	IItemMouseEvent* OnItemChecked;    //Item��CheckBox����¼�

	UINT ItemFromPoint(CPoint pt);
	void SetItemHeight( int nidx, int nheight );
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	void DrawItemCaption(HDC pDc, CLdListBoxItem* item, UINT itemAction, UINT itemState);

	BOOL OnEraseBkgnd(HDC pDC);
	void OnSize(UINT nType, int cx, int cy);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnDestroy();
private:
	CLdListBoxItem* m_MouseMoveItem;
	CLdListBoxItem* m_MouseDownItem;

	void InitMember();
	void DoDrawItem( HDC pDc, CLdListBoxItem* item, UINT itemAction, UINT itemState );
	CLdImage* GetItemImage( CLdListBoxItem* item );
public:
	CLdImage* ImgBackgrdNoneItem;
	CLdImage* ImgBackgrd;
	CLdImage* ImgItemNormal;
	CLdImage* ImgItemMouseDown;
	CLdImage* ImgItemMouseOver;

};


