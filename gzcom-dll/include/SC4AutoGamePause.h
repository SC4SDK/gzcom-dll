/*
 * gzcom-dll - an open-source DLL Plugin SDK for SimCity 4
 *
 * SC4AutoGamePause.h
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

// A RAII helper class for temporarily pausing various game systems.
class SC4AutoGamePause
{
public:
	/** @brief Initializes the SC4AutoGamePause instance
	* @param[in] pauseDraw Pause the drawing system.
	* @param[in] pauseAnimation Pause the animation system.
	* @param[in] pauseSimulation Pause the city simulation.
	* @param[in] pause24HourClock Pause the city 24-hour clock. 
	*/
	SC4AutoGamePause(bool pauseDraw, bool pauseAnimation, bool pauseSimulation, bool pause24HourClock);
	~SC4AutoGamePause();
private:
	bool pauseDraw;
	bool pauseAnimation;
	bool pauseSimulation;
	bool pause24HourClock;
};
