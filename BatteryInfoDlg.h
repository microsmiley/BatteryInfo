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

#if !defined(AFX_BATTERYINFODLG_H__EE768B2C_D747_4A2F_8191_C711CC4E966E__INCLUDED_)
#define AFX_BATTERYINFODLG_H__EE768B2C_D747_4A2F_8191_C711CC4E966E__INCLUDED_

#include "Batteries.h"
#include "afxwin.h"
#include "afxcmn.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBatteryInfoDlg : public CDialog
{
// 構築
public:
	void UpdateBatteryInformation();
	CBatteries m_cyBatteries;
	CBatteryInfoDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

	enum { IDD = IDD_BATTERYINFO_DIALOG };
	CButton	m_cbOk;
	CButton	m_cbUpdate;
	CProgressCtrl	m_pCapacity;
	CComboBox	m_cbBatteryList;
	CString	m_csManufactureName;
	CString	m_csUniqueId;
	CString	m_csDeviceName;
	CString	m_csManufactureDate;
	int		m_nSelectedBattery;
	CString	m_csSerialNumber;
	CString	m_csCurrentCapacity;
	CString	m_csFullChargedCapacity;
	CString	m_csDesignedCapacity;
	CString	m_csVoltage;
	BOOL	m_bRelativeCapacity;
	BOOL	m_bShortTerm;
	BOOL	m_bSystemBattery;
	BOOL	m_bChargeable;
	CString	m_csStatus;
	CString	m_csCycleCount;
	CString	m_csRate;
	CString	m_csChemistryCode;
	CString	m_csLowCapacity;
	CString	m_csWarnCapacity;
	CString	m_csEstimatedTime;
	CString	m_csPercent;
	CString	m_csTemperature;

	public:
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUpdate();
	afx_msg void OnSelendokCbBatterylist();

	DECLARE_MESSAGE_MAP()
protected:
	CSpinButtonCtrl m_spAutoUpdate;
	int m_iAutoUpdate;
	CEdit m_eAutoUpdate;
public:
	afx_msg void OnEnChangeEAutoupdate();
public:
	afx_msg void OnTimer(UINT nIDEvent);

protected:
	static const UINT AutoUpdateTimerId = 5783;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BATTERYINFODLG_H__EE768B2C_D747_4A2F_8191_C711CC4E966E__INCLUDED_)
