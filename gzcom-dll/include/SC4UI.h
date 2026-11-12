/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * SC4UI.h
 *
 * Copyright (C) 2024, 2025, 2026 Nicholas Hayes
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
#include "cISC4View3DWin.h"
#include "cRZAutoRefCount.h"
#include <cstdint>
#include <string_view>

class cGZPersistResourceKey;
class cIGZWin;
class cIGZWinMgr;
class cIGZWinProc;
struct StringResourceKey;

namespace SC4UI
{
	// The error return value used by cIGZWinMgr::DoModalWin.
	static constexpr int32_t kModalDialogError = 0x80000000;

	/**
	 * @brief Creates a window from the specified scripted window resource.
	 * @param key The scripted window resource key.
	 * @param parent The parent window.
	 * @param windowClsid The scripted window class id.
	 * @return A pointer to the created window; otherwise, null if it could not be created.
	 */
	cIGZWin* CreateWindowFromScript(const cGZPersistResourceKey& key, cIGZWin* parent, uint32_t windowClsid);

	/**
	 * @brief Creates a window from the specified scripted window resource.
	 * @param key The scripted window resource key.
	 * @param parent The parent window.
	 * @param windowClsid The scripted window class id.
	 * @param riid The interface id that the object should be cast to.
	 * @param ppvObj The output object.
	 * @return True if the window was created and cast to the specified interface; otherwise, false.
	 */
	bool CreateWindowFromScript(
		const cGZPersistResourceKey& key,
		cIGZWin* parent,
		uint32_t windowClsid,
		uint32_t riid,
		void** ppvObj);

	/**
	 * @brief Gets a value that indicates if popup modal dialog boxes are enabled.
	 * @return A value indicating if popup modal dialog boxes are enabled.
	 */
	bool GetPopupModalDialogsEnabled();
	/**
	 * @brief Gets the gets the city view window.
	 * @return 
	 */
	cRZAutoRefCount<cISC4View3DWin> GetView3DWin();

	/**
	 * @brief Displays a scripted window as a modal dialog.
	 * The dialog will be displayed in the center of the game window, and close on the first button click.
	 * @param key The scripted window resource key.
	 * @param windowClsid The scripted window class id.
	 * @return The id of the button that was clicked or kModalDialogError.
	 */
	int32_t ShowScriptedModalDialog(const cGZPersistResourceKey& key, uint32_t windowClsid);
	/**
	 * @brief Displays a scripted window as a modal dialog.
	 * The dialog will be displayed in the center of the game window, and close on the first button click.
	 * @param parent The parent window.
	 * @param key The scripted window resource key.
	 * @param windowClsid The scripted window class id.
	 * @return The id of the button that was clicked or kModalDialogError.
	 */
	int32_t ShowScriptedModalDialog(cIGZWin* parent, const cGZPersistResourceKey& key, uint32_t windowClsid);
	/**
	 * @brief Displays a scripted window as a modal dialog.
	 * @param key The scripted window resource key.
	 * @param windowClsid The scripted window class id.
	 * @param winProc The dialog window procedure.
	 * @return The id of the button that was clicked or kModalDialogError.
	 */
	int32_t ShowScriptedModalDialog(const cGZPersistResourceKey& key, uint32_t windowClsid, cIGZWinProc* winProc);
	/**
	 * @brief Displays a scripted window as a modal dialog.
	 * @param parent The parent window.
	 * @param key The scripted window resource key.
	 * @param windowClsid The scripted window class id.
	 * @param winProc The dialog window procedure.
	 * @return The id of the button that was clicked or kModalDialogError.
	 */
	int32_t ShowScriptedModalDialog(cIGZWin* parent, const cGZPersistResourceKey& key, uint32_t windowClsid, cIGZWinProc* winProc);
	/**
	 * @brief Displays a scripted window as a modal dialog.
	 * @param winMgr The window manager pointer.
	 * @param parent The parent window.
	 * @param key The scripted window resource key.
	 * @param windowClsid The scripted window class id.
	 * @param winProc The dialog window procedure.
	 * @return The id of the button that was clicked or kModalDialogError.
	 */
	int32_t ShowScriptedModalDialog(cIGZWinMgr* winMgr, cIGZWin* parent, const cGZPersistResourceKey& key, uint32_t windowClsid, cIGZWinProc* winProc);

	enum class ConfirmationDialogButton : int32_t
	{
		Accept = 0,
		Cancel
	};

	/**
	 * @brief Shows an Accept/Cancel style confirmation dialog.
	 * @param message The message.
	 * @param caption The caption.
	 * @param acceptButtonText An optional override for the game's default accept button text.
	 * @param cancelButtonText An optional override for the game's default cancel button text.
	 * @return The button that was clicked.
	 */
	ConfirmationDialogButton ShowConfirmationDialog(const cIGZString& message, const cIGZString& caption, const cIGZString* acceptButtonText = nullptr, const cIGZString* cancelButtonText = nullptr);
	/**
	 * @brief Shows an Accept/Cancel style confirmation dialog.
	 * @param message The message.
	 * @param caption The caption.
	 * @param acceptButtonText An optional override for the game's default accept button text.
	 * @param cancelButtonText An optional override for the game's default cancel button text.
	 * @return The button that was clicked.
	 */
	ConfirmationDialogButton ShowConfirmationDialog(const std::string_view& message, const std::string_view& caption, const std::string_view* acceptButtonText = nullptr, const std::string_view* cancelButtonText = nullptr);
	
	/**
	 * @brief Shows a notification dialog with an OK button.
	 * @param message The message.
	 * @param caption The caption.
	 */
	void ShowNotificationDialog(const cIGZString& message, const cIGZString& caption);
	/**
	 * @brief Shows a notification dialog with an OK button.
	 * @param message The message.
	 * @param caption The caption.
	 */
	void ShowNotificationDialog(const std::string_view& message, const std::string_view& caption);
	/**
	 * @brief Shows a notification dialog with an OK button.
	 * @param message The message string resource key.
	 * @param caption The caption string resource key.
	 */
	void ShowNotificationDialog(const StringResourceKey& messageKey, const StringResourceKey& captionKey);
}
