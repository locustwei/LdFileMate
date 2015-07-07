#pragma once
#include "atlimage.h"

 /*�Ź������죨ѹ����ͼƬ
 ��ԭͼƬ��ֳɾŸ����֣�
 ���ϡ����С�����
 ���С����ġ�����
 ���¡����С����¡�
 ����4���Ǳ��֣����ϡ����ϡ� ���¡����£����䣻
 ���С�����ˮƽ���죻
 ���С����д�ֱ���죻
 ������ˮƽ�ʹ�ֱͬʱ���졣

 ͬ����СͼƬ��
 */
typedef struct tagImageSplit{ 
	UINT nFixLeft;
	UINT nFixTop;
	UINT nFixRight;            //��0��ʼ���ұ߾ࡣ
	UINT nFixBottm;            //��0��ʼ���±߾ࡣ
}IMAGESPLIT, *LPIMAGESPLIT;

class CLdImage :public CImage
{
public:
	CLdImage(void);
	~CLdImage(void);

	IMAGESPLIT m_ImgSplit;

	BOOL DrawSplit(HDC hDestDC, const RECT& rectDest);           //�Ź����죨ѹ��������
	void ImgageTran();                                           //͸��������alphaֵ��ͼƬ��Ҫ����һ�²��ܻ���͸��Ч������
};

