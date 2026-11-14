/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cRZBaseVariant.cpp
 *
 * Copyright (C) 2023, 2024, 2025, 2026 Nicholas Hayes
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

#include "cRZBaseVariant.h"
#include "cIGZString.h"
#include "cRZAutoRefCount.h"
#include "SC4String.h"
#include <cstdint>
#include <string>
#include <vector>

namespace
{
	void PointerToString(void* ptr, cIGZString& dest)
	{
		dest.Sprintf("0x%08X", reinterpret_cast<uintptr_t>(ptr));
	}

	char RZUnicodeCharToRZChar(uint16_t unicodeChar)
	{
		// A simple mapping from RZUnicodeChar (a.k.a. UTF-16LE) to US-ASCII.
		// This implementation is more conservative than SC4's own version as
		// it ignores characters outside of the printable US-ASCII range.

		return unicodeChar >= 0x20 && unicodeChar <= 0x7e ? static_cast<char>(unicodeChar) : '?';
	}

	void RZUnicodeCharArrayToString(uint16_t const* pUnicodeChars, uint32_t count, cIGZString& dest)
	{
		if (count == 0)
		{
			dest.Erase(0, UINT_MAX);
		}
		else if (count == 1)
		{
			char converted = RZUnicodeCharToRZChar(pUnicodeChars[0]);
			dest.FromChar(&converted, 1);
		}
		else
		{
			std::vector<char> convertedChars;
			convertedChars.reserve(count);

			for (uint32_t i = 0; i < count; i++)
			{
				convertedChars.push_back(RZUnicodeCharToRZChar(pUnicodeChars[i]));
			}

			dest.FromChar(convertedChars.data(), count);
		}
	}
}

cRZBaseVariant::cRZBaseVariant()
	: type(cIGZVariant::Type::Empty),
	  count(0)
{
	data.Uint64 = 0;
}

cRZBaseVariant::cRZBaseVariant(bool value)
	: type(cIGZVariant::Type::Bool),
	  count(0)
{
	data.Uint64 = 0;
	data.Bool = value;
}

cRZBaseVariant::cRZBaseVariant(uint16_t value)
	: type(cIGZVariant::Type::Uint16),
	  count(0)
{
	data.Uint64 = 0;
	data.Uint16 = value;
}

cRZBaseVariant::cRZBaseVariant(int16_t value)
	: type(cIGZVariant::Type::Sint16),
	  count(0)
{
	data.Uint64 = 0;
	data.Sint16 = value;
}

cRZBaseVariant::cRZBaseVariant(uint32_t value)
	: type(cIGZVariant::Type::Uint32),
	  count(0)
{
	data.Uint64 = 0;
	data.Uint32 = value;
}

cRZBaseVariant::cRZBaseVariant(int32_t value)
	: type(cIGZVariant::Type::Sint32),
	  count(0)
{
	data.Uint64 = 0;
	data.Sint32 = value;
}

cRZBaseVariant::cRZBaseVariant(uint64_t value)
	: type(cIGZVariant::Type::Uint64),
	  count(0)
{
	data.Uint64 = 0;
	data.Uint64 = value;
}

cRZBaseVariant::cRZBaseVariant(int64_t value)
	: type(cIGZVariant::Type::Sint64),
	  count(0)
{
	data.Uint64 = 0;
	data.Sint64 = value;
}

cRZBaseVariant::cRZBaseVariant(float value)
	: type(cIGZVariant::Type::Float32),
	  count(0)
{
	data.Uint64 = 0;
	data.Float32 = value;
}

cRZBaseVariant::cRZBaseVariant(double value)
	: type(cIGZVariant::Type::Float64),
	  count(0)
{
	data.Uint64 = 0;
	data.Float64 = value;
}

cRZBaseVariant::cRZBaseVariant(const cIGZString& value)
	: type(cIGZVariant::Type::Empty),
	  count(0)
{
	data.Uint64 = 0;
	RefRZChar(const_cast<char*>(value.Data()), value.Strlen());
}

cRZBaseVariant::cRZBaseVariant(const cIGZVariant& other)
	: type(cIGZVariant::Type::Empty),
	  count(0)
{
	CopyFrom(other);
}

cRZBaseVariant::cRZBaseVariant(const cIGZVariant* other)
	: type(cIGZVariant::Type::Empty),
	  count(0)
{
	if (other)
	{
		CopyFrom(*other);
	}
	else
	{
		data.Uint64 = 0;
	}
}

