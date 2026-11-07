/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * SC4DrawAttributes.h
 *
 * Copyright (C) 2026 Casper Van Gheluwe
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
#include <cstddef>
#include <cstdint>

class SC4DrawAttributes
{
	public:
		enum Flags : uint8_t
		{
			kHighlight = 0x01,           // draw highlightType over the model
			kApplyAlpha = 0x02,
			kSelfLit = 0x04,
			kDimByAlpha = 0x08,          // darken by alpha instead of blending, no highlight
			kNoDepth = 0x10,             // no depth test or write
			kDepthGreaterNoWrite = 0x20, // only drawn where something is in front of it
		};

		uint8_t flags;
		// Index into the highlight colors, render properties 0xEA639FB1 + n.
		// Lot placement uses 3 (blue) for valid and 4 (red) for invalid spots.
		uint8_t highlightType;
		uint16_t reserved;
		float color[3];
		float alpha;
};

static_assert(offsetof(SC4DrawAttributes, color) == 0x04);
static_assert(offsetof(SC4DrawAttributes, alpha) == 0x10);
static_assert(sizeof(SC4DrawAttributes) == 0x14);
