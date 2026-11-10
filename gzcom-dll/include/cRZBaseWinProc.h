/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cRZBaseWinProc.h
 *
 * Copyright (C) 2025, 2026 Nicholas Hayes
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
#include "cIGZWinProc.h"
#include "cRZUnknown.h"

class cRZBaseWinProc : public cIGZWinProc, public cRZUnknown
{
protected:
	cRZBaseWinProc();

public:
	// cIGZUnknown

	bool QueryInterface(uint32_t riid, void** ppvObj) override;
	uint32_t AddRef() override;
	uint32_t Release() override;

	// cIGZWinProc
	// DoWinMessage is left as a pure virtual function to force derived classes to implement it.
	// This is more discoverable than having a default implementation that derived classes would
	// need to remember to override.

	// This is an obsolete window procedure method that appears to be a SC3K UI porting leftover.
	// It will be called if DoWinProcMessage returns false, our implementation follows the pattern
	// used by SC4's window procedures in treating this override as function that always returns false.
	bool DoWinMsg(cIGZWin* pWin, uint32_t dwMessageID, uint32_t data1, uint32_t data2, uint32_t data3) override;
};