/************************************************************************
�ɷݲ�ѯ����
************************************************************************/
#pragma once
#include "..\..\PublicLib\hooks\WindowHook.h"

class CTDXGfcx :public CWndHook
{
public:
	CTDXGfcx(HWND hWnd);
	~CTDXGfcx(void);
private:
	HWND m_l628;         // �ʲ�ͳ����Ϣ�����:*  ����:*  �ο���ֵ:*  �ʲ�:*  ӯ��:* 
	HWND m_lst61F;       // ���й�Ʊ�б�

	BOOL GetStatisticsValue(float& ye, float& ky, float& sz, float& yk);

};

