/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * SC4AutoGamePause.cpp
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

#include "SC4AutoGamePause.h"
#include "cIGZGraphicSystem.h"
#include "cISC424HourClock.h"
#include "cISC4App.h"
#include "cISC4AnimationTickManager.h"
#include "cISC4City.h"
#include "cISC4Simulator.h"
#include "GZServPtrs.h"

namespace
{
	void PauseGame(bool pause, bool pauseDraw, bool pauseAnimation, bool pauseSimulation, bool pause24HourClock)
	{
		if (pauseDraw)
		{
			cIGZGraphicSystemPtr graphicSystem;

			if (graphicSystem)
			{
				if (pause)
				{
					graphicSystem->PauseDraw();
				}
				else
				{
					graphicSystem->UnpauseDraw();
				}
			}
		}

		if (pauseAnimation)
		{
			cISC4AnimationTickManagerPtr animationSystem;

			if (animationSystem)
			{
				animationSystem->PauseAnimationSystem(pause);
			}
		}

		if (pauseSimulation)
		{
			cISC4SimulatorPtr simulator;

			if (simulator)
			{
				if (pause)
				{
					simulator->HiddenPause();
				}
				else
				{
					simulator->HiddenResume();
				}
			}
		}

		if (pause24HourClock)
		{
			cISC4AppPtr sc4App;

			if (sc4App)
			{
				cISC4City* pCity = sc4App->GetCity();

				if (pCity)
				{
					cISC424HourClock* pClock = pCity->Get24HourClock();

					if (pClock)
					{
						pClock->HiddenPause(pause);
					}
				}
			}
		}
	}
}

SC4AutoGamePause::SC4AutoGamePause(bool pauseDraw, bool pauseAnimation, bool pauseSimulation, bool pause24HourClock)
	: pauseDraw(pauseDraw), pauseAnimation(pauseAnimation), pauseSimulation(pauseSimulation), pause24HourClock(pause24HourClock)
{
	PauseGame(true, pauseDraw, pauseAnimation, pauseSimulation, pause24HourClock);
}

SC4AutoGamePause::~SC4AutoGamePause()
{
	PauseGame(false, pauseDraw, pauseAnimation, pauseSimulation, pause24HourClock);
}
