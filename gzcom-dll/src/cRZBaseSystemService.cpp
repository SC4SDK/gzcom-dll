/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 * 
 * cRZBaseSystemService.cpp
 * 
 * Copyright (C) 2024, 2026 Nicholas Hayes
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, under
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */

#include "cRZBaseSystemService.h"

cRZBaseSystemService::cRZBaseSystemService(uint32_t serviceID, int32_t servicePriority)
	: cRZUnknown(),
	  serviceID(serviceID),
	  servicePriority(servicePriority),
	  serviceTickPriority(servicePriority),
	  serviceRunning(false)
{
}

bool cRZBaseSystemService::QueryInterface(uint32_t riid, void** ppvObj)
{
	if (riid == GZIID_cIGZSystemService)
	{
		*ppvObj = static_cast<cIGZSystemService*>(this);
		AddRef();

		return true;
	}
	
	return cRZUnknown::QueryInterface(riid, ppvObj);
}

uint32_t cRZBaseSystemService::AddRef()
{
	return cRZUnknown::AddRef();
}

uint32_t cRZBaseSystemService::Release()
{
	return cRZUnknown::Release();
}

uint32_t cRZBaseSystemService::GetServiceID()
{
	return serviceID;
}

cIGZSystemService* cRZBaseSystemService::SetServiceID(uint32_t id)
{
	serviceID = id;
	return this;
}

int32_t cRZBaseSystemService::GetServicePriority()
{
	return servicePriority;
}

bool cRZBaseSystemService::IsServiceRunning()
{
	return serviceRunning;
}

cIGZSystemService* cRZBaseSystemService::SetServiceRunning(bool running)
{
	serviceRunning = running;
	return this;
}

bool cRZBaseSystemService::OnTick(uint32_t unknown1)
{
	return true;
}

bool cRZBaseSystemService::OnIdle(uint32_t unknown1)
{
	return true;
}

int32_t cRZBaseSystemService::GetServiceTickPriority()
{
	return serviceTickPriority;
}
