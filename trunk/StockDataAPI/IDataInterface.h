/*!
 *
 * \author asa
 *  ��Ʊ���ݽӿڡ�
 * 
 */
#pragma once

#pragma warning(disable : 4091)

typedef enum STOCK_MARK  //���б��
{
	MARK_SZ = 0,   //����
	MARK_SH = 1    //����
};

typedef struct _STOCK_DATA_SIMPLE
{
	STOCK_MARK  mark;        //�г�
	LPCSTR      szCode;
	float       fClose;      //�����̼�
	float       fOpen;       //���̼�
	float       fHigh;
	float       fLow;
	float       fCurrent;     //�ּ�
	DWORD       dwVolume;     //�ɽ���(��)
	float       fAmount;      //�ɽ���Ԫ��
}STOCK_DATA_SIMPLE, *PSTOCK_DATA_SIMPLE;

typedef struct _STOCK_DATA_PK   // ��Ʊ�̿�����
{
	union{
		STOCK_DATA_SIMPLE smple;
		struct{
			STOCK_MARK  mark;        //�г�
			LPCSTR      szCode;
			float       fClose;      //�����̼�
			float       fOpen;       //���̼�
			float       fHigh;
			float       fLow;
			float       fCurrent;     //�ּ�
			DWORD       dwVolume;     //�ɽ���(��)
			float       fAmount;      //�ɽ���Ԫ��
		};
	};

	float       fBuyp[5];     //��������(Ԫ��    
	DWORD       dwBuyv[5];    //��Ӧ�������۵�������̣��֣�
	float       fSellp[5];    //���������
	DWORD       dwSellv[5];   //��Ӧ��������۵��������

// #define mark smple.mark
// #define szCode smple.szCode
// #define fClose smple.fClose
// #define fOpen smple.fOpen
// #define fHigh smple.fHigh
// #define fLow smple.fLow
// #define fCurrent smple.fCurrent
// #define dwVolume smple.dwVolume
// #define fAmount smple.fAmount
}STOCK_DATA_PK, *PSTOCK_DATA_PK;

struct IDataInterface
{
	//��������
	virtual BOOL GetStockPK(_Inout_ PSTOCK_DATA_PK* pStockData, int count) = 0;                        //��ȡ��Ʊ�̿�����
	virtual float GetCurrent(STOCK_MARK nMark, LPCSTR szCode, PSTOCK_DATA_SIMPLE pSD) = 0;             //��ǰ��
	virtual float GetOpen(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;           //���̼�
	virtual float GetHigh(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;           //��߼�
	virtual float GetLow(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;            //��ͼ�
	virtual float GetClose(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;          //������
	virtual DWORD GetVolume(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;         //�ɽ���
	virtual double GetAmount(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;        //�ɽ���
	//��ʷ����
	virtual BOOL GetStockDay(_Out_ PSTOCK_DATA_SIMPLE* pStockData, STOCK_MARK nMark, const char* szCode, int count, int y, int m, int d) = 0;     //��ȡ��Ʊ������
	virtual BOOL GetStockWeek(_Out_ PSTOCK_DATA_SIMPLE* pStockData, STOCK_MARK nMark, const char* szCode, int count, int y, int w) = 0;           //��ȡ��Ʊ������
	virtual BOOL GetStockMonth(_Out_ PSTOCK_DATA_SIMPLE* pStockData, STOCK_MARK nMark, const char* szCode, int count, int y, int m) = 0;           //��ȡ��Ʊ������
	virtual BOOL GetStockYear(_Out_ PSTOCK_DATA_SIMPLE* pStockData, STOCK_MARK nMark, const char* szCode, int count, int y) = 0;           //��ȡ��Ʊ������
};

/*
char text[100];
time_t now = time(NULL);
struct tm *t = localtime(&now);


strftime(text, sizeof(text)-1, "%d %m %Y %H:%M", t);
printf("Current Date: %s", text);
*/