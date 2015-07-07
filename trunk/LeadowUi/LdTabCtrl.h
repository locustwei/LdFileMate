/********************************************************************
	created:	2013/12/07
	created:	7:12:2013   23:35
	author:		����
	
	purpose:	ҳ��ؼ���Ϊ��ʡȥ�Ի�CTabCtrl���鷳������CLdButton��CWnd���ʵ�֡�
*********************************************************************/
#pragma once
#include "LdButton.h"
#include "LdPanel.h"
#include "..\PublicLib\comps\LdList.h"

class CLdSheet : public CLdPanel
{
};

// CLdTabCtrl

class CLdTabSheet : public CLdPanel
{
public:
	CLdTabSheet();
	virtual ~CLdTabSheet();
public:
	IItemChange* OnBeforeSheetChange;              //����sheet�ı��¼���ǰ��
	IItemChange* OnAfterSheetChange;               //����sheet�ı��¼�����

	UINT AddSheet( LPCTSTR lpCaption);              //����sheet
	void SetBtnSize(CSize size);                    //���ð�ť��С
	CSize GetBtnSize();                             //��ȡ��ť��С
	int GetCurSheetId(CLdSheet** tabSheet);      //��ȡ��ǰѡ��sheet��id��tabSheetΪ����ѡ��sheet������Ҫ����NULL
	CLdButton* GetSheetBtn(int nId);                //��ȡ��ťָ��
	CLdSheet* GetSheet( int nId );                  //��ȡSheetָ��
	int SetCurSheet(int nId);                       //����ѡ�е�Sheet
protected:
//BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam,LRESULT* pResult);
	void OnSize(UINT nType, int cx, int cy); //
	CRect GetSheetRect();                            //��ȡSheet���򣨣�
private:
	int m_CurSheetId;
	CSize m_BtnSize;
	CLdList<CLdSheet*> m_Sheets;          //�Ѵ�����sheet
	CLdList<CLdButton*> m_Btns;           //�Ѵ�����btn

	void ChangeSheet(int newId);                      //�ı�ѡ�е�sheet
	void SheetBtnClick( CLdButton* Sender );
private:
	INotifyEvent* m_SheetBtnClickHandler;   //�ຯ��ָ��

};


