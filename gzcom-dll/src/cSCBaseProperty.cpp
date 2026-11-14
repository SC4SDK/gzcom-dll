/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cSCBaseProperty.cpp
 *
 * Copyright (C) 2023, 2025, 2026 Nicholas Hayes
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

#include "cSCBaseProperty.h"
#include "cIGZIStream.h"
#include "cIGZOStream.h"
#include "cISC4DBSegmentIStream.h"
#include "cISC4DBSegmentOStream.h"
#include <utility>

cSCBaseProperty::cSCBaseProperty()
	: propertyID(0), propertyValue()
{
}

cSCBaseProperty::cSCBaseProperty(uint32_t propertyID)
	: propertyID(propertyID), propertyValue()
{
}

cSCBaseProperty::cSCBaseProperty(uint32_t propertyID, uint32_t value)
	: propertyID(propertyID), propertyValue(value)
{
}

cSCBaseProperty::cSCBaseProperty(uint32_t propertyID, int32_t value)
	: propertyID(propertyID), propertyValue(value)
{
}

cSCBaseProperty::cSCBaseProperty(uint32_t propertyID, float value)
	: propertyID(propertyID), propertyValue(value)
{
}

cSCBaseProperty::cSCBaseProperty(uint32_t propertyID, cIGZVariant const& propertyValue)
	: propertyID(propertyID), propertyValue(propertyValue)
{
}

cSCBaseProperty::cSCBaseProperty(uint32_t propertyID, cIGZVariant const* propertyValue)
	: propertyID(propertyID), propertyValue(propertyValue)
{
}

cSCBaseProperty::cSCBaseProperty(cISCProperty const& value)
	: propertyID(value.GetPropertyID()),
	  propertyValue(value.GetPropertyValue())
{
}

cSCBaseProperty::cSCBaseProperty(cSCBaseProperty const& value)
	: propertyID(value.propertyID),
	  propertyValue(value.propertyValue)
{
}

cSCBaseProperty& cSCBaseProperty::operator=(const cSCBaseProperty& other)
{
	if (this == &other)
	{
		return *this;
	}

	propertyID = other.propertyID;
	propertyValue = other.propertyValue;

	return *this;
}

cSCBaseProperty& cSCBaseProperty::operator=(cSCBaseProperty&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	propertyID = other.propertyID;
	propertyValue = std::move(other.propertyValue);
	mnRefCount = other.mnRefCount;

	other.propertyID = 0;
	other.mnRefCount = 0;

	return *this;
}

bool cSCBaseProperty::QueryInterface(uint32_t riid, void** ppvObj)
{
	if (riid == GZIID_cISCProperty)
	{
		*ppvObj = static_cast<cISCProperty*>(this);
		AddRef();

		return true;
	}
	else if (riid == GZIID_cIGZUnknown)
	{
		*ppvObj = static_cast<cIGZUnknown*>(static_cast<cISCProperty*>(this));
		AddRef();

		return true;
	}

	return propertyValue.QueryInterface(riid, ppvObj);
}

uint32_t cSCBaseProperty::AddRef()
{
	return cRZUnknown::AddRef();
}

uint32_t cSCBaseProperty::Release()
{
	return cRZUnknown::Release();
}

uint32_t cSCBaseProperty::GetPropertyID() const
{
	return propertyID;
}

void cSCBaseProperty::SetPropertyID(uint32_t value)
{
	propertyID = value;
}

cIGZVariant* cSCBaseProperty::GetPropertyValue()
{
	return &propertyValue;
}

const cIGZVariant* cSCBaseProperty::GetPropertyValue() const
{
	return &propertyValue;
}

bool cSCBaseProperty::SetPropertyValue(const cIGZVariant& value)
{
	return propertyValue.CopyFrom(value);
}

bool cSCBaseProperty::Write(cIGZOStream& stream) const
{
	bool result = false;

	cISC4DBSegmentOStream* dbSegment = nullptr;

	if (stream.QueryInterface(GZIID_cISC4DBSegmentOStream, reinterpret_cast<void**>(&dbSegment)))
	{
		result = dbSegment->SetUint32(propertyID)
			  && dbSegment->WriteVariant(propertyValue);

		dbSegment->Release();
	}

	return result;
}

bool cSCBaseProperty::Read(cIGZIStream& stream)
{
	bool result = false;

	cISC4DBSegmentIStream* dbSegment = nullptr;

	if (stream.QueryInterface(GZIID_cISC4DBSegmentIStream, reinterpret_cast<void**>(&dbSegment)))
	{
		result = dbSegment->GetUint32(propertyID)
			  && dbSegment->ReadVariant(propertyValue);

		dbSegment->Release();
	}

	return result;
}
