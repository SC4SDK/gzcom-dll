#include "ScriptedDialogWinProcBase.h"
#include "cGZMessage.h"
#include "cIGZWin.h"
#include "cIGZWinBtn.h"
#include "cIGZWinGen.h"
#include "cIGZWinMgr.h"

ScriptedDialogWinProcBase::ScriptedDialogWinProcBase() : pWin(nullptr)
{
}

bool ScriptedDialogWinProcBase::DoWinProcMessage(cIGZWin* pWin, cGZMessage& msg)
{
	if (msg.dwMessageType == cIGZWin::tWinProcMessageTypes::Command)
	{
		return OnCommand(msg);
	}
	else if (msg.dwMessageType == cIGZWinGen::tWinProcMessageTypes::Attach)
	{
		this->pWin = pWin;
		OnAttach();
		return true;
	}
	else if (msg.dwMessageType == cIGZWinGen::tWinProcMessageTypes::Detach)
	{
		this->pWin = nullptr;
		OnDetach();
		return true;
	}

    return false;
}

void ScriptedDialogWinProcBase::CenterDialogInParentWindow()
{
	if (pWin)
	{
		cIGZWin* pParentWin = pWin->GetParentWin();

		if (pParentWin)
		{
			const int32_t parentWidth = pParentWin->GetW();
			const int32_t parentHeight = pParentWin->GetH();
			const int32_t dialogWidth = pWin->GetW();
			const int32_t dialogHeight = pWin->GetH();

			const int32_t newDialogX = (parentWidth - dialogWidth) / 2;
			const int32_t newDialogY = (parentHeight - dialogHeight) / 2;

			pWin->GZWinMoveTo(newDialogX, newDialogY);
		}
	}
}

void ScriptedDialogWinProcBase::EndDialog(uint32_t result)
{
	if (pWin && pWin->GetFlag(cIGZWin::WinFlag_Modal))
	{
		// The DialogEnd message uses the parameter format:  window pointer, result.
		pWin->GetWindowManager()->GZWinMsgPost(
			cIGZWin::tWinProcMessageTypes::DialogEnd,
			reinterpret_cast<uint32_t>(pWin),
			result);
	}
}

void ScriptedDialogWinProcBase::OnAttach()
{
	CenterDialogInParentWindow();
}

void ScriptedDialogWinProcBase::OnDetach()
{
}

void ScriptedDialogWinProcBase::OnButtonActivated(uint32_t buttonID)
{
	EndDialog(buttonID);
}

bool ScriptedDialogWinProcBase::OnCommand(cGZMessage& msg)
{
	if (msg.dwData1 == cIGZWinBtn::tBtnWinProcCommands::Activated)
	{
		OnButtonActivated(msg.dwData2);
		return true;
	}

	return false;
}