cRZBaseVariant::cRZBaseVariant(const cRZBaseVariant& other)
	: type(cIGZVariant::Type::Empty),
	  count(0)
{
	CopyFrom(other);
}

cRZBaseVariant::cRZBaseVariant(cRZBaseVariant&& other) noexcept
	: type(other.type),
	  count(other.count)
{
	operator=(std::move(other));
}

cRZBaseVariant::~cRZBaseVariant()
{
	Destroy();
}

cRZBaseVariant& cRZBaseVariant::operator=(const cIGZVariant& other)
{
	CopyFrom(other);

	return *this;
}

cRZBaseVariant& cRZBaseVariant::operator=(const cRZBaseVariant& other)
{
	if (this == &other)
	{
		return *this;
	}

	CopyFrom(other);

	return *this;
}

cRZBaseVariant& cRZBaseVariant::operator=(cRZBaseVariant&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	Destroy();

	type = other.type;
	count = other.count;
	mnRefCount = other.mnRefCount;

	switch (static_cast<cIGZVariant::Type>(other.GetType()))
	{
	case cIGZVariant::Type::Empty:
		break;
	case cIGZVariant::Type::Bool:
		data.Bool = other.GetValBool();
		break;
	case cIGZVariant::Type::Uint8:
		data.Uint8 = other.GetValUint8();
		break;
	case cIGZVariant::Type::Sint8:
		data.Sint8 = other.GetValSint8();
		break;
	case cIGZVariant::Type::Uint16:
		data.Uint16 = other.GetValUint16();
		break;
	case cIGZVariant::Type::Sint16:
		data.Sint16 = other.GetValSint16();
		break;
	case cIGZVariant::Type::Uint32:
		data.Uint32 = other.GetValUint32();
		break;
	case cIGZVariant::Type::Sint32:
		data.Sint32 = other.GetValSint32();
		break;
	case cIGZVariant::Type::Uint64:
		data.Uint64 = other.GetValUint64();
		break;
	case cIGZVariant::Type::Sint64:
		data.Sint64 = other.GetValSint64();
		break;
	case cIGZVariant::Type::Float32:
		data.Float32 = other.GetValFloat32();
		break;
	case cIGZVariant::Type::Float64:
		data.Float64 = other.GetValFloat64();
		break;
	case cIGZVariant::Type::Char:
		data.Char = other.GetValChar();
		break;
	case cIGZVariant::Type::RZUnicodeChar:
		data.RZUnicodeChar = other.GetValRZUnicodeChar();
		break;
	case cIGZVariant::Type::RZChar:
		data.RZChar = other.GetValRZChar();
		break;
	case cIGZVariant::Type::VoidPtr:
		data.VoidPtr = other.GetValVoidPtr();
		break;
	case cIGZVariant::Type::IGZUnknown:
		data.IGZUnknown = other.RefIGZUnknown();
		break;
	case cIGZVariant::Type::VoidArray:
	case cIGZVariant::Type::BoolArray:
	case cIGZVariant::Type::Uint8Array:
	case cIGZVariant::Type::Sint8Array:
	case cIGZVariant::Type::Uint16Array:
	case cIGZVariant::Type::Sint16Array:
	case cIGZVariant::Type::Uint32Array:
	case cIGZVariant::Type::Sint32Array:
	case cIGZVariant::Type::Uint64Array:
	case cIGZVariant::Type::Sint64Array:
	case cIGZVariant::Type::Float32Array:
	case cIGZVariant::Type::Float64Array:
	case cRZBaseVariant::cIGZVariant::Type::CharArray:
	case cRZBaseVariant::cIGZVariant::Type::RZUnicodeCharArray:
	case cRZBaseVariant::cIGZVariant::Type::RZCharArray:
	case cRZBaseVariant::cIGZVariant::Type::VoidPtrArray:
		data.VoidPtr = other.data.VoidPtr;
		break;
	}

	other.type = cIGZVariant::Type::Empty;
	other.count = 0;
	other.data.Uint64 = 0;
	other.mnRefCount = 0;

	return *this;
}

bool cRZBaseVariant::QueryInterface(uint32_t riid, void** ppvObj)
{
	if (riid == GZIID_cIGZVariant)
	{
		*ppvObj = static_cast<cIGZVariant*>(this);
		AddRef();

		return true;
	}
	
	return cRZUnknown::QueryInterface(riid, ppvObj);
}

