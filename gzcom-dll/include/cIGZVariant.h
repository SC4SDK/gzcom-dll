/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cIGZVariant.h
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

#pragma once
#include "cIGZUnknown.h"

class cIGZString;

static const uint32_t GZIID_cIGZVariant = 0x60fd4d2b;

class cIGZVariant : public cIGZUnknown
{
public:

	static const uint16_t TypeArray = 0x8000;

	enum Type : uint16_t
	{
		Empty = 0x0000,
		Bool = 0x0001,
		Uint8 = 0x0002,
		Sint8 = 0x0003,
		Uint16 = 0x0004,
		Sint16 = 0x0005,
		Uint32 = 0x0006,
		Sint32 = 0x0007,
		Uint64 = 0x0008,
		Sint64 = 0x0009,
		Float32 = 0x000a,
		Float64 = 0x000b,
		Char = 0x000c,
		RZUnicodeChar = 0x000d,
		RZChar = 0x000e,
		VoidPtr = 0x000f,
		IGZUnknown = 0x0010,
		VoidArray = TypeArray,
		BoolArray = TypeArray | Bool,
		Uint8Array = TypeArray | Uint8,
		Sint8Array = TypeArray | Sint8,
		Uint16Array = TypeArray | Uint16,
		Sint16Array = TypeArray | Sint16,
		Uint32Array = TypeArray | Uint32,
		Sint32Array = TypeArray | Sint32,
		Uint64Array = TypeArray | Uint64,
		Sint64Array = TypeArray | Sint64,
		Float32Array = TypeArray | Float32,
		Float64Array = TypeArray | Float64,
		CharArray = TypeArray | Char,
		RZUnicodeCharArray = TypeArray | RZUnicodeChar,
		RZCharArray = TypeArray | RZChar,
		VoidPtrArray = TypeArray | VoidPtr,
	};

	virtual uint16_t GetType() const = 0;
	virtual uint32_t GetCount() const = 0;
	virtual bool Erase() = 0;
	virtual bool CopyFrom(cIGZVariant const& value) = 0;
	virtual bool CreateCopy(cIGZVariant** value) const = 0;
	virtual bool CanGetVal() const = 0;

	virtual bool GetValBool(bool& value) const = 0;
	virtual bool GetValBool() const = 0;
	virtual void SetValBool(bool value) = 0;

	virtual bool GetValUint8(uint8_t& value) const = 0;
	virtual uint8_t GetValUint8() const = 0;
	virtual void SetValUint8(uint8_t value) = 0;

	virtual bool GetValSint8(int8_t& value) const = 0;
	virtual int8_t GetValSint8() const = 0;
	virtual void SetValSint8(int8_t value) = 0;

	virtual bool GetValUint16(uint16_t& value) const = 0;
	virtual uint16_t GetValUint16() const = 0;
	virtual void SetValUint16(uint16_t value) = 0;

	virtual bool GetValSint16(int16_t& value) const = 0;
	virtual int16_t GetValSint16() const = 0;
	virtual void SetValSint16(int16_t value) = 0;

	virtual bool GetValUint32(uint32_t& value) const = 0;
	virtual uint32_t GetValUint32() const = 0;
	virtual void SetValUint32(uint32_t value) = 0;

	virtual bool GetValSint32(int32_t& value) const = 0;
	virtual int32_t GetValSint32() const = 0;
	virtual void SetValSint32(int32_t value) = 0;

	virtual bool GetValUint64(uint64_t& value) const = 0;
	virtual uint64_t GetValUint64() const = 0;
	virtual void SetValUint64(uint64_t value) = 0;

	virtual bool GetValSint64(int64_t& value) const = 0;
	virtual int64_t GetValSint64() const = 0;
	virtual void SetValSint64(int64_t value) = 0;

	virtual bool GetValFloat32(float& value) const = 0;
	virtual float GetValFloat32() const = 0;
	virtual void SetValFloat32(float vlaue) = 0;

	virtual bool GetValFloat64(double& value) const = 0;
	virtual double GetValFloat64() const = 0;
	virtual void SetValFloat64(double value) = 0;

	virtual bool GetValChar(char& value) const = 0;
	virtual char GetValChar() const = 0;
	virtual void SetValChar(char value) = 0;

	virtual bool GetValRZUnicodeChar(uint16_t& value) const = 0;
	virtual uint16_t GetValRZUnicodeChar() const = 0;
	virtual void SetValRZUnicodeChar(uint16_t value) = 0;

	virtual bool GetValRZChar(char& value) const = 0;
	virtual char GetValRZChar() const = 0;
	virtual void SetValRZChar(char value) = 0;

