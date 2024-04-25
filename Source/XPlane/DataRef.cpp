

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

#include <stdexcept>
#include "DataRef.h"

/*

template<typename T>
DataRef<T>::DataRef(const std::string& name) {
    handle = XPLMFindDataRef(name.c_str());
//    if (!handle) {
//        throw std::runtime_error("Invalid DataRef: " + name);
//    }
}

template<typename T>
DataRef<T>::DataRef(const std::string& name, T defaultValue) {
    handle = XPLMFindDataRef(name.c_str());
//    if (!handle) {
//        logger::warn("DataRef '%s' not available, using defaults");
//        overrideValue = defaultValue;
//    }
}

template<>
DataRef<int>::operator int() {
    if (handle) {
        return XPLMGetDatai(handle);
    } else {
        return overrideValue;
    }
}

template<>
DataRef<bool>::operator bool() {
    if (handle) {
        return XPLMGetDatai(handle) != 0;
    } else {
        return overrideValue;
    }
}

template<>
DataRef<float>::operator float() {
    if (handle) {
        return XPLMGetDataf(handle);
    } else {
        return overrideValue;
    }
}

template class DataRef<int>;
template class DataRef<bool>;
template class DataRef<float>;

*/


DataRef::DataRef(const char* dataRefName) {
    
    dataRefInfo = new XPLMDataRefInfo_t;
    dataRefInfo -> structSize = sizeof(XPLMDataRefInfo_t);

    if (dataRefName != NULL)
        dataRef = XPLMFindDataRef(dataRefName);
    else dataRef = NULL;
    
    if (dataRef != NULL) {
        XPLMGetDataRefInfo(dataRef, dataRefInfo);
        
        switch (dataRefInfo -> type) {
            case xplmType_Unknown: _dataType = XPUnknown; break;
            case xplmType_Int: _dataType = XPInt; break;
            case xplmType_Float: _dataType = XPFloat; break;
            case xplmType_Double: _dataType = XPDouble; break;
            case xplmType_FloatArray: _dataType = XPFloatArray; break;
            case xplmType_IntArray: _dataType = XPIntArray; break;
            case xplmType_Data: _dataType = XPDataBlock; break;
            case 7: _dataType = XPMulti; break;        // free to choose between int, float or double.  This particular dataref supports all three
            default: _dataType = XPUnknown; break;
        }
        getData();
    } else _dataType = XPUnknown;
}

DataRef::~DataRef() {
}


XPDataValue DataRef::dataValue() {
    getData();
    return _dataValue;
}

const char * DataRef::dataRefName() {
    if (dataRef != NULL)
        return dataRefInfo -> name;
    else return NULL;
}

XPDataType DataRef::dataType() {
    return _dataType;
}

int DataRef::dataArraySize() {
    return _arraySize;
}

void DataRef::getData() {
    
    if (dataRef != NULL) {
        switch (_dataType) {
            case XPUnknown: _dataValue.intValue = 0; break;
            case XPInt: _dataValue.intValue = XPLMGetDatai(dataRef); break;
            case XPFloat: _dataValue.floatValue = XPLMGetDataf(dataRef); break;
            case XPDouble: _dataValue.doubleValue = XPLMGetDatad(dataRef); break;
            case XPFloatArray: _arraySize = XPLMGetDatavf(dataRef, _dataValue.floatArray, 0, XPMaxArraySize); break;
            case XPIntArray: _arraySize = XPLMGetDatavi(dataRef, _dataValue.intArray, 0, XPMaxArraySize); break;
            case XPDataBlock: _arraySize = XPLMGetDatab(dataRef, _dataValue.dataBlock, 0, XPMaxDataBlockSize); break;
            case XPMulti: { _dataValue.intValue = XPLMGetDatai(dataRef); _dataValue.floatValue = XPLMGetDataf(dataRef); _dataValue.doubleValue = XPLMGetDatad(dataRef); } break;
        }
    } else _dataValue.intValue = 0;  // NULL ref, so type already set to 'XPUnKnown'  for extra safety set a valid first byte.
}
