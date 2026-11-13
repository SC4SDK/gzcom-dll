/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cRZUnknown.h
 *
 * Copyright (C) 2016 Nelson Gomez
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
#include <cassert>

 /**
  * @brief A base class for types that implement cIGZUnknown and delete
  * themselves when their reference count drops to zero.
  */
class cRZUnknown : public cIGZUnknown
{
	public:
		virtual ~cRZUnknown() {
		}

		/**
		* @brief Casts the object to the interface specified by riid. Override
		* this method to respond to queries for any additional interfaces that
		* you implement.
		* @param riid The GUID for the interface type to cast to.
		* @param ppvObj A pointer to a void pointer to store the result in.
		* @return Whether the object could be successfully cast or not.
		*/
		bool QueryInterface(uint32_t riid, void** ppvObj) override {
			if (riid == GZIID_cIGZUnknown) {
				*ppvObj = static_cast<cIGZUnknown*>(this);
				AddRef();
				return true;
			}
			else {
				*ppvObj = nullptr;
				return false;
			}
		}

		/**
		* @brief Adds a reference to this object.
		* @return The new reference count for this object.
		*/
		uint32_t AddRef(void) override {
			uint32_t localRefCount = mnRefCount + 1;
			mnRefCount = localRefCount;

			return localRefCount;
		}

		/**
		 * @brief Removes a reference to this object. When the reference
		 * count drops to zero the object will delete itself.
		 * @return The new reference count for this object.
		 */
		uint32_t Release(void) override {
			assert(mnRefCount > 0);

			uint32_t localRefCount = 0;

			if (mnRefCount > 0) {
				localRefCount = mnRefCount - 1;
				mnRefCount = localRefCount;

				if (localRefCount == 0)
				{
					delete this;
				}
			}

			return localRefCount;
		}
	protected:
		cRZUnknown() {
			mnRefCount = 0;
		}

		uint32_t mnRefCount;
};