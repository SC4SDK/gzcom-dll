/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * SC4UI.cpp
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

#include "SC4UI.h"
#include "cIGZUIScriptService.h"
#include "cIGZWin.h"
#include "cIGZWinBtn.h"
#include "cIGZWinGen.h"
#include "cIGZWinMgr.h"
#include "cIGZWinProc.h"
#include "cIGZWinText.h"
#include "cISC4App.h"
#include "GZServPtrs.h"
#include "ScriptedDialogWinProcBase.h"
#include "SC4AutoGamePause.h"

namespace
{
	class ConfirmationDialogWinProc : public ScriptedDialogWinProcBase
	{
	public:
		static constexpr int32_t kAcceptButtonID = 0x8a8dfd4e;
		static constexpr int32_t kCancelButtonID = 0x8a8dfd4a;

		ConfirmationDialogWinProc(
			const cIGZString& message,
			const cIGZString& caption,
			const cIGZString* acceptButtonText,
			const cIGZString* cancelButtonText)
			: message(message), caption(caption), acceptButtonText(), cancelButtonText()
		{
			if (acceptButtonText)
			{
				this->acceptButtonText.FromChar(acceptButtonText->ToChar(), acceptButtonText->Strlen());
			}

			if (cancelButtonText)
			{
				this->cancelButtonText.FromChar(cancelButtonText->ToChar(), cancelButtonText->Strlen());
			}
		}

		ConfirmationDialogWinProc(
			const std::string_view& message,
			const std::string_view& caption,
			const std::string_view* acceptButtonText,
			const std::string_view* cancelButtonText)
			: message(message), caption(caption), acceptButtonText(), cancelButtonText()
		{
			if (acceptButtonText)
			{
				this->acceptButtonText.FromChar(acceptButtonText->data(), static_cast<uint32_t>(acceptButtonText->size()));
			}

			if (cancelButtonText)
			{
				this->cancelButtonText.FromChar(cancelButtonText->data(), static_cast<uint32_t>(cancelButtonText->size()));
			}
		}

		void OnAttach() override
		{
			CenterDialogInParentWindow();

			cRZAutoRefCount<cIGZWinText> captionWin;

			if (pWin->GetChildAsRecursive(kCaptionWinID, GZIID_cIGZWinText, captionWin.AsPPVoid()))
			{
				captionWin->SetCaption(caption);
			}

			cRZAutoRefCount<cIGZWinText> messageWin;

			if (pWin->GetChildAsRecursive(kMessageWinID, GZIID_cIGZWinText, messageWin.AsPPVoid()))
			{
				messageWin->SetCaption(message);
			}

			if (acceptButtonText.Strlen() > 0)
			{
				cRZAutoRefCount<cIGZWinBtn> button;

				if (pWin->GetChildAsRecursive(static_cast<uint32_t>(kAcceptButtonID), GZIID_cIGZWinBtn, button.AsPPVoid()))
				{
					button->SetCaption(acceptButtonText);
				}
			}

			if (cancelButtonText.Strlen() > 0)
			{
				cRZAutoRefCount<cIGZWinBtn> button;

				if (pWin->GetChildAsRecursive(static_cast<uint32_t>(kCancelButtonID), GZIID_cIGZWinBtn, button.AsPPVoid()))
				{
					button->SetCaption(cancelButtonText);
				}
			}
		}

	private:
		static constexpr uint32_t kCaptionWinID = 0x8a91e4fd;
		static constexpr uint32_t kMessageWinID = 0x6a8cc495;

		cRZBaseString caption;
		cRZBaseString message;
		cRZBaseString acceptButtonText;
		cRZBaseString cancelButtonText;
	};

	class NotificationDialogWinProc : public ScriptedDialogWinProcBase
	{
	public:
		NotificationDialogWinProc(const cIGZString& message, const cIGZString& caption)
			: message(message), caption(caption)
		{
		}

		NotificationDialogWinProc(const std::string_view& message, const std::string_view& caption)
			: message(message), caption(caption)
		{
		}

