#include "..\StdAfx.h"
#include "TdxTrading.h"

class CTdxListenner: public ISocketListener
{
public:
	CTdxTrading* m_Trading;

	virtual void OnConnected(PLD_CLIENT_SOCKET)
	{
		
	}

	virtual void OnRecv(PLD_CLIENT_SOCKET pSocket)
	{
		if(pSocket->nRecvSize==0 || pSocket->lpRecvedBuffer==NULL)
			return;

		PTDX_SOCKET_DATA pData = (PTDX_SOCKET_DATA)pSocket->lpRecvedBuffer;
		switch(pData->ID){
		case TF_REGISTER:
			pSocket->tag = 1;  //��֤�ɹ�todo
			m_Trading->m_bAvailable = TRUE;
			break;
		case TF_STOCKBY:
		case TF_STOCKBYED:
			SetEvent(m_Trading->m_hEvent);
			break;
		case TF_STOCKSEL:
			break;
		case TF_STOCKSELED:
			SetEvent(m_Trading->m_hEvent);
			break;
		}
	}

	virtual void OnClosed(PLD_CLIENT_SOCKET)
	{
		
	}

	virtual void OnAccept(PLD_CLIENT_SOCKET pSocket)
	{
		pSocket->tag = 0;  //�ȴ���֤
	}

	virtual void OnError(PLD_CLIENT_SOCKET, int)
	{
		
	}

};

CTdxTrading::CTdxTrading(void)
{
	m_bAvailable = FALSE;

	m_Socket = new CLdSocket();
	m_Listenner = new CTdxListenner();
	m_Socket->SetListener(m_Listenner);

	//���ڵȴ�Socket��Ӧ
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("CTdxTradingEvent")); 

	ConnectTdx();
}


CTdxTrading::~CTdxTrading(void)
{
	if(m_Socket)
		delete m_Socket;
	if(m_Listenner)
		delete m_Listenner;
	if(m_hEvent)
		CloseHandle(m_hEvent);
}

BOOL CTdxTrading::StockBy( STOCK_MARK mark, LPCSTR szCode, float fPrice, DWORD dwVolume )
{
	if(!IsAvailable())
		return FALSE;
	
	BOOL result = FALSE;
	int nSize = 0;
	S_TDX_STOCK_BY stb = {mark, *szCode, fPrice, dwVolume};

	PTDX_SOCKET_DATA pData = MakeStockData(&stb, sizeof(stb), TF_STOCKBY, nSize);

	PLD_CLIENT_SOCKET pSocket = NULL;
	if(m_Socket->GetStatus()==SS_LISTENING && m_Socket->GetClientHead()!=NULL){  //��Ϊ�����
		pSocket = m_Socket->GetClientHead();
	}else if(m_Socket->GetStatus()==SS_CONNECTED)     //��Ϊ�ͻ���
		pSocket = m_Socket;

	result = SendStockDataWait(pSocket, pData, nSize);
	free(pData);

	if(result){
		PTDX_SOCKET_DATA pRet = (PTDX_SOCKET_DATA)pSocket->lpRecvedBuffer;
		result = pRet->data[0];
	}
	return result;
}

BOOL CTdxTrading::StockSell( STOCK_MARK mark, LPCSTR szCode, float fPrice, DWORD dwVolume )
{
	if(!IsAvailable())
		return FALSE;

	BOOL result = FALSE;
	int nSize = 0;
	S_TDX_STOCK_BY stb = {mark, *szCode, fPrice, dwVolume};

	PTDX_SOCKET_DATA pData = MakeStockData(&stb, sizeof(stb), TF_STOCKSEL, nSize);


	PLD_CLIENT_SOCKET pSocket = NULL;
	if(m_Socket->GetStatus()==SS_LISTENING && m_Socket->GetClientHead()!=NULL){  //��Ϊ�����
		pSocket = m_Socket->GetClientHead();
	}else if(m_Socket->GetStatus()==SS_CONNECTED)     //��Ϊ�ͻ���
		pSocket = m_Socket;

	result = SendStockDataWait(pSocket, pData, nSize);
	free(pData);

	if(result){
		PTDX_SOCKET_DATA pRet = (PTDX_SOCKET_DATA)pSocket->lpRecvedBuffer;
		result = pRet->data[0];
	}

	return result;
}

BOOL CTdxTrading::IsAvailable()
{
	return m_bAvailable;
}

//���Ƴ����뽻�׳���˭������˭Listen�˿�
void CTdxTrading::ConnectTdx()
{
	int i=0;
	do{ //����3������TDX���������
		if(m_Socket->ConnectTo("127.0.0.1", TDX_SOCKET_PORT)){
			m_bAvailable = TRUE;
			return;
		}
	}while(i++<3);

	if(m_Socket->GetStatus()==SS_NONE){ //����ʧ��
		//����������Ϊ�ǽ������û�����������Լ���Ϊ����״̬�ȴ����ӡ�
		m_Socket->Listen(TDX_SOCKET_PORT);
	}
}

BOOL CTdxTrading::SendStockDataWait(PLD_CLIENT_SOCKET pSocket, PTDX_SOCKET_DATA pData, int nSize)
{
	BOOL result = FALSE;

	if(m_Socket->Send((char*)pData, nSize, pSocket)==nSize){
		result = WaitReturn(10000);
	}

	return result;
}

//�ȴ�ִ�н������
BOOL CTdxTrading::WaitReturn(DWORD msecond)
{
	if(msecond<=0)
		msecond = INFINITE;
	return WaitForSingleObject(m_hEvent, msecond) == WAIT_OBJECT_0;
}