uint32_t cRZBaseVariant::AddRef()
{
	return cRZUnknown::AddRef();
}

uint32_t cRZBaseVariant::Release()
{
	return cRZUnknown::Release();
}

uint16_t cRZBaseVariant::GetType() const
{
	return static_cast<uint16_t>(type);
}

uint32_t cRZBaseVariant::GetCount() const
{
	return count;
}

bool cRZBaseVariant::Erase()
{
	Destroy();
	return true;
}

bool cRZBaseVariant::CopyFrom(cIGZVariant const& other)
{
	Destroy();

	switch (static_cast<cIGZVariant::Type>(other.GetType()))
	{
	case cIGZVariant::Type::Empty:
		break;
	case cIGZVariant::Type::Bool:
		SetValBool(other.GetValBool());
		break;
	case cIGZVariant::Type::Uint8:
		SetValUint8(other.GetValUint8());
		break;
	case cIGZVariant::Type::Sint8:
		SetValSint8(other.GetValSint8());
		break;
	case cIGZVariant::Type::Uint16:
		SetValUint16(other.GetValUint16());
		break;
	case cIGZVariant::Type::Sint16:
		SetValSint16(other.GetValSint16());
		break;
	case cIGZVariant::Type::Uint32:
		SetValUint32(other.GetValUint32());
		break;
	case cIGZVariant::Type::Sint32:
		SetValSint32(other.GetValSint32());
		break;
	case cIGZVariant::Type::Uint64:
		SetValUint64(other.GetValUint64());
		break;
	case cIGZVariant::Type::Sint64:
		SetValSint64(other.GetValSint64());
		break;
	case cIGZVariant::Type::Float32:
		SetValFloat32(other.GetValFloat32());
		break;
	case cIGZVariant::Type::Float64:
		SetValFloat64(other.GetValFloat64());
		break;
	case cIGZVariant::Type::Char:
		SetValChar(other.GetValChar());
		break;
	case cIGZVariant::Type::RZUnicodeChar:
		SetValRZUnicodeChar(other.GetValRZUnicodeChar());
		break;
	case cIGZVariant::Type::RZChar:
		SetValRZChar(other.GetValRZChar());
		break;
	case cIGZVariant::Type::VoidPtr:
		SetValVoidPtr(other.GetValVoidPtr());
		break;
	case cIGZVariant::Type::IGZUnknown:
		SetValUnknown(other.RefIGZUnknown());
		break;
	case cIGZVariant::Type::VoidArray:
		RefVoid(other.RefVoid(), other.GetCount());
		break;
	case cIGZVariant::Type::BoolArray:
		RefBool(other.RefBool(), other.GetCount());
		break;
	case cIGZVariant::Type::Uint8Array:
		RefUint8(other.RefUint8(), other.GetCount());
		break;
	case cIGZVariant::Type::Sint8Array:
		RefSint8(other.RefSint8(), other.GetCount());
		break;
	case cIGZVariant::Type::Uint16Array:
		RefUint16(other.RefUint16(), other.GetCount());
		break;
	case cIGZVariant::Type::Sint16Array:
		RefSint16(other.RefSint16(), other.GetCount());
		break;
	case cIGZVariant::Type::Uint32Array:
		RefUint32(other.RefUint32(), other.GetCount());
		break;
	case cIGZVariant::Type::Sint32Array:
		RefSint32(other.RefSint32(), other.GetCount());
		break;
	case cIGZVariant::Type::Uint64Array:
		RefUint64(other.RefUint64(), other.GetCount());
		break;
	case cIGZVariant::Type::Sint64Array:
		RefSint64(other.RefSint64(), other.GetCount());
		break;
	case cIGZVariant::Type::Float32Array:
		RefFloat32(other.RefFloat32(), other.GetCount());
		break;
	case cIGZVariant::Type::Float64Array:
		RefFloat64(other.RefFloat64(), other.GetCount());
		break;
	case cRZBaseVariant::cIGZVariant::Type::CharArray:
		RefChar(other.RefChar(), other.GetCount());
		break;
	case cRZBaseVariant::cIGZVariant::Type::RZUnicodeCharArray:
		RefRZUnicodeChar(other.RefRZUnicodeChar(), other.GetCount());
		break;
	case cRZBaseVariant::cIGZVariant::Type::RZCharArray:
		RefRZChar(other.RefRZChar(), other.GetCount());
		break;
	case cRZBaseVariant::cIGZVariant::Type::VoidPtrArray:
		RefVoidPtr(other.RefVoidPtr(), other.GetCount());
		break;
	}

	return true;
}

