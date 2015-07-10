/*!
 * Socket 通讯数据定义
 *通达信外挂动态库与主控程序使用Socket进行进程间通信。
 * 此文件定义相关数据结构
 */
#pragma once

#include <Windows.h>
#include <malloc.h>

#define TDX_SOCKET_PORT 0x3421

enum TDX_TRAD_FUN
{
	TF_REGISTER,        //注册（连接后确认身份）
	TF_STOCKBY,         //股票买入
	TF_STOCKBYED,       //股票买入返回
	TF_STOCKSEL,        //股票卖出
	TF_STOCKSELED       //卖出返回
};

typedef struct _TDX_SOCKET_DATA
{
	TDX_TRAD_FUN ID;
	WORD nLen;
	unsigned char data[0];
}TDX_SOCKET_DATA, *PTDX_SOCKET_DATA;

inline PTDX_SOCKET_DATA MakeStockData(LPVOID p, int n, TDX_TRAD_FUN id, int& nSize)
{
	nSize = sizeof(TDX_SOCKET_DATA)+n;
	PTDX_SOCKET_DATA result = (PTDX_SOCKET_DATA)malloc(nSize);
	ZeroMemory(result, nSize);
	result->ID = id;
	result->nLen = n;
	CopyMemory(result->data, p, n);
	return result;
};

typedef struct _S_TDX_STOCK_BY
{
	STOCK_MARK mark;
	char Code[7];
	float fPrice;
	DWORD dwVolume;
}S_TDX_STOCK_BY, *PS_TDX_STOCK_BY;