#pragma once

#include "../../StockDataAPI/IDataInterface.h"
#include "../ITradInterface.h"
#include "../../PublicLib/comps/LdList.h"

extern "C"{
	#include "../../LuaLib/lua.h"
	#include "../../LuaLib/lauxlib.h"
	#include "../../LuaLib/lualib.h"
};

#define S_COMMENT_B "--[["
#define S_COMMENT_E "--]]"

#define S_TRAD_NAME "[����]:"
#define	S_TRAD_MEMO "[˵��]:"
#define	S_TRAD_PARAM "[����"

typedef struct _TRAD_STRCPIT_PARAM
{

};

typedef struct _TRAD_STRCPIT
{
	LPCSTR szName;
	LPSTR szFunction;
	LPCSTR szComment;
	int nParamCount;
	LPSTR* szParams;
}TRAD_STRCPIT, *PTRAD_STRCPIT;

class CScriptEng
{
public:
	CScriptEng(void);
	~CScriptEng(void);

	BOOL SetDataInterface(IDataInterface* iInt);
	BOOL SetTradInterface(ITradInterface* iInt);

	BOOL LoadScriptLib(LPCSTR szLib);   //���غ�����
	PTRAD_STRCPIT LoadScriptTrad( LPSTR szScript);  //���ؽ��׺���

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

	BOOL RunScript(LPCSTR szScript);
};

