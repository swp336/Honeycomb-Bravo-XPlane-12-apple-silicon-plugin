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


#ifndef SRC_ENVIRONMENT_XPLANE_DATAREF_H_
#define SRC_ENVIRONMENT_XPLANE_DATAREF_H_

#include <XPLMDataAccess.h>
#include <string>

/*
template<typename T>
class DataRef final {
public:
    DataRef(const std::string& name);
    DataRef(const std::string& name, T defaultValue);

    operator T();
private:
    T overrideValue{};
    XPLMDataRef handle = nullptr;
};

*/

enum XPDataType { XPUnknown, XPInt, XPFloat, XPDouble, XPFloatArray, XPIntArray, XPDataBlock, XPMulti };

const int XPMaxArraySize = 16;
const int XPMaxDataBlockSize = 64;

union XPDataValue {
    int intValue;
    float floatValue;
    double doubleValue;
    float floatArray[XPMaxArraySize];
    int intArray[XPMaxArraySize];
    char dataBlock[XPMaxDataBlockSize];
};

class DataRef {

public:
    DataRef(const char* dataRefName);
    ~DataRef();
    XPDataType dataType();
    int dataArraySize();
    XPDataValue dataValue();
    const char * dataRefName();
    
protected:
    XPLMDataRef dataRef;
    XPLMDataRefInfo_t* dataRefInfo;
    XPDataType _dataType;
    XPDataValue _dataValue;
    int _arraySize;
    void getData();
};

#endif /* SRC_ENVIRONMENT_XPLANE_DATAREF_H_ */
