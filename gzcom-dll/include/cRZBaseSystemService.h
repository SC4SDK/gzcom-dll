/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cRZBaseSystemService.h
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

#pragma once
#include "cIGZSystemService.h"
#include "cRZUnknown.h"

/**
 * @brief A base class that handles the boilerplate for
 * implementing a GZCOM system service.
 */
class cRZBaseSystemService : public cIGZSystemService, public cRZUnknown
{
public:
	// cIGZUnknown

	bool QueryInterface(uint32_t riid, void** ppvObj) override;
	uint32_t AddRef() override;
	uint32_t Release() override;

	// cIGZSystemService

	uint32_t GetServiceID() override;
	cIGZSystemService* SetServiceID(uint32_t id) override;
	int32_t GetServicePriority() override;
	bool IsServiceRunning() override;
	cIGZSystemService* SetServiceRunning(bool running) override;
	bool OnTick(uint32_t unknown1) override;
	bool OnIdle(uint32_t unknown1) override;
	int32_t GetServiceTickPriority() override;

protected:
	cRZBaseSystemService(uint32_t serviceID, int32_t servicePriority);

	uint32_t serviceID;
	int32_t servicePriority;
	int32_t serviceTickPriority;
	bool serviceRunning;
};
