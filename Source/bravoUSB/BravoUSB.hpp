//
//  BravoUSB.hpp
//  BravoLights
//
//  Created by Steve Proctor on 05/06/2023.
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


#ifndef BravoUSB_hpp
#define BravoUSB_hpp

#include "hidapi.h"
#include <cstdint>

class BravoUSB {
    
public:
    BravoUSB();
    ~BravoUSB();
    
    void setLights(uint64_t thisMask);
    bool getCurrentSettings(unsigned char* data);
    
private:
    hid_device *bravoDevice;
};


#endif /* BravoUSB_hpp */
