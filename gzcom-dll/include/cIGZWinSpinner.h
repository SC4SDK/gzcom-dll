/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cIGZWinSpinner.h
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

#pragma once
#include "cIGZUnknown.h"

static const uint32_t GZIID_cIGZWinSpinner = 0x612ce0c3;

class cIGZBuffer;
class cIGZFont;
class cIGZWin;
class cRZColor;
class cRZRect;

class cIGZWinSpinner : public cIGZUnknown
{
public:
	enum class tFontColorIdx : int32_t
	{
		Normal = 0,
		Highlighted = 1,
		Disabled = 2
	};

	enum class tOutlineIndex : int32_t
	{
		Left = 0,
		Top = 1,
		Right = 2,
		Bottom = 3
	};

	enum tSpinnerFlag : int32_t
	{
		SpinnerFlagOutline = 0x1,
		SpinnerFlagFill = 0x2,
		SpinnerFlagAutoNumber = 0x1000,
		SpinnerFlagAutoNumberComma = 0x2000,
		SpinnerFlagAutoNumberCurrency = 0x4000,
	};

	enum class tSpinnerType : int32_t
	{
		NoDigits = 0,
		LeftDigits = 1,
		RightDigits = 2,
	};

	enum class tTextAlignment : int32_t
	{
		Left = 0,
		Center = 1,
		Right = 2
	};

	struct tWinProcMessageTypes
	{
		enum eWinProcMessageTypes : uint32_t
		{
			// The control id is in data1, and the new value is in data2.
			ValueChanged = 0xe8711255,
		};
	};

	virtual cIGZWin* AsIGZWin() = 0;

	virtual bool SetSpinnerType(tSpinnerType type) = 0;
	virtual bool GetSpinnerType(tSpinnerType& type) const = 0;
	virtual bool SetSpinnerFlag(tSpinnerFlag flags, bool enabled) = 0;
	virtual bool GetSpinnerFlag(tSpinnerFlag flags) const = 0;

	virtual int32_t GetValue() = 0;
	virtual bool SetValue(int32_t value) = 0;
	virtual bool SetMinMax(int32_t min, int32_t max) = 0;
	virtual bool GetMinMax(int32_t& min, int32_t& max) = 0;
	virtual bool SetStepSize(int32_t value) = 0;
	virtual bool GetStepSize(int32_t& value) = 0;

	virtual bool SetImage(cIGZBuffer* imageBuffer, cRZRect const& imageArea) = 0;
	virtual bool SetButtonImage(cIGZBuffer* imageBuffer) = 0;
	virtual bool GetButtonImage(cIGZBuffer*& imageBuffer) = 0;
	virtual bool SetButtonImageArea(cRZRect const& imageArea) = 0;
	virtual bool GetButtonImageArea(cRZRect& imageArea) = 0;

	virtual bool SetFont(cIGZFont* font) = 0;
	virtual bool SetFontStyle(uint32_t style) = 0;
	virtual bool GetFontStyle(uint32_t& style) = 0;

	virtual bool SetFontColor(tFontColorIdx index, cRZColor color) = 0;
	virtual bool SetFontColor(tFontColorIdx index, uint32_t color) = 0;
	virtual bool GetFontColor(tFontColorIdx index, cRZColor& color) = 0;
	virtual bool GetFontColor(tFontColorIdx index, uint32_t& color) = 0;
	virtual bool ClearFontColor(tFontColorIdx index) = 0;

	virtual bool SetTextAlignment(tTextAlignment value) = 0;
	virtual bool GetTextAlignment(tTextAlignment& value) const = 0;
	virtual bool SetGutters(uint8_t unknown1, uint8_t unknown2) = 0;
	virtual bool GetGutters(uint8_t& unknown1, uint8_t& unknown2) const = 0;

	virtual bool SetOutlineColors(uint32_t outlineLeft, uint32_t outlineTop, uint32_t outlineRight, uint32_t outlineBottom) = 0;
	virtual bool GetOutlineColors(uint32_t& outlineLeft, uint32_t& outlineTop, uint32_t& outlineRight, uint32_t& outlineBottom) = 0;
	virtual bool SetOutlineColor(tOutlineIndex index, cRZColor const& color) = 0;
	virtual bool GetOutlineColor(tOutlineIndex index, cRZColor& color) = 0;
};