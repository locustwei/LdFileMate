// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once


#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include "windows.h"
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "resource.h"

#define MM_CUSTOM WM_USER + 0xA0CD
#define MM_RUNONMAINTHREAD MM_CUSTOM + 1      //���������̷߳���Ϣ���Ա��ô������������߳̿ռ䡣wprarm: ����ָ�룻lparam������
typedef int (* RUNONPROC)(LPARAM);            //���߳����к������� 
#define MM_LOGINED MM_CUSTOM + 2


extern HINSTANCE hInstance;  //��̬��handle
extern DWORD dwViceThreadId; //���߳�ID