bool cRZBaseVariant::CreateCopy(cIGZVariant** value) const
{
	*value = new cRZBaseVariant(*this);

	return true;
}

bool cRZBaseVariant::CanGetVal() const
{
	return type != cIGZVariant::Type::Empty;
}

bool cRZBaseVariant::GetValBool(bool& value) const
{
	if (type == cIGZVariant::Type::Bool)
	{
		value = data.Bool;
		return true;
	}

	return false;
}

bool cRZBaseVariant::GetValBool() const
{
	return data.Bool;
}

void cRZBaseVariant::SetValBool(bool value)
{
	SetType(cIGZVariant::Type::Bool);
	data.Bool = value;
}

bool cRZBaseVariant::GetValUint8(uint8_t& value) const
{
	if (type == cIGZVariant::Type::Uint8)
	{
		value = data.Uint8;
		return true;
	}

	return false;
}

uint8_t cRZBaseVariant::GetValUint8() const
{
	return data.Uint8;
}

void cRZBaseVariant::SetValUint8(uint8_t value)
{
	SetType(cIGZVariant::Type::Uint8);
	data.Uint8 = value;
}

bool cRZBaseVariant::GetValSint8(int8_t& value) const
{
	if (type == cIGZVariant::Type::Sint8)
	{
		value = data.Sint8;
		return true;
	}

	return false;
}

int8_t cRZBaseVariant::GetValSint8() const
{
	return data.Sint8;
}

void cRZBaseVariant::SetValSint8(int8_t value)
{
	SetType(cIGZVariant::Type::Sint8);
	data.Sint8 = value;
}

bool cRZBaseVariant::GetValUint16(uint16_t& value) const
{
	if (type == cIGZVariant::Type::Uint16)
	{
		value = data.Uint16;
		return true;
	}

	return false;
}

uint16_t cRZBaseVariant::GetValUint16() const
{
	return data.Uint16;
}

void cRZBaseVariant::SetValUint16(uint16_t value)
{
	SetType(cIGZVariant::Type::Uint16);
	data.Uint16 = value;
}

bool cRZBaseVariant::GetValSint16(int16_t& value) const
{
	if (type == cIGZVariant::Type::Sint16)
	{
		value = data.Sint16;
		return true;
	}

	return false;
}

int16_t cRZBaseVariant::GetValSint16() const
{
	return data.Sint16;
}

void cRZBaseVariant::SetValSint16(int16_t value)
{
	SetType(cIGZVariant::Type::Sint16);
	data.Sint16 = value;
}

bool cRZBaseVariant::GetValUint32(uint32_t& value) const
{
	if (type == cIGZVariant::Type::Uint32)
	{
		value = data.Uint32;
		return true;
	}

	return false;
}

uint32_t cRZBaseVariant::GetValUint32() const
{
	return data.Uint32;
}

void cRZBaseVariant::SetValUint32(uint32_t value)
{
	SetType(cIGZVariant::Type::Uint32);
	data.Uint32 = value;
}

bool cRZBaseVariant::GetValSint32(int32_t& value) const
{
	if (type == cIGZVariant::Type::Sint32)
	{
		value = data.Sint32;
		return true;
	}

	return false;
}

int32_t cRZBaseVariant::GetValSint32() const
{
	return data.Sint32;
}

void cRZBaseVariant::SetValSint32(int32_t value)
{
	SetType(cIGZVariant::Type::Sint32);
	data.Sint32 = value;
}

bool cRZBaseVariant::GetValUint64(uint64_t& value) const
{
	if (type == cIGZVariant::Type::Uint64)
	{
		value = data.Uint64;
		return true;
	}

	return false;
}

uint64_t cRZBaseVariant::GetValUint64() const
{
	return data.Uint64;
}

void cRZBaseVariant::SetValUint64(uint64_t value)
{
	SetType(cIGZVariant::Type::Uint64);
	data.Uint64 = value;
}

bool cRZBaseVariant::GetValSint64(int64_t& value) const
{
	if (type == cIGZVariant::Type::Sint64)
	{
		value = data.Sint64;
		return true;
	}

	return false;
}

int64_t cRZBaseVariant::GetValSint64() const
{
	return data.Sint64;
}

void cRZBaseVariant::SetValSint64(int64_t value)
{
	SetType(cIGZVariant::Type::Sint64);
	data.Sint64 = value;
}

