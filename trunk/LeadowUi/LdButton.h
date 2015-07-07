/********************************************************************
	created:	2013/12/07
	created:	7:12:2013   23:21
	author:		����
	
	purpose:	֧��4̬ͼƬ��ť��
*********************************************************************/
#pragma once

#include "LdImage.h"
#include "LdWnd.h"

// CLdButton

class CLdButton : public CLdWnd
{

public:
	CLdButton();
	virtual ~CLdButton();
	BOOL PtInThis(POINT pt, BOOL bScreen=FALSE);     //�ж�pt�Ƿ���button�������ڡ�bScreenָʾpt�Ƿ���Ļ����
	BOOL EnableWindow(BOOL bEnable = TRUE);

	INotifyEvent* OnClick;          //����Click�¼�
	INotifyEvent* OnEnter;          //�����������¼�
	INotifyEvent* OnLeave;          //��������뿪�¼�
	//MOUSEEVENT OnMouseMove;
	IDrawEvent* OnBeforeDraw;          //����ť֮ǰ
	IDrawEvent* OnAfterDraw;           //����ť���

	//CLdImage* m_BtnImags[CS_DISABLEED+1];    //��ť4̬ͼƬ���飨��CONTROLSTATUS��
	BOOL m_Selected;                       //ʹ��ť����ѡ��״̬����CS_SELECED��

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void ChangStatus(CONTROLSTATUS newStatus);           //��ť״̬�����ı䣨CONTROLSTATUS�任�������ػ�
	BOOL DoDrawControl( HDC hDc, CRect rect );          //����ť����
private:
	CONTROLSTATUS m_CurStatus;                           //��ǰ�İ�ť״̬

	void DefaultDraw(LPDRAWITEMSTRUCT lpDrawItemStruct); //ϵͳĬ�ϻ�Button��û��ͼƬʱִ�С�
	void OnLButtonDown(UINT x, UINT y);   
	void OnLButtonUp(UINT x, UINT y);

	CLdImage* GetCurstatusImage();                       //��֮ǰ��ȡ���õ�ͼƬ��

	void OnMouseMove(UINT x, UINT y);
	
	void DoClick();                           //�����¼�
	BOOL DoBeforeDraw(HDC pDc, CRect rect);
	void DoAfterDraw(HDC pDc, CRect rect);
	void DoEnter();
	void DoLeave();

public:
	CLdImage* ImgNormal;
	CLdImage* ImgDown;
	CLdImage* ImgEnter;
	CLdImage* ImgDisable;
	//static void InitStaticImages();

};

