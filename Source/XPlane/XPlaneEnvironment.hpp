//
//  XPlanEnvironment.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 17/04/2023.
//

/*
 *   X-Plane 12 Plugin for Apple Silicon Computers
 *
 *   Copyright (C) 2024 Steve Proctor <swp336@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 *   My thanks to AviTab developer Folke Will <folko@solhost.org> for
 *   releasing the AviTab code as open source.  It gave me a working example
 *   of an X-Plane plugin that helped jump-start my own X-Plane coding journey
 */

#ifndef XPlanEnvironment_h
#define XPlanEnvironment_h

#include "XPlane.hpp"
#include "BravoLights.hpp"
#include "BravoControls.hpp"

extern std::shared_ptr<XPlane> xplane;
extern std::shared_ptr<BravoLights> lights;
extern std::shared_ptr<BravoControls> controls;

#endif /* XPlanEnvironment_h */
