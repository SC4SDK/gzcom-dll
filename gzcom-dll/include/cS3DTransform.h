/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cS3DTransform.h
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
#include "cS3DVector3.h"
#include <cstddef>
#include <cstdint>

// point' = scale * (rotation * point) + translation
class cS3DTransform
{
	public:
		enum Flags : uint8_t
		{
			kTranslation = 0x01,
			kScale = 0x02,
			kRotation = 0x04,
		};

		cS3DTransform() = default;

		explicit cS3DTransform(cS3DVector3 const& position)
			: changeCount(1), flags(kTranslation), translation(position)
		{
		}

		uint8_t changeCount = 0; // bumped on every change
		uint8_t flags = 0;       // 0 is the identity, the other fields are ignored
		float rotation[3][3] = { // [row][column], the columns are the rotated axes
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		cS3DVector3 translation;
		float scale = 1.0f;
};

static_assert(offsetof(cS3DTransform, flags) == 0x01);
static_assert(offsetof(cS3DTransform, rotation) == 0x04);
static_assert(offsetof(cS3DTransform, translation) == 0x28);
static_assert(offsetof(cS3DTransform, scale) == 0x34);
static_assert(sizeof(cS3DTransform) == 0x38);
