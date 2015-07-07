/********************************************************************
	created:	2013/12/07
	created:	7:12:2013   23:09
	author:		����
	
	purpose:	������Toolbar�ؼ�����Panel�ϷŶ����ť���������ñ���ͼ����ťͼƬ
*********************************************************************/
#pragma once
#include "LdPanel.h"
#include "LdImage.h"
#include <Commctrl.h>
#include "..\PublicLib\comps\LdList.h"

typedef struct tagBtnBarItem{ //��ť�����ݽṹ
	UINT nImage;
	CString szCaption;
	CONTROLSTATUS csStatus;
	BOOL bVisiabled;
	CRect crRect;
	CRect crCaption;
	CString szHint;
	LPVOID lpData;
}BTNBARITEM, *LPBTNBARITEM;

// CLdBtnBar

class CLdBtnBar : public CLdPanel
{

public:
	CLdBtnBar();
	virtual ~CLdBtnBar();
public:
	CLdImage* m_ImgBackgrd;                    //����ͼ
	HIMAGELIST m_ImstItem;                  //Btnͼ�ꡣ
	DWORD m_BtnAlign;                    //Btn���з�ʽ��Ĭ��ˮƽ���󣬴�ֱ����
	DWORD m_BtnCaptionAlign;             //��ťCaption�ŵ�λ�á�Ĭ��ˮƽ���У���ֱ���¡�
	BOOL m_ShowBtnCaption;                   //�Ƿ���ʾBtn��Caption��Ĭ��True
	IItemChange* OnItemClicked;               //����Item������¼�


	LPBTNBARITEM InsertItem(LPCTSTR szCaption, UINT nImage, UINT nAffter=-1);//����BtnĬ�Ϸ������
	UINT GetItemCount();                     //����Btn����
	LPBTNBARITEM GetItem(int nIdx);
	void DeleteItem(int nIdx);              //
	void UpdateItem(int nIdx);              //�ػ�Item
	LPBTNBARITEM GetItemFrom(POINT pt);     //��ȡ������Item

	CSize GetItemSize();                     //��ȡBtn�Ĵ�С
	void SetItemSize(CSize szie);                      //����Btn�Ĵ�С
protected:
	//void SelectChange(UINT nNew);            //�ı䵱ǰѡ�е�Item����
	void DrawItem(LPBTNBARITEM pItem);       //��Btn
	void DrawItem( HDC pDc, LPBTNBARITEM pItem );
	void OnMouseMove(UINT nFlags, POINT point);
	void OnPaint();
	void OnLButtonDown(UINT nFlags, POINT point);
	void OnLButtonUp(UINT nFlags, POINT point);
	void OnSize(UINT nType, int cx, int cy);
	BOOL OnDrawBackgrd(HDC pDC);
private:
	CSize m_ItemSize;
	CLdList<LPBTNBARITEM> m_Items;
	LPBTNBARITEM m_CaptureItem;
	void InitMember();                   //��ʼ������
	UINT GetItemIndex(LPBTNBARITEM lpItem);

	void DrawBackgrd( HDC pDc );
};


