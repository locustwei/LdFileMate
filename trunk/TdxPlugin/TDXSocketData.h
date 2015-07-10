/*!
 * Socket ͨѶ���ݶ���
 *ͨ������Ҷ�̬�������س���ʹ��Socket���н��̼�ͨ�š�
 * ���ļ�����������ݽṹ
 */
#pragma once

#include <Windows.h>
#include <malloc.h>
#include "..\StockDataAPI\IDataInterface.h"

#define TDX_SOCKET_PORT 0x3421

enum TDX_TRAD_FUN
{
	TF_REGISTER,        //ע�ᣨ���Ӻ�ȷ����ݣ�
	TF_STOCKBY,         //��Ʊ����
	TF_STOCKBYED,       //��Ʊ���뷵��
	TF_STOCKSEL,        //��Ʊ����
	TF_STOCKSELED       //��������
};

typedef struct _TDX_SOCKET_DATA
{
	TDX_TRAD_FUN ID;
	WORD nLen;
	unsigned char data[0];
}TDX_SOCKET_DATA, *PTDX_SOCKET_DATA;

inline PTDX_SOCKET_DATA MakeStockData(LPVOID p, TDX_TRAD_FUN id, _Inout_ int& nSize)
{
	int nLen = sizeof(TDX_SOCKET_DATA)+nSize;
	PTDX_SOCKET_DATA result = (PTDX_SOCKET_DATA)malloc(nLen);
	ZeroMemory(result, nLen);
	result->ID = id;
	result->nLen = nSize;
	if(p)
		CopyMemory(result->data, p, nSize);
	nSize = nLen;
	return result;
};

typedef struct _S_TDX_STOCK_BY
{
	STOCK_MARK mark;
	char Code[7];
	float fPrice;
	DWORD dwVolume;
}S_TDX_STOCK_BY, *PS_TDX_STOCK_BY;