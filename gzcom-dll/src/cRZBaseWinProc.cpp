/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cRZBaseWinProc.cpp
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

#include "cRZBaseWinProc.h"

cRZBaseWinProc::cRZBaseWinProc()
{
}

bool cRZBaseWinProc::QueryInterface(uint32_t riid, void** ppvObj)
{
    if (riid == GZIID_cIGZWinProc)
    {
        *ppvObj = static_cast<cIGZWinProc*>(this);
        AddRef();

        return true;
    }
    
    return false;
}

uint32_t cRZBaseWinProc::AddRef()
{
    return cRZUnknown::AddRef();
}

uint32_t cRZBaseWinProc::Release()
{
    return cRZUnknown::Release();
}

bool cRZBaseWinProc::DoWinMsg(cIGZWin* pWin, uint32_t dwMessageID, uint32_t data1, uint32_t data2, uint32_t data3)
{
    return false;
}
