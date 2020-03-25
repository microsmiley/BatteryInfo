/*
    Yuryu's Battery Information, displays detailed battery info.
    Copyright (C) 2008 Yuryu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#if !defined(AFX_BATTERYINFO_H__82987620_B89A_46CD_BE2B_6A9DE69D06FA__INCLUDED_)
#define AFX_BATTERYINFO_H__82987620_B89A_46CD_BE2B_6A9DE69D06FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"	


class CBatteryInfoApp : public CWinApp
{
public:
	bool IsRunningOnWin2kOrLater();
	CBatteryInfoApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BATTERYINFO_H__82987620_B89A_46CD_BE2B_6A9DE69D06FA__INCLUDED_)
