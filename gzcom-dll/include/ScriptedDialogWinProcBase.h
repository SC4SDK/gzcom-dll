/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * ScriptedDialogWinProcBase.h
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
#include "cRZBaseWinProc.h"
#include "cGZPersistResourceKey.h"

// A base class for IGZWinGen dialog box window procedures.
// 
// Derived classes can customize its behavior by overriding the virtual
// methods for things like initialization or handing more control types.
// 
// See NotificationDialogWinProc in SC4UI.cpp for an example implementation
// and ShowNotificationDialog in the same file for the usage pattern.

class ScriptedDialogWinProcBase : public cRZBaseWinProc
{
public:
	// The constructor is public because the default behavior of this class is
	// appropriate for 'generic' scripted modal windows.
	// A generic' scripted modal window:
	// 
	// 1. Is centered in the parent window.
	// 2. Closes when any of its buttons are clicked.
	// 3. Does not require any initialization or customization in the window procedure.
	
	ScriptedDialogWinProcBase();

protected:
	// Can be overridden to customize the message handling.
	virtual bool DoWinProcMessage(cIGZWin* pWin, cGZMessage& pMsg) override;

	// Centers the dialog in the parent window.
	void CenterDialogInParentWindow();
	// Closes the dialog with the specified result value.
	// The result value will be returned by cIGZWinMgr::DoModalWin.
	void EndDialog(uint32_t result);

	// Called when the window procedure is attached to the dialog.
	// The default implementation calls CenterDialogInParentWindow.
	virtual void OnAttach();
	// Called when the window procedure is set to NULL.
	// Can be overridden to perform shutdown for the dialog.
	virtual void OnDetach();
	// Called when a dialog button is clicked.
	// The default implementation calls EndDialog with the specified button id.
	virtual void OnButtonActivated(uint32_t buttonID);
	// Called for the cIGZWin Command message code (3).
	// The default implementation handles button clicks by calling OnButtonActivated.
	virtual bool OnCommand(cGZMessage& msg);

	cIGZWin* pWin;
};

