/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * STLPORTCharString.h
 *
 * Copyright (C) 2026 Nicholas Hayes
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

#include "STLPORTCharString.h"
#include "cIGZAllocatorService.h"
#include "GZServPtrs.h"
#include <stdexcept>

namespace
{
	char* allocate(size_t length)
	{
		cIGZAllocatorServicePtr pAllocator;

		char* ptr = static_cast<char*>(pAllocator->Allocate(length));

		if (!ptr)
		{
			throw std::bad_alloc();
		}

		return ptr;
	}

	void deallocate(char* ptr)
	{
		cIGZAllocatorServicePtr pAllocator;

		pAllocator->Deallocate(ptr);
	}
}

STLPORT::CharString::CharString() : mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
{
	construct_empty_string();
}

STLPORT::CharString::CharString(CharString const& other) : mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
{
	operator=(other);
}

STLPORT::CharString::CharString(CharString&& other) noexcept : mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
{
	operator=(std::move(other));
}

STLPORT::CharString::CharString(std::string_view const& view) : mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
{
	assign(view.data(), view.size());
}

STLPORT::CharString::CharString(char const* pszSource) : mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
{
	assign(pszSource);
}

STLPORT::CharString::CharString(char const* pszSource, size_t dwLength) : mpStart(nullptr), mpEnd(nullptr), mpCapacity(nullptr)
{
	assign(pszSource, dwLength);
}

STLPORT::CharString::~CharString()
{
	if (mpStart)
	{
		deallocate(mpStart);
	}

	mpStart = nullptr;
	mpEnd = nullptr;
	mpCapacity = nullptr;
}

STLPORT::CharString& STLPORT::CharString::operator=(CharString const& other)
{
	if (this != &other)
	{
		assign(other.data(), other.length());
	}
	return *this;
}

STLPORT::CharString& STLPORT::CharString::operator=(CharString&& other) noexcept
{
	if (this != &other)
	{
		mpStart = std::exchange(other.mpStart, nullptr);
		mpEnd = std::exchange(other.mpEnd, nullptr);
		mpCapacity = std::exchange(other.mpCapacity, nullptr);
	}
	return *this;
}

char* STLPORT::CharString::data() const
{
	return mpStart;
}

size_t STLPORT::CharString::length() const
{
	return mpEnd - mpStart;
}

void STLPORT::CharString::assign(const char* pszSource)
{
	if (!pszSource || *pszSource == 0)
	{
		this->construct_empty_string();
	}
	else
	{
		const size_t dwLength = std::char_traits<char>::length(pszSource);

		this->allocate_string_buffer(dwLength);

		std::char_traits<char>::move(mpStart, pszSource, dwLength);
	}
}

void STLPORT::CharString::assign(const char* pszSource, size_t dwLength)
{
	if (!pszSource || dwLength == 0)
	{
		this->construct_empty_string();
	}
	else
	{
		this->allocate_string_buffer(dwLength);

		std::char_traits<char>::move(mpStart, pszSource, dwLength);
	}
}

int STLPORT::CharString::compare(char const* pszOther, size_t length) const
{
	if (length == SIZE_MAX)
	{
		length = std::char_traits<char>::length(pszOther);
	}

	const size_t thisStringLength = this->length();

	int result = memcmp(this->mpStart, pszOther, (std::min)(thisStringLength, length));

	if (result == 0)
	{
		if (thisStringLength < length)
		{
			result = -1;
		}
		else if (thisStringLength > length)
		{
			result = 1;
		}
	}

	return result;
}

void STLPORT::CharString::append(char const* pszOther, size_t length)
{
	if (length == SIZE_MAX)
	{
		length = std::char_traits<char>::length(pszOther);
	}

	if (length != 0)
	{
		if (this->length() == 0)
		{
			this->assign(pszOther, length);
		}
		else
		{
			std::string temp(this->data(), this->length());
			temp.append(pszOther, length);

			this->assign(temp.c_str(), temp.size());
		}
	}
}

void STLPORT::CharString::insert(size_t pos, char const* pszOther, size_t length)
{
	std::string temp(this->data(), this->length());
	temp.insert(pos, pszOther, length);

	this->assign(temp.c_str(), temp.size());
}

void STLPORT::CharString::replace(size_t pos, char const* pszOther, size_t length)
{
	std::string temp(this->data(), this->length());
	temp.replace(pos, length, pszOther);

	this->assign(temp.c_str(), temp.size());
}

void STLPORT::CharString::erase(size_t startPos, size_t endPos)
{
	std::string temp(this->data(), this->length());
	temp.erase(startPos, endPos);

	this->assign(temp.c_str(), temp.size());
}

void STLPORT::CharString::resize(size_t dwNewSize)
{
	if (dwNewSize == 0)
	{
		this->construct_empty_string();
	}
	else if (this->length() == 0)
	{
		this->allocate_string_buffer(dwNewSize);
		std::char_traits<char>::assign(mpStart, dwNewSize, '\0');
	}
	else
	{
		std::string temp(this->data(), this->length());
		temp.resize(dwNewSize);

		this->assign(temp.c_str(), temp.size());
	}
}

void STLPORT::CharString::allocate_string_buffer(size_t stringLength)
{
	if (stringLength == SIZE_MAX)
	{
		throw std::out_of_range("STLPORT::CharString");
	}

	const size_t lengthWithTerminator = stringLength + 1;

	if (lengthWithTerminator < capacity())
	{
		mpEnd = mpStart + stringLength;
		*mpEnd = 0;
	}
	else
	{
		if (mpStart)
		{
			deallocate(mpStart);
			mpStart = nullptr;
			mpEnd = nullptr;
			mpCapacity = nullptr;
		}

		char* newStart = allocate(lengthWithTerminator);

		mpStart = newStart;
		mpEnd = newStart + stringLength;
		mpCapacity = mpEnd;
		*mpEnd = 0;
	}
}

size_t STLPORT::CharString::capacity()
{
	return mpCapacity - mpStart;
}

void STLPORT::CharString::construct_empty_string()
{
	if (mpStart)
	{
		if (mpStart != mpEnd)
		{
			*mpStart = 0;
			mpEnd = mpStart;
		}
	}
	else
	{
		constexpr size_t emptyStringSize = 1;

		mpStart = allocate(emptyStringSize);
		mpEnd = mpStart;
		mpCapacity = mpStart + emptyStringSize;
		*mpStart = 0;
	}
}

static_assert(sizeof(STLPORT::CharString) == 0xc);
