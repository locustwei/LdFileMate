#include "PriceComboBox.h"


CPriceComboBox::CPriceComboBox(void)
{
}


CPriceComboBox::~CPriceComboBox(void)
{
}

BOOL CPriceComboBox::OnInitWnd()
{
	CLdComboBox::OnInitWnd();
	m_ListWnd->AddString(L"��ǰ��");
	m_ListWnd->AddString(L"���ռ�");
	m_ListWnd->AddString(L"��߼�");
	m_ListWnd->AddString(L"��ͼ�");
	return TRUE;
}
