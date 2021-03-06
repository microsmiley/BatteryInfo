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
// YBattery.cpp: CYBattery
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BatteryInfo.h"
#include "Battery.h"

#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CBattery::CBattery()
{
	m_hBattery = NULL;
	m_ulBatTag = 0;
	m_ulEstimatedTime = 0;
	m_ulTemperature = 0;
	m_manufactureDate.Year = 2000;
	m_manufactureDate.Month = 1;
	m_manufactureDate.Day = 1;
}

CBattery::~CBattery()
{
	CloseIfOpen();
}


bool CBattery::GetBatteryInformation(BATTERY_INFORMATION &batInfo)
{
	BATTERY_QUERY_INFORMATION batQueryInfo;
	DWORD dwBytesReturned;

	batQueryInfo.BatteryTag = m_ulBatTag;
	batQueryInfo.InformationLevel = BatteryInformation;
	BOOL bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), &batInfo, sizeof(batInfo),
					&dwBytesReturned, NULL);
	TRACE(_T("error = %d\n"), GetLastError());
	return !bSucceeded;
		
}

bool CBattery::Open(const CString &csBatDevice)
{
	CloseIfOpen();
	m_hBattery = CreateFile(csBatDevice, GENERIC_READ, 
						FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if(m_hBattery == INVALID_HANDLE_VALUE)
	{
		m_hBattery = NULL;
		return false;
	}
	return Update();
}

bool CBattery::CloseIfOpen()
{
	if(m_hBattery)
	{
		CloseHandle(m_hBattery);
		m_hBattery = NULL;
		return true;
	}
	return false;
}

ULONG CBattery::GetNewTag()
{
	ULONG ulWait = 5000;
	ULONG ulTag;
	DWORD dwBytesReturned;

	BOOL bResult = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_TAG, &ulWait, sizeof(ULONG),
					&ulTag, sizeof(ULONG), &dwBytesReturned, NULL);

	if(bResult == FALSE)
	{
		m_ulBatTag = 0;
		return 0;
	}

	m_ulBatTag = ulTag;
	return ulTag;
}

//DEL ULONG CBattery::GetTemperature()
//DEL {
//DEL 	ULONG batTemp;
//DEL 	BATTERY_QUERY_INFORMATION batQueryInfo;
//DEL 	BOOL bSucceeded;
//DEL 	DWORD dwBytesReturned;
//DEL 
//DEL 	batQueryInfo.InformationLevel = BatteryTemperature;
//DEL 	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
//DEL 					&batQueryInfo, sizeof(batQueryInfo), &batTemp, sizeof(batTemp),
//DEL 					&dwBytesReturned, NULL);
//DEL 	if(bSucceeded){
//DEL 		return batTemp;
//DEL 	}else{
//DEL 		return 0;
//DEL 	}
//DEL }

bool CBattery::Update()
{
	if(GetNewTag() == 0){
		return false;
	}

	BATTERY_QUERY_INFORMATION batQueryInfo;
	DWORD dwBytesReturned;

	batQueryInfo.BatteryTag = m_ulBatTag;

	batQueryInfo.InformationLevel = BatteryManufactureName;
	QueryString(batQueryInfo, m_csManufactureName);

	batQueryInfo.InformationLevel = BatteryDeviceName;
	QueryString(batQueryInfo, m_csDeviceName);

	batQueryInfo.InformationLevel = BatterySerialNumber;
	QueryString(batQueryInfo, m_csSerialNumber);

	batQueryInfo.InformationLevel = BatteryUniqueID;
	QueryString(batQueryInfo, m_csUniqueId);

	batQueryInfo.InformationLevel = BatteryManufactureDate;
	BOOL bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), &m_manufactureDate, sizeof(m_manufactureDate),
					&dwBytesReturned, NULL);
	if(!bSucceeded)
		ZeroMemory(&m_manufactureDate, sizeof(m_manufactureDate));

	batQueryInfo.InformationLevel = BatteryEstimatedTime;
	batQueryInfo.AtRate = 0;
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), &m_ulEstimatedTime, sizeof(ULONG),
					&dwBytesReturned, NULL);

	if(!bSucceeded)
		m_ulEstimatedTime = BATTERY_UNKNOWN_TIME;

	batQueryInfo.InformationLevel = BatteryTemperature;
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), &m_ulTemperature, sizeof(ULONG),
					&dwBytesReturned, NULL);

	if(!bSucceeded)
		m_ulTemperature = 0;

	return true;

}

bool CBattery::QueryString(BATTERY_QUERY_INFORMATION& batQueryInfo, CString& csOutStr)
{
	wchar_t wszStrTemp[200];
	wszStrTemp[0] = '\0';
	BOOL bSucceeded = FALSE;
	DWORD dwBytesReturned = 0;

	ZeroMemory(wszStrTemp, sizeof(wszStrTemp));
	bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_INFORMATION,
					&batQueryInfo, sizeof(batQueryInfo), wszStrTemp, sizeof(wszStrTemp),
					&dwBytesReturned, NULL);
	if(bSucceeded)
	{
		csOutStr = CString(wszStrTemp);
	}
	else
	{
		if (csOutStr.LoadString(IDS_UNKNOWN))
			return !bSucceeded;
	}
	return !bSucceeded;
}

bool CBattery::GetBatteryStatus(BATTERY_STATUS &batStat)
{
	BATTERY_WAIT_STATUS batWaitStatus;
	DWORD dwBytesReturned;
	
	batWaitStatus.BatteryTag = m_ulBatTag;
	batWaitStatus.Timeout = 0;
	BOOL bSucceeded = DeviceIoControl(m_hBattery, IOCTL_BATTERY_QUERY_STATUS,
				&batWaitStatus, sizeof(batWaitStatus),
				&batStat, sizeof(batStat), &dwBytesReturned, NULL);

	return !bSucceeded;

}
