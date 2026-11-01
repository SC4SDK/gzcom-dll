/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * cIGZCommandServer.h
 *
 * Copyright (C) 2018 Nelson Gomez
 * Copyright (C) 2025, 2026 Nicholas Hayes
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
#include <vector>
#include "cIGZString.h"
#include "cIGZUnknown.h"

class cIGZCommandDispatcher;
class cIGZCommandGenerator;
class cIGZCommandParameterSet;

template <typename T> class SC4Vector;

class cIGZCommandServer : public cIGZUnknown
{
	public:
		struct cGZCommandInfo
		{
			uint32_t dwCommandID;
			char const *pszCommandName;
			char const *pszParameterInfo;
		};

		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual bool CreateCommandParameterSet(cIGZCommandParameterSet **ppParamSet) = 0;

		virtual bool RegisterCommand(uint32_t dwCommandID, char const *pszCommandName, char const *pszParameterInfo) = 0;
		virtual bool RegisterCommands(cGZCommandInfo *pCmdInfoArray, uint32_t dwCommandCount) = 0;
		virtual bool RegisterCommandParameterInfo(uint32_t dwCommandID, char const *pszParameterInfo) = 0;

		virtual bool UnregisterCommand(uint32_t dwCommandID) = 0;
		virtual bool UnregisterCommands(cGZCommandInfo *pCmdInfoArray, uint32_t dwCommandCount) = 0;

		virtual bool GetCommandInfo(uint32_t dwCommandID, cIGZString& szCommandNameOut, cIGZString& szParameterInfoOut) = 0;
		virtual uint32_t GetCommandID(cIGZString const& szCommandName) = 0;
		virtual uint32_t GetCommandIDFromCommandString(char const *pszCommandString, int32_t nStringLen) = 0;

		virtual bool EnumerateCommands(SC4Vector<uint32_t>& vecCommandIDs) = 0;

		virtual bool RegisterCommandGenerator(cIGZCommandGenerator *pCommandGen) = 0;
		virtual bool UnregisterCommandGenerator(cIGZCommandGenerator *pCommandGen) = 0;

		virtual cIGZCommandDispatcher* GetCommandDispatcher(void) = 0;
		virtual bool SetCommandDispatcher(cIGZCommandDispatcher* pCommandDispatcher) = 0;

		virtual int32_t ExecuteCommand(uint32_t dwCommandID, cIGZCommandParameterSet* pInput, cIGZCommandParameterSet* pOutput) = 0;
		virtual int32_t ExecuteCommand(char const *pszCommandString, uint32_t nStringLen, cIGZCommandParameterSet* pParamSet) = 0;
		virtual int32_t ExecuteCommandFormatted(char const *pszCommandFormat, cIGZCommandParameterSet *pParamUnknown, ...) = 0;

		virtual bool ConvertStringToCommand(char const *pszCommandString, uint32_t nStringLen, uint32_t& dwCommandIDOut, cIGZCommandParameterSet*& pParamSetOut) = 0;
		virtual bool ConvertCommandToString(uint32_t dwCommandID, cIGZCommandParameterSet *pParamSet, cIGZString& szStringOut) = 0;
		virtual bool ConvertCommandOutputToString(cIGZCommandParameterSet *pParamSet, cIGZString& szStringOut) = 0;
};