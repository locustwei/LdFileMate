// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "resource.h"
#include "ITradInterface.h"
#include "interface\TdxTrading.h"
#include "script\ScriptEng.h"
#include "..\StockDataAPI\IDataInterface.h"

extern HINSTANCE hInstance;
extern ITradInterface* TradClient;
extern CScriptEng* ScriptEng;
extern IDataInterface* DateInterface;