/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cISC4EffectsCollection.h
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

class cISC4ComponentDescription;
class cSC4CameraParams;
class cSC4DecalDescription;
class cSC4DynamicParticleDescription;
class cSC4EffectDescription;
class cSC4LightDescription;
class cSC4MessageTriggerDescription;
class cSC4ParticlesDescription;
class cSC4ShakeDescription;

static const uint32_t GZIID_cISC4EffectsCollection = 0xc97cf5ce;

class cISC4EffectsCollection : public cIGZUnknown
{
public:
	virtual void BeginCollection() = 0;
	virtual void EndCollection() = 0;
	virtual void AddEffectDescription(char const*, cSC4EffectDescription const&) = 0;
	virtual bool GetEffectDescription(char const*, cSC4EffectDescription*) = 0;
	virtual void AddParticleDescription(char const*, cSC4ParticlesDescription const&) = 0;
	virtual bool GetParticleDescription(char const*, cSC4ParticlesDescription*) = 0;
	virtual void AddDynamicParticleDescription(char const*, cSC4DynamicParticleDescription const&) = 0;
	virtual bool GetDynamicParticleDescription(char const*, cSC4DynamicParticleDescription*) = 0;
	virtual void AddDecalDescription(char const*, cSC4DecalDescription const&) = 0;
	virtual bool GetDecalDescription(char const*, cSC4DecalDescription*) = 0;
	virtual void AddShakeDescription(char const*, cSC4ShakeDescription const&) = 0;
	virtual bool GetShakeDescription(char const*, cSC4ShakeDescription*) = 0;
	virtual void AddLightDescription(char const*, cSC4LightDescription const&) = 0;
	virtual bool GetLightDescription(char const*, cSC4LightDescription*) = 0;
	virtual int32_t AddComponentDescription(char const*, cISC4ComponentDescription*) = 0;
	virtual bool GetComponentDescription(char const*, uint32_t, cISC4ComponentDescription**) = 0;
	virtual void SetCameraParams(cSC4CameraParams const&) = 0;
	virtual void AddEffectBinding(char const*, uint32_t, uint32_t) = 0;
	virtual void AddMessageTrigger(cSC4MessageTriggerDescription const&) = 0;
	virtual bool UpdateEffectPriority(char const*, uint32_t, char const*) = 0;
};