		void OnAttach() override
		{
			CenterDialogInParentWindow();

			cRZAutoRefCount<cIGZWinText> captionWin;

			if (pWin->GetChildAsRecursive(kCaptionWinID, GZIID_cIGZWinText, captionWin.AsPPVoid()))
			{
				captionWin->SetCaption(caption);
			}

			cRZAutoRefCount<cIGZWinText> messageWin;

			if (pWin->GetChildAsRecursive(kMessageWinID, GZIID_cIGZWinText, messageWin.AsPPVoid()))
			{
				messageWin->SetCaption(message);
			}
		}

	private:
		static constexpr uint32_t kCaptionWinID = 0xca8cc4b6;
		static constexpr uint32_t kMessageWinID = 0x4a8cc4a9;

		cRZBaseString caption;
		cRZBaseString message;
	};
}

cIGZWin* SC4UI::CreateWindowFromScript(const cGZPersistResourceKey& key, cIGZWin* parent, uint32_t windowClsid)
{
	cIGZUIScriptServicePtr pUIScriptService;

	if (pUIScriptService)
	{
		return pUIScriptService->CreateWindowFromScript(key, parent, windowClsid);
	}

	return nullptr;
}

bool SC4UI::CreateWindowFromScript(
	const cGZPersistResourceKey& key,
	cIGZWin* parent,
	uint32_t windowClsid,
	uint32_t riid,
	void** ppvObj)
{
	cIGZUIScriptServicePtr pUIScriptService;

	if (pUIScriptService)
	{
		return pUIScriptService->CreateWindowFromScript(key, parent, windowClsid, riid, ppvObj);
	}

	return false;
}

bool SC4UI::GetPopupModalDialogsEnabled()
{
	bool result = false;

	cISC4AppPtr pSC4App;

	if (pSC4App)
	{
		result = pSC4App->GetPopupDialogsEnabled();
	}

	return result;
}

cRZAutoRefCount<cISC4View3DWin> SC4UI::GetView3DWin()
{
	cRZAutoRefCount<cISC4View3DWin> view3D;

	cISC4AppPtr pSC4App;

	if (pSC4App)
	{
		cIGZWin* mainWindow = pSC4App->GetMainWindow();

		if (mainWindow)
		{
			const uint32_t kGZWin_WinSC4App = 0x6104489a;
			const uint32_t kGZWin_SC4View3DWin = 0x9a47b417;

			cIGZWin* pParentWin = mainWindow->GetChildWindowFromID(kGZWin_WinSC4App);

			if (pParentWin)
			{
				cRZAutoRefCount<cISC4View3DWin> temp;

				if (pParentWin->GetChildAs(
					kGZWin_SC4View3DWin,
					kGZIID_cISC4View3DWin,
					temp.AsPPVoid()))
				{
					view3D = std::move(temp);
				}
			}
		}
	}

	return view3D;
}

int32_t SC4UI::ShowScriptedModalDialog(const cGZPersistResourceKey& key, uint32_t windowClsid)
{
	// The base window procedure behavior is appropriate for 'generic' dialog boxes that don't require other setup.
	// The dialog box will appear in the center of the screen and close on any button click.

	cRZAutoRefCount<cIGZWinProc> winProc(new ScriptedDialogWinProcBase(), cRZAutoRefCount<cIGZWinProc>::kAddRef);

	return ShowScriptedModalDialog(key, windowClsid, winProc);
}

int32_t SC4UI::ShowScriptedModalDialog(cIGZWin* parent, const cGZPersistResourceKey& key, uint32_t windowClsid)
{
	// The base window procedure behavior is appropriate for 'generic' dialog boxes that don't require other setup.
	// The dialog box will appear in the center of the screen and close on any button click.

	cRZAutoRefCount<cIGZWinProc> winProc(new ScriptedDialogWinProcBase(), cRZAutoRefCount<cIGZWinProc>::kAddRef);

	return ShowScriptedModalDialog(parent, key, windowClsid, winProc);
}

int32_t SC4UI::ShowScriptedModalDialog(const cGZPersistResourceKey& key, uint32_t windowClsid, cIGZWinProc* winProc)
{
	cIGZWinMgrPtr pWinMgr;

	return ShowScriptedModalDialog(pWinMgr, pWinMgr->GetMainWindow(), key, windowClsid, winProc);
}

