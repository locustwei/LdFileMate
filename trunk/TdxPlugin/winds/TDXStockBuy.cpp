/************************************************************************/
/* ��Ʊ���봰��
*/
/************************************************************************/
#include "TDXStockBuy.h"
#include <stdio.h>
#include "..\..\PublicLib\Utils_Wnd.h"

CTDXStockBuy::CTDXStockBuy(HWND hWnd):CWndHook(hWnd)
{
	m_Inited = FALSE;
	m_edCode   = GetDlgItem(hWnd, 0x2EE5);     //��Ʊ���루Edit��
	m_edValue  = GetDlgItem(hWnd, 0x2EE6);	   //����۸�Edit��
	m_edCount  = GetDlgItem(hWnd, 0x2EE7);     //����������Edit��
	m_btnOk    = GetDlgItem(hWnd, 0x07DA);     //�����µ���Button��
	m_lbJe     = GetDlgItem(hWnd, 0x2EFC);     //���ý�Static��
	m_lbZdsl   = GetDlgItem(hWnd, 0x07E6); 	   //������������Static��
	m_lstGp    = GetDlgItem(hWnd, 0x0810); 	   //���й�ƱList��SysListView32��
	m_cbBjfs   = GetDlgItem(hWnd, 0x046D);     //���۷�ʽ��ComboBox��
	m_btnAll   = GetDlgItem(hWnd, 0x05D7); 	   //ȫ����Button��
}


CTDXStockBuy::~CTDXStockBuy(void)
{
}

LRESULT CTDXStockBuy::WndPROC( HWND hwnd, UINT nCode,WPARAM wparam,LPARAM lparam )
{
	LRESULT result = CWndHook::WndPROC(hwnd, nCode, wparam, lparam);
	switch(nCode){
	case WM_SHOWWINDOW:

		m_Inited = TRUE;
		break;
	}
	return result;
}

BOOL CTDXStockBuy::DoBy( STOCK_MARK mark, LPCSTR szCode, float fPrice, DWORD dwVolume )
{
	while(!IsWindowVisible(m_hWnd))
		HandleMessssage(m_hWnd);
	while(GetFocus()!=m_edCode)
		HandleMessssage(m_hWnd);
	while(GetWindowTextLength(m_edCode)>0) //�������������Ķ������ȴ�ִ��
		HandleMessssage(m_hWnd);

	BOOL result = FALSE;
	SetWindowTextA(m_edCode, szCode);
	char szPrice[10] = {0};
	sprintf_s(szPrice, "%.2f", fPrice);
	SetWindowTextA(m_edValue, szPrice);
	sprintf_s(szPrice, "%d", dwVolume);
	SetWindowTextA(m_edCount, szPrice);
	return result;
}
