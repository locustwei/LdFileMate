// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once


#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include "windows.h"
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <Windowsx.h>
#include "resource.h"

//#define interface struct
#define GETMEM(dwSize) VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE)
#define FREEMEM(lp) VirtualFree(lp, 0, MEM_RESET)
#define FREEMEM_NIL(lp) (FREEMEM(*lp), *lp=NULL)
#define NULL_STRING L""
