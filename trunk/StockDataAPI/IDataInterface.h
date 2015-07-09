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
	union{  //Ϊ��ʹ�÷���
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
			double      fAmount;      //�ɽ���Ԫ��
		};
	};
	
	float       fBuyp[5];     //��������(Ԫ��    
	DWORD       dwBuyv[5];    //��Ӧ�������۵�������̣��֣�
	float       fSellp[5];    //���������
	DWORD       dwSellv[5];   //��Ӧ��������۵��������
}STOCK_DATA_PK, *PSTOCK_DATA_PK;

struct IDataInterface
{
	virtual BOOL GetStockPK(_Inout_ PSTOCK_DATA_PK* pStockData, int count) = 0;                        //��ȡ��Ʊ�̿�����
	virtual float GetCurrent(STOCK_MARK nMark, LPCSTR szCode, PSTOCK_DATA_SIMPLE pSD) = 0;             //��ǰ��
	virtual float GetOpen(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;           //���̼�
	virtual float GetHigh(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;           //��߼�
	virtual float GetLow(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;            //��ͼ�
	virtual float GetClose(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;          //������
	virtual DWORD GetVolume(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;         //�ɽ���
	virtual double GetAmount(STOCK_MARK nMark, const char* szCode, PSTOCK_DATA_SIMPLE pSD) = 0;        //�ɽ���
};