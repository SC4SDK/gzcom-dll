/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cISC4ComponentEffect.h
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
#include "cISC4VisualEffect.h"

static const uint32_t GZIID_cISC4ComponentEffect = 0x2c279933;

// A part of a visual effect: particles, a decal, a sound, a camera move, ...
// Not a cIGZUnknown, AddRef and Release come last.
class cISC4ComponentEffect
{
public:
	virtual void Start(cISC4VisualEffect::tTransitionType type) = 0;
	virtual void Stop(cISC4VisualEffect::tTransitionType type) = 0;
	virtual bool IsStarted() const = 0;

	virtual void SetTransforms(cS3DTransform const& sourceTransform, cS3DTransform const& effectTransform) = 0;
	virtual void ApplyEffect(float deltaTime) = 0;

	virtual bool SetFloatParams(cISC4VisualEffect::tParamType paramType, float const* data, int dataCount) = 0;
	virtual bool SetVoidParams(cISC4VisualEffect::tParamType paramType, void** data, int dataCount) = 0;

	virtual uint32_t AddRef() = 0;
	virtual uint32_t Release() = 0;
};
