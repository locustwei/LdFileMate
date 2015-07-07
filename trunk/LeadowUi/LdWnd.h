#pragma once

#include "stdafx.h"

#define MM_LDWND_MESSAGE WM_USER + 0x34
#define MM_ANCHORS MM_LDWND_MESSAGE + 1  //����sizing���������Ӵ���
#define MM_NOTIFY MM_LDWND_MESSAGE + 2   //WM_NOTIFY���͵��Ӵ���

class CLdUiObject
{
public:
	static HINSTANCE hInstance;
};

/************************************************************************/
/* һ����¼��ص��������塣��Button�����ã���
Sender��Ϊ�¼������߱���*/
/************************************************************************/
struct INotifyEvent
{
	virtual void OnNotify(CLdUiObject* Sender) = 0;
};

struct IDrawEvent
{
	virtual BOOL OnDraw(CLdUiObject* Sender, HDC pDc, RECT rect) = 0;
};

struct IItemChange
{
	virtual BOOL OnItemChang(CLdUiObject* Sender, int nNew) = 0;
};

struct IMouseEvent
{
	virtual void OnMouseEvent(CLdUiObject* Sender, POINT pt) = 0;
};

struct IItemMouseEvent
{
	virtual void OnItemMouseEvent(CLdUiObject* Sender, CLdUiObject* item, POINT pt) = 0;
};
/************************************************************************/
/* �ؼ�״̬ö�١�
CS_NORMAL��������CS_MOUSEMOVE����꾭����CS_MOUSEDOWN����갴�¡�CS_DISABLEED�������á�CS_SELECED��ѡ�У���ȡ���㣩��*/
/************************************************************************/
typedef enum CONTROLSTATUS{CS_NORMAL, CS_MOUSEMOVE, CS_MOUSEDOWN, CS_DISABLEED, CS_SELECTED};

/************************************************************************/
/* ���ڱ�������ѡ����Ŀ                                                 */
/************************************************************************/
typedef enum LDFORMTITLEBOX{
	LFT_NONE = 0,                                          //ɶҲ����
	LFT_CPTION = 1,                                        //��ͷ�ַ���
	LFT_MENUBOX =  2,                                      //���ڲ˵�
	LFT_MINBOX = 4,                                        //��С����ť
	LFT_MAXBOX = 8,                                        //��󻯰�ť
	LFT_CLOSEBOX = 16,                                     //�رհ�ť
	LFT_SIZEBOX =32,                                       //�ı��С�߿�
	LFT_ICON = 64,                                         //����ͼ��
	LFT_DEFAULT = LFT_ICON|LFT_CPTION|LFT_CLOSEBOX         //���ڱ���Ĭ����ʽ
};

/************************************************************************/
/* �ؼ���Ը�Wnd��������ʽ
�������ڴ�С�����ı�ʱ���ؼ�������һ�߷����ı䡣�����*/
/************************************************************************/
typedef enum ANCHORS{
	akLeft = 1,
	akTop = 2,
	akRight = 4,
	akBottom = 8
};

/************************************************************************/
/* �ַ�����ؼ��ŷŷ�ʽ�� ��ˮƽ�ʹ�ֱ��������ˮƽ�ʹ�ֱ����������ʹ��*/
/************************************************************************/
typedef enum ALIGNMENT{
	taLeft=1,
	taRight=2,
	taHCenter=4,

	taTop=16,
	taBottom=32,
	taVCenter=64
};

class CLdWnd: public CLdUiObject
{
	friend LRESULT CALLBACK LdWindowProc(
		_In_ HWND   hwnd,
		_In_ UINT   uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
		);
public:
	CLdWnd(void);
	virtual ~CLdWnd(void);
	virtual void Create( HWND pParent);
	virtual void AttchWindow(HWND hwnd);
	void Invalidate();
	void ShowWindow(int nCmdShow);
	void MoveWindow(RECT rc, BOOL update = FALSE);

	HWND m_hWnd;
	PVOID m_Data;
	int m_Tag;
	BYTE m_Anchors;
protected:
	WNDPROC m_WndProc;
	LPCTSTR m_ClassName;
	DWORD m_ExStyle;
	DWORD m_Style;
	virtual LRESULT WindowProc(HWND   hwnd, UINT   uMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitWnd();
private:
	void OnParentSizing(UINT nSide, int nx, int ny);
	void OnSizing( UINT nSide, LPRECT lpRect );
	void ResizeChilds(UINT nSide, int nx, int ny);
};

