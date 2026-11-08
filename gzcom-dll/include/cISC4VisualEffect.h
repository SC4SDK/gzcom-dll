/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cISC4VisualEffect.h
 *
 * Copyright (C) 2025 Nicholas Hayes
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

class cS3DTransform;
class cS3DVector3;
class cISC4ComponentEffect;
class cISC4Occupant;

class cISC4VisualEffect : public cIGZUnknown
{
public:
	enum class tTransitionType : int32_t
	{
		Soft = 0,            // a stop lets the particles finish
		Hard = 1,            // immediate, -hard in the effect test command
		HardNoAncillary = 2, // Hard, without the effects manager's ancillary start/stop
	};

	// Bits for CheckEffectFlag, set by the switches on an effect in the .fx files.
	enum class tEffectFlag : uint32_t
	{
		ViewRelative = 0,      // follows the camera rotation
		NoAutoStop = 1,        // keeps running when all components are done
		HardStop = 2,          // Soft stops become Hard
		Rigid = 3,             // source and effect transforms are combined
		NoPropagate = 4,       // ignores SetFloatParams and SetVoidParams
		ApplyCursor = 5,       // gets the cursor ViewRay every tick
		IgnoreOrientation = 6, // drops the rotation
		NoLODStop = 7,
		ManualRestart = 8,
	};

	// Each component effect handles the parameters it knows and ignores the rest.
	// SetVectorParams counts vectors, SetFloatParams counts floats.
	enum class tParamType : uint32_t
	{
		Speed = 0x00,             // float, particle speed scale
		Size = 0x01,              // float, particle size scale
		Rate = 0x02,              // float, particle emission rate scale
		Alpha = 0x03,             // float, alpha scale
		Color = 0x04,             // 3 floats, RGB color scale
		Target = 0x05,            // vector, particle target position
		Texture = 0x06,           // void, cS3DTextureBinding* for decals
		Model = 0x07,             // void, cIS3DModelInstance* for model particles
		ExplosionCenter = 0x08,   // vector, geometry sourced particles only
		ViewRay = 0x09,           // 2 vectors, ray origin and direction
		AttractorPosition = 0x0a, // vector
		AttractorStrength = 0x0b, // float
		DecalRect = 0x0c,         // 4 floats, x1 z1 x2 z2 in world coordinates
		MessageData = 0x0d,       // void, sent along with scrubber messages, disasters pass themselves
		ClickRay = 0x0e,          // 2 vectors, query tool click ray for camera effects
		Velocity = 0x0f,          // vector, emitter velocity
		Occupant = 0x10,          // void, cISC4Occupant* that owns a dynamic particle
		LinkOccupant = 0x11,      // void, cISC4Occupant* whose dynamic particle to link to
		AttachSlaveEffect = 0x12, // 2 voids, attaches a slave effect to a dynamic particle

		// Only for cISC4ComponentEffect, the visual effect rejects these.
		CopyOffset = 0x101,       // float, index * spacing for repeated copies of a component
		LODScale = 0x102,         // 2 floats, emission rate and size scale for the LOD level
	};

	virtual void Start(tTransitionType type) = 0;
	virtual void Stop(tTransitionType type) = 0;
	virtual bool IsStarted() const = 0;
	virtual bool IsStopping() const = 0;

	virtual void SetEffectTransform(cS3DTransform const& transform) = 0;
	virtual void SetSourceTransform(cS3DTransform const& transform) = 0;

	virtual bool SetModelFromOccupant(cISC4Occupant* pOccupant) = 0;
	// Posted when the effect stops by itself, messageData goes in void1.
	virtual void SetFinishNotifyMessage(uint32_t messageType, uint32_t messageData) = 0;

	virtual bool SetVectorParams(tParamType paramType, cS3DVector3 const* data, int dataCount) = 0;
	virtual bool SetFloatParams(tParamType paramType, float const* data, int dataCount) = 0;
	virtual bool SetVoidParams(tParamType paramType, void** data, int dataCount) = 0;

	virtual void GetEffectTransform(cS3DTransform& transform) = 0;
	virtual void GetSourceTransform(cS3DTransform& transform) = 0;

	virtual bool AddComponentEffect(cISC4ComponentEffect* pEffect, cS3DTransform* pLocalTransform) = 0;

	virtual bool CheckEffectFlag(tEffectFlag flag) const = 0;
};