/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cIS3DResModel.h
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
#include "cIGZUnknown.h"

class cIS3DMeshAndMaterial;
class cIS3DModelInstance;
class cIS3DModelInstanceAnimated;
class cS3DAnimInfo;
class cS3DBoundingBox;
class cS3DModelData;

static const uint32_t GZIID_cIS3DResModel = 0x9ad0e7e3;

class cIS3DResModel : public cIGZUnknown
{
public:
	virtual const cS3DAnimInfo* GetAnimInfo() const = 0;
	virtual bool GetModelInstance(uint32_t, cIS3DModelInstance**) = 0;
	virtual bool GetModelInstance(uint32_t, cIS3DModelInstanceAnimated**) = 0;
	virtual bool GetMeshAndMaterial(uint32_t, cIS3DMeshAndMaterial**) = 0;
	virtual void GetModelBounds(cS3DBoundingBox&) const = 0;
	virtual bool GetModelFrame(uint32_t, cS3DModelData*) const = 0;
};
