#pragma once

#include "stdafx.h"
#include "LdImage.h"
#include "LdWnd.h"


class CLdListItem: public CLdUiObject
{

protected:
	inline CLdListItem()
	{
		rcItem.SetRect(-1, -1, -1, -1);
		rcIcon.SetRect(-1, -1, -1, -1);
		rcCheckBox.SetRect(-1, -1, -1, -1);
		rcCaption.SetRect(-1, -1, -1, -1);
	
		Checked=FALSE;
		Visible=TRUE;
		pData=NULL;
		imgIcon=NULL;
		Disabled=FALSE;
	}	

public:
	LPTSTR Caption;
	BOOL Disabled;
	BOOL Checked;                        //��һ�Ҫֱ�Ӹ�ֵ�������ǵ�ѡ����ʹ��CheckItem
	BOOL Visible;
	CRect rcItem;
	CRect rcIcon;
	CRect rcCheckBox;
	CRect rcCaption;
	LPVOID pData;
	CLdImage* imgIcon;
};
