/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cSCBaseProperty.h
 *
 * Copyright (C) 2023, 2026 Nicholas Hayes
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

#include "cISCProperty.h"
#include "cRZBaseVariant.h"

class cSCBaseProperty : public cISCProperty, public cRZUnknown
{
public:

	cSCBaseProperty();
	cSCBaseProperty(uint32_t propertyID);
	cSCBaseProperty(uint32_t propertyID, bool value);
	cSCBaseProperty(uint32_t propertyID, uint8_t value);
	cSCBaseProperty(uint32_t propertyID, int8_t value);
	cSCBaseProperty(uint32_t propertyID, uint16_t value);
	cSCBaseProperty(uint32_t propertyID, int16_t value);
	cSCBaseProperty(uint32_t propertyID, uint32_t value);
	cSCBaseProperty(uint32_t propertyID, int32_t value);
	cSCBaseProperty(uint32_t propertyID, uint64_t value);
	cSCBaseProperty(uint32_t propertyID, int64_t value);
	cSCBaseProperty(uint32_t propertyID, float value);
	cSCBaseProperty(uint32_t propertyID, double value);
	cSCBaseProperty(uint32_t propertyID, cIGZString const& value);
	cSCBaseProperty(uint32_t propertyID, cIGZVariant const& propertyValue);
	cSCBaseProperty(uint32_t propertyID, cIGZVariant const* propertyValue);

	cSCBaseProperty(cISCProperty const& value);
	cSCBaseProperty(cSCBaseProperty const& value);

	cSCBaseProperty& operator=(const cSCBaseProperty& other);
	cSCBaseProperty& operator=(cSCBaseProperty&& other) noexcept;

	// cIGZUnknown

	bool QueryInterface(uint32_t riid, void** ppvObj);
	uint32_t AddRef();
	uint32_t Release();

	// cISCProperty

	uint32_t GetPropertyID() const;
	void SetPropertyID(uint32_t value);

	cIGZVariant* GetPropertyValue();
	const cIGZVariant* GetPropertyValue() const;

	bool SetPropertyValue(const cIGZVariant& value);
	bool Write(cIGZOStream& stream) const;
	bool Read(cIGZIStream& stream);

private:

	uint32_t propertyID;
	cRZBaseVariant propertyValue;
};