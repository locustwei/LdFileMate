#pragma once

#include "LdImage.h"


//************************************
// Qualifier:����CImage��͸������͸���ȵ�ͼƬ����ô˷�������
// Parameter: CImage * image
//************************************
void PngImgTransparency(CLdImage* image);
//************************************
// Qualifier: ˮƽ����ƽ���ָ�ͼƬ��
// Parameter: CImage * image ԭͼƬ
// Parameter: int nCount  Ҫ�ֳɶ��ٸ�
// Parameter: CImage * * result ���շָ����ͼƬ���飨Ҫ���ȷ�����ڴ�ռ䣩
// return ���سɹ����
//************************************
BOOL HSplitImg(CLdImage* image, int nCount, CLdImage** result);

void DrawCtrlBackgnd(HDC pDc, RECT rect, CLdImage* img);