	virtual bool GetValVoidPtr(void** value) const = 0;
	virtual void* GetValVoidPtr() const = 0;
	virtual void SetValVoidPtr(void* value) = 0;

	virtual bool CreateValString(cIGZString** value) const = 0;
	virtual bool GetValString(cIGZString& value) const = 0;
	virtual void SetValString(cIGZString const& value) = 0;

	virtual bool GetValVoid(void* value, uint32_t& length) const = 0;
	virtual void SetValVoid(void const* value, uint32_t length) = 0;

	virtual bool GetValUnknown(cIGZUnknown** outValue) = 0;
	virtual cIGZUnknown* GetValUnknown() = 0;
	virtual void SetValUnknown(cIGZUnknown* value) = 0;

	virtual bool& AsBool() = 0;
	virtual bool AsBool() const = 0;
	virtual uint8_t& AsUint8() = 0;
	virtual uint8_t AsUint8() const = 0;
	virtual int8_t& AsSint8() = 0;
	virtual int8_t AsSint8() const = 0;
	virtual uint16_t& AsUint16() = 0;
	virtual uint16_t AsUint16() const = 0;
	virtual int16_t& AsSint16() = 0;
	virtual int16_t AsSint16() const = 0;
	virtual uint32_t& AsUint32() = 0;
	virtual uint32_t AsUint32() const = 0;
	virtual int32_t& AsSint32() = 0;
	virtual int32_t AsSint32() const = 0;
	virtual uint64_t& AsUint64() = 0;
	virtual uint64_t AsUint64() const = 0;
	virtual int64_t& AsSint64() = 0;
	virtual int64_t AsSint64() const = 0;
	virtual float& AsFloat32() = 0;
	virtual float AsFloat32() const = 0;
	virtual double& AsFloat64() = 0;
	virtual double AsFloat64() const = 0;
	virtual char& AsChar() = 0;
	virtual char AsChar() const = 0;
	virtual uint16_t& AsRZUnicodeChar() = 0;
	virtual uint16_t AsRZUnicodeChar() const = 0;
	virtual char& AsRZChar() = 0;
	virtual char AsRZChar() const = 0;
	virtual void*& AsVoidPtr() = 0;
	virtual void* AsVoidPtr() const = 0;

	virtual bool* RefBool() const = 0;
	virtual void RefBool(bool const* value, uint32_t length) = 0;
	virtual uint8_t* RefUint8() const = 0;
	virtual void RefUint8(uint8_t const* value, uint32_t length) = 0;
	virtual int8_t* RefSint8() const = 0;
	virtual void RefSint8(int8_t const* value, uint32_t length) = 0;
	virtual uint16_t* RefUint16() const = 0;
	virtual void RefUint16(uint16_t const* value, uint32_t length) = 0;
	virtual int16_t* RefSint16() const = 0;
	virtual void RefSint16(int16_t const* value, uint32_t length) = 0;
	virtual uint32_t* RefUint32() const = 0;
	virtual void RefUint32(uint32_t const* value, uint32_t length) = 0;
	virtual int32_t* RefSint32() const = 0;
	virtual void RefSint32(int32_t const* value, uint32_t length) = 0;
	virtual uint64_t* RefUint64() const = 0;
	virtual void RefUint64(uint64_t const* value, uint32_t length) = 0;
	virtual int64_t* RefSint64() const = 0;
	virtual void RefSint64(int64_t const* value, uint32_t length) = 0;
	virtual float* RefFloat32() const = 0;
	virtual void RefFloat32(float const* value, uint32_t length) = 0;
	virtual double* RefFloat64() const = 0;
	virtual void RefFloat64(double const* value, uint32_t length) = 0;
	virtual char* RefChar() const = 0;
	virtual void RefChar(char const* value, uint32_t length) = 0;
	virtual uint16_t* RefRZUnicodeChar() const = 0;
	virtual void RefRZUnicodeChar(uint16_t const* value, uint32_t length) = 0;
	virtual char* RefRZChar() const = 0;
	virtual void RefRZChar(char const* value, uint32_t length) = 0;
	virtual void** RefVoidPtr() const = 0;
	virtual void RefVoidPtr(void** value, uint32_t length) = 0;
	virtual void* RefVoid() const = 0;
	virtual void RefVoid(void* value, uint32_t length) = 0;
	virtual cIGZUnknown* RefIGZUnknown() const = 0;
	virtual bool RefIGZUnknown(uint32_t riid, void** ppvObj) = 0;
	virtual void RefIGZUnknown(cIGZUnknown* value) = 0;
};