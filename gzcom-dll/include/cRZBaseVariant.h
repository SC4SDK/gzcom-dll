/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cRZBaseVariant.h
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

#include "cIGZVariant.h"
#include "cRZUnknown.h"

class cRZBaseVariant : public cIGZVariant, public cRZUnknown
{
public:

	cRZBaseVariant();
	cRZBaseVariant(bool);
	cRZBaseVariant(uint16_t);
	cRZBaseVariant(int16_t);
	cRZBaseVariant(uint32_t);
	cRZBaseVariant(int32_t);
	cRZBaseVariant(uint64_t);
	cRZBaseVariant(int64_t);
	cRZBaseVariant(float);
	cRZBaseVariant(double);
	cRZBaseVariant(const cIGZString&);
	cRZBaseVariant(const cIGZVariant& other);
	cRZBaseVariant(const cIGZVariant* other);

	cRZBaseVariant(const cRZBaseVariant& other);
	cRZBaseVariant(cRZBaseVariant&& other) noexcept;

	~cRZBaseVariant();

	cRZBaseVariant& operator=(const cIGZVariant& other);
	cRZBaseVariant& operator=(const cRZBaseVariant& other);
	cRZBaseVariant& operator=(cRZBaseVariant&& other) noexcept;

	// cIGZUnknown

	bool QueryInterface(uint32_t riid, void** ppvObj);
	uint32_t AddRef();
	uint32_t Release();

	// cIGZVariant

	uint16_t GetType() const;
	uint32_t GetCount() const;
	bool Erase();
	bool CopyFrom(cIGZVariant const& value);
	bool CreateCopy(cIGZVariant** value) const;
	bool CanGetVal() const;

	bool GetValBool(bool& value) const;
	bool GetValBool() const;
	void SetValBool(bool value);

	bool GetValUint8(uint8_t& value) const;
	uint8_t GetValUint8() const;
	void SetValUint8(uint8_t value);

	bool GetValSint8(int8_t& value) const;
	int8_t GetValSint8() const;
	void SetValSint8(int8_t value);

	bool GetValUint16(uint16_t& value) const;
	uint16_t GetValUint16() const;
	void SetValUint16(uint16_t value);

	bool GetValSint16(int16_t& value) const;
	int16_t GetValSint16() const;
	void SetValSint16(int16_t value);

	bool GetValUint32(uint32_t& value) const;
	uint32_t GetValUint32() const;
	void SetValUint32(uint32_t value);

	bool GetValSint32(int32_t& value) const;
	int32_t GetValSint32() const;
	void SetValSint32(int32_t value);

	bool GetValUint64(uint64_t& value) const;
	uint64_t GetValUint64() const;
	void SetValUint64(uint64_t value);

	bool GetValSint64(int64_t& value) const;
	int64_t GetValSint64() const;
	void SetValSint64(int64_t value);

	bool GetValFloat32(float& value) const;
	float GetValFloat32() const;
	void SetValFloat32(float value);

	bool GetValFloat64(double& value) const;
	double GetValFloat64() const;
	void SetValFloat64(double value);

	bool GetValChar(char& value) const;
	char GetValChar() const;
	void SetValChar(char value);

	bool GetValRZUnicodeChar(uint16_t& value) const;
	uint16_t GetValRZUnicodeChar() const;
	void SetValRZUnicodeChar(uint16_t value);

	bool GetValRZChar(char& value) const;
	char GetValRZChar() const;
	void SetValRZChar(char value);

	bool GetValVoidPtr(void** value) const;
	void* GetValVoidPtr() const;
	void SetValVoidPtr(void* value);

	bool CreateValString(cIGZString** value) const;
	bool GetValString(cIGZString& value) const;
	void SetValString(cIGZString const& value);

	bool GetValVoid(void* value, uint32_t& length) const;
	void SetValVoid(void* value, uint32_t length);

	bool GetValUnknown(cIGZUnknown** outValue);
	cIGZUnknown* GetValUnknown();
	void SetValUnknown(cIGZUnknown* value);

	bool& AsBool();
	bool AsBool() const;
	uint8_t& AsUint8();
	uint8_t AsUint8() const;
	int8_t& AsSint8();
	int8_t AsSint8() const;
	uint16_t& AsUint16();
	uint16_t AsUint16() const;
	int16_t& AsSint16();
	int16_t AsSint16() const;
	uint32_t& AsUint32();
	uint32_t AsUint32() const;
	int32_t& AsSint32();
	int32_t AsSint32() const;
	uint64_t& AsUint64();
	uint64_t AsUint64() const;
	int64_t& AsSint64();
	int64_t AsSint64() const;
	float& AsFloat32();
	float AsFloat32() const;
	double& AsFloat64();
	double AsFloat64() const;
	char& AsChar();
	char AsChar() const;
	uint16_t& AsRZUnicodeChar();
	uint16_t AsRZUnicodeChar() const;
	char& AsRZChar();
	char AsRZChar() const;
	void*& AsVoidPtr();
	void* AsVoidPtr() const;

	bool* RefBool() const;
	void RefBool(bool* value, uint32_t length);
	uint8_t* RefUint8() const;
	void RefUint8(uint8_t* value, uint32_t length);
	int8_t* RefSint8() const;
	void RefSint8(int8_t* value, uint32_t length);
	uint16_t* RefUint16() const;
	void RefUint16(uint16_t* value, uint32_t length);
	int16_t* RefSint16() const;
	void RefSint16(int16_t* value, uint32_t length);
	uint32_t* RefUint32() const;
	void RefUint32(uint32_t* value, uint32_t length);
	int32_t* RefSint32() const;
	void RefSint32(int32_t* value, uint32_t length);
	uint64_t* RefUint64() const;
	void RefUint64(uint64_t* value, uint32_t length);
	int64_t* RefSint64() const;
	void RefSint64(int64_t* value, uint32_t length);
	float* RefFloat32() const;
	void RefFloat32(float* value, uint32_t length);
	double* RefFloat64() const;
	void RefFloat64(double* value, uint32_t length);
	char* RefChar() const;
	void RefChar(char* value, uint32_t length);
	uint16_t* RefRZUnicodeChar() const;
	void RefRZUnicodeChar(uint16_t* value, uint32_t length);
	char* RefRZChar() const;
	void RefRZChar(char* value, uint32_t length);
	void** RefVoidPtr() const;
	void RefVoidPtr(void** value, uint32_t length);
	void* RefVoid() const;
	void RefVoid(void* value, uint32_t length);
	cIGZUnknown* RefIGZUnknown() const;
	bool RefIGZUnknown(uint32_t riid, void** ppObj);
	void RefIGZUnknown(cIGZUnknown* value);

private:

	void Clear();
	void SetType(cIGZVariant::Type newType, uint32_t count = 0);

	union
	{
		bool Bool;
		uint8_t Uint8;
		int8_t Sint8;
		uint16_t Uint16;
		int16_t Sint16;
		uint32_t Uint32;
		int32_t Sint32;
		uint64_t Uint64;
		int64_t Sint64;
		float Float32;
		double Float64;
		char Char;
		uint16_t RZUnicodeChar;
		char RZChar;
		void* VoidPtr;
		cIGZUnknown* IGZUnknown;
	} data;
	cIGZVariant::Type type;
	uint32_t count;
};