bool cRZBaseVariant::GetValFloat32(float& value) const
{
	if (type == cIGZVariant::Type::Float32)
	{
		value = data.Float32;
		return true;
	}

	return false;
}

float cRZBaseVariant::GetValFloat32() const
{
	return data.Float32;
}

void cRZBaseVariant::SetValFloat32(float value)
{
	SetType(cIGZVariant::Type::Float32);
	data.Float32 = value;
}

bool cRZBaseVariant::GetValFloat64(double& value) const
{
	if (type == cIGZVariant::Type::Float64)
	{
		value = data.Float64;
		return true;
	}

	return false;
}

double cRZBaseVariant::GetValFloat64() const
{
	return data.Float64;
}

void cRZBaseVariant::SetValFloat64(double value)
{
	SetType(cIGZVariant::Type::Float64);
	data.Float64 = value;
}

bool cRZBaseVariant::GetValChar(char& value) const
{
	if (type == cIGZVariant::Type::Char)
	{
		value = data.Char;
		return true;
	}

	return false;
}

char cRZBaseVariant::GetValChar() const
{
	return data.Char;
}

void cRZBaseVariant::SetValChar(char value)
{
	SetType(cIGZVariant::Type::Char);
	data.Char = value;
}

bool cRZBaseVariant::GetValRZUnicodeChar(uint16_t& value) const
{
	if (type == cIGZVariant::Type::RZUnicodeChar)
	{
		value = data.RZUnicodeChar;
		return true;
	}

	return false;
}

uint16_t cRZBaseVariant::GetValRZUnicodeChar() const
{
	return data.RZUnicodeChar;
}

void cRZBaseVariant::SetValRZUnicodeChar(uint16_t value)
{
	SetType(cIGZVariant::Type::RZUnicodeChar);
	data.RZUnicodeChar = value;
}

bool cRZBaseVariant::GetValRZChar(char& value) const
{
	if (type == cIGZVariant::Type::RZChar)
	{
		value = data.RZChar;
		return true;
	}

	return false;
}

char cRZBaseVariant::GetValRZChar() const
{
	return data.RZChar;
}

void cRZBaseVariant::SetValRZChar(char value)
{
	SetType(cIGZVariant::Type::RZChar);
	data.RZChar = value;
}

bool cRZBaseVariant::GetValVoidPtr(void** value) const
{
	if (type == cIGZVariant::Type::VoidPtr)
	{
		*value = data.VoidPtr;
		return true;
	}

	return false;
}

void* cRZBaseVariant::GetValVoidPtr() const
{
	return data.VoidPtr;
}

void cRZBaseVariant::SetValVoidPtr(void* value)
{
	SetType(cIGZVariant::Type::VoidPtr);
	data.VoidPtr = value;
}

bool cRZBaseVariant::CreateValString(cIGZString** value) const
{
	SC4String* pSC4String = new SC4String();
	pSC4String->AddRef();

	if (ConvertToString(*pSC4String))
	{
		*value = pSC4String;
		return true;
	}

	pSC4String->Release();
	*value = nullptr;
	return false;
}

bool cRZBaseVariant::GetValString(cIGZString& value) const
{
	return ConvertToString(value);
}

void cRZBaseVariant::SetValString(cIGZString const& value)
{
	RefRZChar(value.Data(), value.Strlen());
}

bool cRZBaseVariant::GetValVoid(void* value, uint32_t& length) const
{
	if (type == cIGZVariant::VoidArray)
	{
		if (length > count)
		{
			length = count;
		}

		memmove(value, data.VoidPtr, length);
		return true;
	}

	return false;
}

void cRZBaseVariant::SetValVoid(void const* value, uint32_t length)
{
	if (type == cIGZVariant::VoidArray && length == count && data.VoidPtr != nullptr)
	{
		memmove(data.VoidPtr, value, length);
	}
	else
	{
		Destroy();

		data.VoidPtr = new uint8_t[length];

		if (value != nullptr)
		{
			memmove(data.VoidPtr, value, length);
		}

		type = cIGZVariant::VoidArray;
		count = length;
	}
}

bool cRZBaseVariant::GetValUnknown(cIGZUnknown** outValue)
{
	if (type == cIGZVariant::Type::IGZUnknown)
	{
		cIGZUnknown* gzUnknown = data.IGZUnknown;

		*outValue = gzUnknown;

		if (gzUnknown)
		{
			gzUnknown->AddRef();
		}
		return true;
	}

	return false;
}

