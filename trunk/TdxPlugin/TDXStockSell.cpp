#include "TDXStockSell.h"


CTDXStockSell::CTDXStockSell(HWND hWnd):CWndHook(hWnd)
{
	m_edCode   = GetDlgItem(hWnd, 0x2EE5);     //��Ʊ���루Edit��
	m_edValue  = GetDlgItem(hWnd, 0x2EE6);	   //�����۸�Edit��
	m_edCount  = GetDlgItem(hWnd, 0x2EE7);     //����������Edit��
	m_btnOk    = GetDlgItem(hWnd, 0x07DA);     //�����µ���Button��
	m_lbJe     = GetDlgItem(hWnd, 0x2EFC);     //���ý�Static��
	m_lbZdsl   = GetDlgItem(hWnd, 0x0811); 	   //������������Static��
	m_lstGp    = GetDlgItem(hWnd, 0x0810); 	   //���й�ƱList��SysListView32��
	m_cbBjfs   = GetDlgItem(hWnd, 0x046D);     //���۷�ʽ��ComboBox��
	m_btnAll   = GetDlgItem(hWnd, 0x05D7); 	   //ȫ����Button��
}


CTDXStockSell::~CTDXStockSell(void)
{
}

LRESULT CTDXStockSell::WndPROC( HWND hwnd, UINT nCode,WPARAM wparam,LPARAM lparam )
{
	return CWndHook::WndPROC(hwnd, nCode, wparam, lparam);
}

BOOL CTDXStockSell::DoSell( LPCSTR szCode, float fPrice )
{
	return FALSE;
}
