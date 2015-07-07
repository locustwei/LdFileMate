#include "StdAfx.h"
#include "LdImage.h"
#include "LdGraphicFuncs.h"


CLdImage::CLdImage(void)
{
	ZeroMemory(&m_ImgSplit, sizeof(IMAGESPLIT));
}


CLdImage::~CLdImage(void)
{
}

BOOL CLdImage::DrawSplit( HDC hDestDC, const RECT& rectDest )
{
	UINT nWidth=GetWidth();
	UINT nHeight=GetHeight();

	if( ((m_ImgSplit.nFixLeft>nWidth)||(m_ImgSplit.nFixTop>nHeight)) ||           //�߽����
		((m_ImgSplit.nFixRight-m_ImgSplit.nFixLeft<=0)||(m_ImgSplit.nFixBottm-m_ImgSplit.nFixTop<=0))//���Ϊ0
		)
		return CImage::Draw(hDestDC, rectDest);

	//HDC hDc=CreateCompatibleDC(hDestDC);
	HDC hDc=hDestDC;
	if(!hDc)
		return FALSE;


	CRect crImg(0, 0, m_ImgSplit.nFixLeft, m_ImgSplit.nFixTop);                                                   //Image���Ͻ�
	CRect crDest(rectDest.left, rectDest.top, rectDest.left+crImg.Width(), rectDest.top+crImg.Height());           //Ŀ�����Ͻ�
	CLdImage::Draw(hDc, crDest, crImg);

	crImg.left=m_ImgSplit.nFixLeft;
	crImg.right=m_ImgSplit.nFixRight;                                                                             //Image���м�
	crDest.left=rectDest.left+m_ImgSplit.nFixLeft;
	crDest.right=rectDest.right-(nWidth-m_ImgSplit.nFixRight);                                                    //Ŀ������
	CLdImage::Draw(hDc, crDest, crImg);

	crImg.left=m_ImgSplit.nFixRight;
	crImg.right=nWidth;                                                                                           //Image���Ͻ�
	crDest.left=rectDest.right-crImg.Width();
	crDest.right=rectDest.right;                                                                                  //Ŀ�����Ͻ�
	CLdImage::Draw(hDc, crDest, crImg);

	crImg.top=m_ImgSplit.nFixTop;
	crImg.bottom=m_ImgSplit.nFixBottm;                                                                            //Image����
	crDest.top=rectDest.top+m_ImgSplit.nFixTop;
	crDest.bottom=rectDest.bottom-(nHeight-m_ImgSplit.nFixBottm);                                                 //Ŀ������
	CLdImage::Draw(hDc, crDest, crImg);

	crImg.top=m_ImgSplit.nFixBottm;
	crImg.bottom=nHeight;                                                                                         //Image����
	crDest.top=rectDest.bottom-crImg.Height();
	crDest.bottom=rectDest.bottom;                                                                                //Ŀ������
	CLdImage::Draw(hDc, crDest, crImg);

	crImg.left=m_ImgSplit.nFixLeft;
	crImg.right=m_ImgSplit.nFixRight;                                                                             //Imag����
	crDest.left=rectDest.left+m_ImgSplit.nFixLeft;
	crDest.right=rectDest.right-(nWidth-m_ImgSplit.nFixRight);                                                    //Ŀ������
	CLdImage::Draw(hDc, crDest, crImg);

	crImg.left=0;
	crImg.right=m_ImgSplit.nFixLeft;                                                                              //Image����
	crDest.left=rectDest.left;
	crDest.right=rectDest.left+m_ImgSplit.nFixLeft;                                                               //Ŀ������
	CLdImage::Draw(hDc, crDest, crImg);

	crImg.top=m_ImgSplit.nFixTop;
	crImg.bottom=m_ImgSplit.nFixBottm;                                                                            //Image����
	crDest.top=rectDest.top+m_ImgSplit.nFixTop;
	crDest.bottom=rectDest.bottom-(nHeight-m_ImgSplit.nFixBottm);                                                 //Ŀ������
	CLdImage::Draw(hDc, crDest, crImg);

	crImg.left=m_ImgSplit.nFixLeft;
	crImg.right=m_ImgSplit.nFixRight;                                                                             //Image����
	crDest.left=rectDest.left+m_ImgSplit.nFixLeft;
	crDest.right=rectDest.right-(nWidth-m_ImgSplit.nFixRight);                                                    //Ŀ������
	CLdImage::Draw(hDc, crDest, crImg);

	return TRUE;
}

void CLdImage::ImgageTran()
{
	PngImgTransparency(this);
}