cIGZUnknown* cRZBaseVariant::GetValUnknown()
{
	return data.IGZUnknown;
}

void cRZBaseVariant::SetValUnknown(cIGZUnknown* value)
{
	SetType(cIGZVariant::Type::IGZUnknown);

	data.IGZUnknown = value;
	if (value)
	{
		value->AddRef();
	}
}

bool& cRZBaseVariant::AsBool()
{
	return data.Bool;
}

bool cRZBaseVariant::AsBool() const
{
	return data.Bool;
}

uint8_t& cRZBaseVariant::AsUint8()
{
	return data.Uint8;
}

uint8_t cRZBaseVariant::AsUint8() const
{
	return data.Uint8;
}

int8_t& cRZBaseVariant::AsSint8()
{
	return data.Sint8;
}

int8_t cRZBaseVariant::AsSint8() const
{
	return data.Sint8;
}

uint16_t& cRZBaseVariant::AsUint16()
{
	return data.Uint16;
}

uint16_t cRZBaseVariant::AsUint16() const
{
	return data.Uint16;
}

int16_t& cRZBaseVariant::AsSint16()
{
	return data.Sint16;
}

int16_t cRZBaseVariant::AsSint16() const
{
	return data.Sint16;
}

uint32_t& cRZBaseVariant::AsUint32()
{
	return data.Uint32;
}

uint32_t cRZBaseVariant::AsUint32() const
{
	return data.Uint32;
}

int32_t& cRZBaseVariant::AsSint32()
{
	return data.Sint32;
}

int32_t cRZBaseVariant::AsSint32() const
{
	return data.Sint32;
}

uint64_t& cRZBaseVariant::AsUint64()
{
	return data.Uint64;
}

uint64_t cRZBaseVariant::AsUint64() const
{
	return data.Uint64;
}

int64_t& cRZBaseVariant::AsSint64()
{
	return data.Sint64;
}

int64_t cRZBaseVariant::AsSint64() const
{
	return data.Sint64;
}

float& cRZBaseVariant::AsFloat32()
{
	return data.Float32;
}

float cRZBaseVariant::AsFloat32() const
{
	return data.Float32;
}

double& cRZBaseVariant::AsFloat64()
{
	return data.Float64;
}

double cRZBaseVariant::AsFloat64() const
{
	return data.Float64;
}

char& cRZBaseVariant::AsChar()
{
	return data.Char;
}

char cRZBaseVariant::AsChar() const
{
	return data.Char;
}

uint16_t& cRZBaseVariant::AsRZUnicodeChar()
{
	return data.RZUnicodeChar;
}

uint16_t cRZBaseVariant::AsRZUnicodeChar() const
{
	return data.RZUnicodeChar;
}

char& cRZBaseVariant::AsRZChar()
{
	return data.RZChar;
}

char cRZBaseVariant::AsRZChar() const
{
	return data.RZChar;
}

void*& cRZBaseVariant::AsVoidPtr()
{
	return data.VoidPtr;
}

void* cRZBaseVariant::AsVoidPtr() const
{
	return data.VoidPtr;
}

bool* cRZBaseVariant::RefBool() const
{
	return static_cast<bool*>(data.VoidPtr);
}

