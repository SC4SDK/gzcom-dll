/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cIGZSystemService.h
 *
 * Copyright (C) 2016 Nelson Gomez
 * Copyright (C) 2023, 2024, 2026 Nicholas Hayes
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

static const uint32_t GZIID_cIGZSystemService = 0x287fb697;

/**
 * @brief An interface for services that provide helpers and run on ticks
 *
 * Services can be used for two purposes. First, it can be used for an object
 * that needs to perform some sort of action on active or idle ticks.
 * Secondly, it can be used to provide a helper object to other directors such
 * that by getting the service by its ID, it can be cast to its actual class
 * type to use any methods provided by it.
 */
class cIGZSystemService : public cIGZUnknown
{
	public:
		/**
		 * @return A unique GUID identifying this service for retrieval
		 */
		virtual uint32_t GetServiceID(void) = 0;

		/**
		 * @brief Sets an ID for this service
		 * @param dwServiceId The ID to give this service
		 * @return The "this" pointer
		 */
		virtual void SetServiceID(uint32_t dwServiceId) = 0;

		/**
		 * @return This service's priority. Lower values yield more priority
		 */
		virtual int32_t GetServicePriority(void) = 0;

		/**
		 * @return Whether the service is running, as a boolean
		 */
		virtual bool IsServiceRunning(void) = 0;

		/**
		 * @brief Toggles whether or not the service is currently running
		 * @return The "this" pointer
		 */
		virtual void SetServiceRunning(bool bRunning) = 0;

		/**
		 * @brief A callback for post-framework initialization
		 */
		virtual bool Init(void) = 0;

		/**
		 * @brief A callback for pre-framework shutdown
		 */
		virtual bool Shutdown(void) = 0;

		/**
		 * @brief A callback for each active tick when the game is focused
		 *
		 * The service must be registered to receive active tick callbacks via
		 * cIGZFrameWork::AddToTick(cIGZSystemService* pService)
		 */
		virtual bool OnTick(uint32_t unknown1) = 0;

		/**
		 * @brief A callback for each idle tick when the game is not focused
		 *
		 * The service must be registered to receive idle tick callbacks via
		 * cIGZFrameWork::AddToOnIdle(cIGZSystemService* pService)
		 */
		virtual bool OnIdle(uint32_t unknown1) = 0;

		/**
		 * @return This service's tick priority. Lower values yield more priority
		 */
		virtual int32_t GetServiceTickPriority() = 0;
};