int32_t SC4UI::ShowScriptedModalDialog(cIGZWin* parent, const cGZPersistResourceKey& key, uint32_t windowClsid, cIGZWinProc* winProc)
{
	cIGZWinMgrPtr pWinMgr;

	return ShowScriptedModalDialog(pWinMgr, parent, key, windowClsid, winProc);
}

int32_t SC4UI::ShowScriptedModalDialog(cIGZWinMgr* winMgr, cIGZWin* parent, const cGZPersistResourceKey& key, uint32_t windowClsid, cIGZWinProc* winProc)
{
	int32_t result = kModalDialogError;

	if (winMgr && parent && winProc && GetPopupModalDialogsEnabled())
	{
		SC4AutoGamePause autoGamePause(false, false, true, true);
		cRZAutoRefCount<cIGZWinGen> dialog;

		if (CreateWindowFromScript(key, parent, windowClsid, GZIID_cIGZWinGen, dialog.AsPPVoid()))
		{
			cIGZWin* pPreviousFocusTarget = winMgr->GZGetFocus();
			cIGZWin* pDialogAsIGZWin = dialog->AsIGZWin();

			dialog->SetWinProc(winProc);

			pDialogAsIGZWin->PullToFront();
			result = winMgr->DoModalWin(pDialogAsIGZWin);

			dialog->SetWinProc(nullptr);

			winMgr->DestroyWindow(pDialogAsIGZWin);

			if (winMgr->IsWindowValid(pPreviousFocusTarget))
			{
				winMgr->GZSetFocus(pPreviousFocusTarget);
			}
		}
	}

	return result;
}

SC4UI::ConfirmationDialogButton SC4UI::ShowConfirmationDialog(const cIGZString& message, const cIGZString& caption, const cIGZString* acceptButtonText, const cIGZString* cancelButtonText)
{
	ConfirmationDialogButton button = ConfirmationDialogButton::Cancel;

	cRZAutoRefCount<cIGZWinProc> winProc(new ConfirmationDialogWinProc(message, caption, acceptButtonText, cancelButtonText), cRZAutoRefCount<cIGZWinProc>::kAddRef);

	const int32_t result = ShowScriptedModalDialog(cGZPersistResourceKey(0, 0x96a006b0, 0xea8cc3c6), 0x8a8dfcf5, winProc);

	if (result == ConfirmationDialogWinProc::kAcceptButtonID)
	{
		button = ConfirmationDialogButton::Accept;
	}

	return button;
}

SC4UI::ConfirmationDialogButton SC4UI::ShowConfirmationDialog(const std::string_view& message, const std::string_view& caption, const std::string_view* acceptButtonText, const std::string_view* cancelButtonText)
{
	ConfirmationDialogButton button = ConfirmationDialogButton::Cancel;

	cRZAutoRefCount<cIGZWinProc> winProc(new ConfirmationDialogWinProc(message, caption, acceptButtonText, cancelButtonText), cRZAutoRefCount<cIGZWinProc>::kAddRef);

	const int32_t result = ShowScriptedModalDialog(cGZPersistResourceKey(0, 0x96a006b0, 0xea8cc3c6), 0x8a8dfcf5, winProc);

	if (result == ConfirmationDialogWinProc::kAcceptButtonID)
	{
		button = ConfirmationDialogButton::Accept;
	}

	return button;
}

void SC4UI::ShowNotificationDialog(const cIGZString& message, const cIGZString& caption)
{
	cRZAutoRefCount<cIGZWinProc> winProc(new NotificationDialogWinProc(message, caption), cRZAutoRefCount<cIGZWinProc>::kAddRef);

	ShowScriptedModalDialog(cGZPersistResourceKey(0, 0x96a006b0, 0xca8cbf0f), 0xaa8def97, winProc);
}

void SC4UI::ShowNotificationDialog(const std::string_view& message, const std::string_view& caption)
{
	cRZAutoRefCount<cIGZWinProc> winProc(new NotificationDialogWinProc(message, caption), cRZAutoRefCount<cIGZWinProc>::kAddRef);

	ShowScriptedModalDialog(cGZPersistResourceKey(0, 0x96a006b0, 0xca8cbf0f), 0xaa8def97, winProc);
}