void cRZBaseVariant::RefBool(bool const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::BoolArray && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(bool));
	}
	else
	{
		SetType(cIGZVariant::Type::BoolArray, length);

		const size_t dataLength = static_cast<size_t>(length) * sizeof(bool);

		if (value && length > 0)
		{
			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

uint8_t* cRZBaseVariant::RefUint8() const
{
	return static_cast<uint8_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefUint8(uint8_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Uint8Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(uint8_t));
	}
	else
	{
		SetType(cIGZVariant::Type::Uint8Array, length);

		const size_t dataLength = static_cast<size_t>(length) * sizeof(uint8_t);

		if (value && length > 0)
		{
			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

int8_t* cRZBaseVariant::RefSint8() const
{
	return static_cast<int8_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefSint8(int8_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Sint8Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(int8_t));
	}
	else
	{
		SetType(cIGZVariant::Type::Sint8Array, length);

		const size_t dataLength = static_cast<size_t>(length) * sizeof(int8_t);

		if (value && length > 0)
		{
			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

uint16_t* cRZBaseVariant::RefUint16() const
{
	return static_cast<uint16_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefUint16(uint16_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Uint16Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(uint16_t));
	}
	else
	{
		SetType(cIGZVariant::Type::Uint16Array, length);

		const size_t dataLength = static_cast<size_t>(length) * sizeof(uint16_t);

		if (value && length > 0)
		{
			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

int16_t* cRZBaseVariant::RefSint16() const
{
	return static_cast<int16_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefSint16(int16_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Sint16Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(int16_t));
	}
	else
	{
		SetType(cIGZVariant::Type::Sint16Array, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(int16_t);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

uint32_t* cRZBaseVariant::RefUint32() const
{
	return static_cast<uint32_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefUint32(uint32_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Uint32Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(uint32_t));
	}
	else
	{
		SetType(cIGZVariant::Type::Uint32Array, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(uint32_t);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

int32_t* cRZBaseVariant::RefSint32() const
{
	return static_cast<int32_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefSint32(int32_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Sint32Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(int32_t));
	}
	else
	{
		SetType(cIGZVariant::Type::Sint32Array, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(int32_t);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

uint64_t* cRZBaseVariant::RefUint64() const
{
	return static_cast<uint64_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefUint64(uint64_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Uint64Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(uint64_t));
	}
	else
	{
		SetType(cIGZVariant::Type::Uint64Array, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(uint64_t);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

int64_t* cRZBaseVariant::RefSint64() const
{
	return static_cast<int64_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefSint64(int64_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Sint64Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(int64_t));
	}
	else
	{
		SetType(cIGZVariant::Type::Sint64Array, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(int64_t);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

float* cRZBaseVariant::RefFloat32() const
{
	return static_cast<float*>(data.VoidPtr);
}

void cRZBaseVariant::RefFloat32(float const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Float32Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(float));
	}
	else
	{
		SetType(cIGZVariant::Type::Float32Array, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(float);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

double* cRZBaseVariant::RefFloat64() const
{
	return static_cast<double*>(data.VoidPtr);
}

void cRZBaseVariant::RefFloat64(double const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::Float64Array && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(double));
	}
	else
	{
		SetType(cIGZVariant::Type::Float64Array, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(double);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

char* cRZBaseVariant::RefChar() const
{
	return static_cast<char*>(data.VoidPtr);
}

void cRZBaseVariant::RefChar(char const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::CharArray && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(char));
	}
	else
	{
		SetType(cIGZVariant::Type::CharArray, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(char);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

uint16_t* cRZBaseVariant::RefRZUnicodeChar() const
{
	return static_cast<uint16_t*>(data.VoidPtr);
}

void cRZBaseVariant::RefRZUnicodeChar(uint16_t const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::RZUnicodeCharArray && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(uint16_t));
	}
	else
	{
		SetType(cIGZVariant::Type::RZUnicodeCharArray, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(uint16_t);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

char* cRZBaseVariant::RefRZChar() const
{
	return static_cast<char*>(data.VoidPtr);
}

void cRZBaseVariant::RefRZChar(char const* value, uint32_t length)
{
	if (type == cIGZVariant::Type::RZCharArray && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(char));
	}
	else
	{
		SetType(cIGZVariant::Type::RZCharArray, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(char);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

void** cRZBaseVariant::RefVoidPtr() const
{
	return reinterpret_cast<void**>(data.VoidPtr);
}

void cRZBaseVariant::RefVoidPtr(void** value, uint32_t length)
{
	if (type == cIGZVariant::Type::VoidPtrArray && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length * sizeof(void*));
	}
	else
	{
		SetType(cIGZVariant::Type::VoidPtrArray, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length) * sizeof(void*);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

void* cRZBaseVariant::RefVoid() const
{
	return data.VoidPtr;
}

void cRZBaseVariant::RefVoid(void* value, uint32_t length)
{
	if (type == cIGZVariant::Type::VoidArray && count == length && value && data.VoidPtr)
	{
		memmove(data.VoidPtr, value, length);
	}
	else
	{
		SetType(cIGZVariant::Type::VoidArray, length);

		if (value && length > 0)
		{
			const size_t dataLength = static_cast<size_t>(length);

			data.VoidPtr = operator new[](dataLength);
			memmove(data.VoidPtr, value, dataLength);
		}
	}
}

cIGZUnknown* cRZBaseVariant::RefIGZUnknown() const
{
	return data.IGZUnknown;
}

bool cRZBaseVariant::RefIGZUnknown(uint32_t riid, void** ppvObj)
{
	bool result = false;

	if (type == cIGZVariant::Type::IGZUnknown)
	{
		cIGZUnknown* item = data.IGZUnknown;

		if (item)
		{
			result = item->QueryInterface(riid, ppvObj);
		}
	}

	return result;
}

void cRZBaseVariant::RefIGZUnknown(cIGZUnknown* value)
{
	SetType(cIGZVariant::Type::IGZUnknown);

	data.IGZUnknown = value;

	if (value)
	{
		value->AddRef();
	}
}

bool cRZBaseVariant::ConvertToString(cIGZString& output) const
{
	if (type == cIGZVariant::Empty)
	{
		output.Erase(0, UINT_MAX);
		return true;
	}
	else if (type == cIGZVariant::IGZUnknown)
	{
		if (data.IGZUnknown)
		{
			cRZAutoRefCount<cIGZString> pString;

			if (data.IGZUnknown->QueryInterface(GZIID_cIGZString, pString.AsPPVoid()))
			{
				output.Copy(*pString);
			}
			else
			{
				PointerToString(data.IGZUnknown, output);
			}
		}
		else
		{
			output.FromChar("0");
		}
		return true;
	}
	else
	{
		if ((static_cast<uint16_t>(type) & cIGZVariant::TypeArray) != 0)
		{
			if (count == 0 || !data.VoidPtr)
			{
				output.FromChar("0");
			}
			else
			{
				switch (type)
				{
				case cIGZVariant::CharArray:
				case cIGZVariant::RZCharArray:
					output.FromChar(static_cast<const char*>(data.VoidPtr), count);
					break;
				case cIGZVariant::RZUnicodeCharArray:
					RZUnicodeCharArrayToString(static_cast<const uint16_t*>(data.VoidPtr), count, output);
					break;
				default:
					PointerToString(data.VoidPtr, output);
					break;
				}
			}
			return true;
		}
		else
		{
			switch (type)
			{
			case cIGZVariant::Bool:
				output.Sprintf("%d", static_cast<int32_t>(data.Bool));
				break;
			case cIGZVariant::Uint8:
				output.Sprintf("%u", static_cast<uint32_t>(data.Uint8));
				break;
			case cIGZVariant::Sint8:
				output.Sprintf("%d", static_cast<int32_t>(data.Sint8));
				break;
			case cIGZVariant::Uint16:
				output.Sprintf("%u", static_cast<uint32_t>(data.Uint16));
				break;
			case cIGZVariant::Sint16:
				output.Sprintf("%d", static_cast<int32_t>(data.Sint16));
				break;
			case cIGZVariant::Uint32:
				output.Sprintf("%u", data.Uint32);
				break;
			case cIGZVariant::Sint32:
				output.Sprintf("%d", data.Sint32);
				break;
			case cIGZVariant::Uint64:
				output.Sprintf("%llu", data.Uint64);
				break;
			case cIGZVariant::Sint64:
				output.Sprintf("%lld", data.Sint64);
				break;
			case cIGZVariant::Float32:
				output.Sprintf("%f", static_cast<double>(data.Float32));
				break;
			case cIGZVariant::Float64:
				output.Sprintf("%f", data.Float64);
				break;
			case cIGZVariant::Char:
				output.FromChar(&data.Char, 1);
				break;
			case cIGZVariant::RZChar:
				output.FromChar(&data.RZChar, 1);
				break;
			case cIGZVariant::RZUnicodeChar:
				output.Sprintf("%c", RZUnicodeCharToRZChar(data.RZUnicodeChar));
				break;
			case cIGZVariant::VoidPtr:
				PointerToString(data.VoidPtr, output);
				break;
			default:
				return false;
			}
			return true;
		}
	}
}

void cRZBaseVariant::Destroy()
{
	if ((static_cast<uint16_t>(type) & cIGZVariant::TypeArray) != 0)
	{
		void* voidPtr = data.VoidPtr;

		if (voidPtr)
		{
			operator delete[](voidPtr);
		}
	}
	else if (type == cIGZVariant::Type::IGZUnknown)
	{
		cIGZUnknown* gzUnknown = data.IGZUnknown;

		if (gzUnknown)
		{
			gzUnknown->Release();
		}
	}

	type = cIGZVariant::Type::Empty;
	count = 0;
	data.Uint64 = 0;
}

void cRZBaseVariant::SetType(cIGZVariant::Type newType, uint32_t count)
{
	Destroy();
	this->type = newType;
	this->count = count;
}
