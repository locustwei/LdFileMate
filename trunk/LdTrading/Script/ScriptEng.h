#pragma once

#include "../../StockDataAPI/IDataInterface.h"
#include "../ITradInterface.h"
#include "../../PublicLib/comps/LdList.h"

extern "C"{
	#include "../../LuaLib/lua.h"
	#include "../../LuaLib/lauxlib.h"
	#include "../../LuaLib/lualib.h"
};

//�ű�ע�Ͳ��ֹؼ��֣�����
#define S_COMMENT_B "--[["  
#define S_COMMENT_E "--]]"
#define S_TRAD_NAME "[����]:"
#define	S_TRAD_MEMO "[˵��]:"

#define S_TARD_PARAM_ID "This"    //Ĭ�ϸ��ű����ӵĲ�����ͨ���˲����ű����Ի���û���������Ϣ

typedef struct _TRAD_STRCPIT
{
	LPCSTR szName;         //��ʾ��
	LPSTR szFunction;      //��̬����ĺ�����
	LPCSTR szComment;      //ע��
	int nParamCount;       //������Ŀ����
	LPSTR* szParams;       //���������б�
}TRAD_STRCPIT, *PTRAD_STRCPIT;

class CScriptEng
{
	friend BOOL CALLBACK EnumResStrategy(__in  HMODULE hModule,__in  LPCTSTR lpszType,__in  LPTSTR lpszName,__in  LONG_PTR lParam);
	friend BOOL CALLBACK EnumResLib(__in  HMODULE hModule,__in  LPCTSTR lpszType,__in  LPTSTR lpszName,__in  LONG_PTR lParam);
public:
	CScriptEng(void);
	~CScriptEng(void);

	BOOL SetDataInterface(IDataInterface* iInt);   //ȡ���ӿ�
	BOOL SetTradInterface(ITradInterface* iInt);


	BOOL RunScript(LPCSTR szScript, float* fResult);      //ִ�нű�
	BOOL RunScript(LPCSTR szScript, DWORD* dwResult);
	BOOL RunScript(LPCSTR szScript, double* fResult);
	BOOL RunScript(LPCSTR szScript, boolean* bResult);
	BOOL RunScript(LPCSTR szScript, LPCSTR* szResult);
private:
	lua_State* m_hLua;
	IDataInterface* m_IStockData;
	ITradInterface* m_IStockTrad;
	CLdList<PTRAD_STRCPIT> m_TradScripts;

	BOOL AddLib(LPCSTR szLib);   //���غ�����
	PTRAD_STRCPIT AddFunction( LPSTR szScript);  //���ز��Ժ���
	BOOL RunScript(LPCSTR szScript);
};

