#include "ConComboBox.h"


CConComboBox::CConComboBox(void)
{
}


CConComboBox::~CConComboBox(void)
{
}

BOOL CConComboBox::OnInitWnd()
{
	CLdComboBox::OnInitWnd();
	m_ListWnd->AddString(L"����");
	m_ListWnd->AddString(L"�µ�");
	ComboBox_SetCurSel(m_hWnd, 0);
	return TRUE;
}
