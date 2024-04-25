//
//  XPlane.cpp
//  Honeycomb
//
//  Created by Steve Proctor on 31/03/2023.
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

#include "XPlane.hpp"
#include <XPLMDataAccess.h>
#include <XPLMPlugin.h>


//void draw_about_box(XPLMWindowID in_window_id, void * in_refcon) {
    
    // Mandatory: We *must* set the OpenGL state before drawing
    // (we can't make any assumptions about it)
//    XPLMSetGraphicsState(
//                         0 /* no fog */,
//                         0 /* 0 texture units */,
//                         0 /* no lighting */,
//                         0 /* no alpha testing */,
//                         1 /* do alpha blend */,
//                         1 /* do depth testing */,
//                         0 /* no depth writing */
//                         );
        
//    int l, t, r, b;
//    XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);
     
//    float col_white[] = {1.0, 1.0, 1.0}; // red, green, blue
   
//    XPLMDrawString(col_white, l + 10, t - 20, (char *)"Hello world!", NULL, xplmFont_Proportional);
//}

//int dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon) { return 0; }
//XPLMCursorStatus dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void * in_refcon) { return xplm_CursorDefault; }
//int dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void * in_refcon) { return 0; }
//void dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void * in_refcon, int losing_focus) { }

//static XPLMWindowID g_window;
//XPLMCreateWindow_t params;


XPlane::XPlane() {
    aircraftRef = XPLMFindDataRef("sim/aircraft/view/acf_ui_name");
    XPLMEnableFeature("XPLM_USE_NATIVE_PATHS", 1);
    XPLMGetSystemPath(_xplaneDirectoryChar);
    _xplaneDirectoryString = _xplaneDirectoryChar;

    /*
    params.structSize = sizeof(params);
    params.visible = 1;
    params.drawWindowFunc = draw_about_box;
    params.handleMouseClickFunc = dummy_mouse_handler;
    params.handleRightClickFunc = dummy_mouse_handler;
    params.handleMouseWheelFunc = dummy_wheel_handler;
    params.handleKeyFunc = dummy_key_handler;
    params.handleCursorFunc = dummy_cursor_status_handler;
    params.refcon = NULL;
    params.layer = xplm_WindowLayerFloatingWindows;
    params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
    
    int left, bottom, right, top;
    XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
    params.left = left + 50;
    params.bottom = bottom + 150;
    params.right = params.left + 200;
    params.top = params.bottom + 200;
    
    g_window = XPLMCreateWindowEx(&params);
    
    XPLMSetWindowPositioningMode(g_window, xplm_WindowPositionFree, -1);
    // Limit resizing our window: maintain a minimum width/height of 100 boxels and a max width/height of 300 boxels
    XPLMSetWindowResizingLimits(g_window, 200, 200, 300, 300);
    XPLMSetWindowTitle(g_window, "Sample Window"); */
}


XPlane::~XPlane() {
    destroyMenu();
    destroyCommands();
}

void XPlane::createMenu(const std::string &name) {

    XPLMMenuID pluginMenu = XPLMFindPluginsMenu();
    subMenuIdx = XPLMAppendMenuItem(pluginMenu, name.c_str(), nullptr, 0);

    if (subMenuIdx < 0) {
        throw std::runtime_error("Couldn't create our menu item");
    }

    subMenu = XPLMCreateMenu(name.c_str(), pluginMenu, subMenuIdx, [] (void *ctrl, void *cb) {
        XPlane *us = (XPlane *) ctrl;
        auto idx = reinterpret_cast<intptr_t>(cb);
        MenuCallback callback = us -> menuCallbacks[idx];
        if (callback) {
            callback();
        }
    }, this);

    if (!subMenu) {
        XPLMRemoveMenuItem(pluginMenu, subMenuIdx);
        throw std::runtime_error("Couldn't create our menu");
    }

}


void XPlane::addMenuEntry(const std::string &label, MenuCallback cb) {
    menuCallbacks.push_back(cb);
    intptr_t idx = menuCallbacks.size() - 1;
    XPLMAppendMenuItem(subMenu, label.c_str(), reinterpret_cast<void *>(idx), 0);
}


void XPlane::destroyMenu() {
    if (subMenu) {
        XPLMDestroyMenu(subMenu);
        subMenu = nullptr;
        XPLMRemoveMenuItem(XPLMFindPluginsMenu(), subMenuIdx);
        subMenuIdx = -1;
    }
}

/*
void XPlane::showAbout() {

    draw_about_box(g_window, &params);
}

*/

void XPlane::createCommand(const std::string &name, const std::string &desc, CommandCallback cb) {
    
    XPLMCommandRef cmd = XPLMCreateCommand(name.c_str(), desc.c_str());
    
    if (!cmd) {
        throw std::runtime_error("Couldn't create command: " + name);
    }

    RegisteredCommand cmdInfo;
    cmdInfo.callback = cb;
    cmdInfo.inBefore = true;
    cmdInfo.refCon = this;

    commandHandlers.insert(std::make_pair(cmd, cmdInfo));

    XPLMRegisterCommandHandler(cmd, handleCommand, true, this);

}

XPLMCommandRef XPlane::createCommandAndTellMe(const std::string &name, const std::string &desc, CommandCallback cb) {

    XPLMCommandRef cmd = XPLMCreateCommand(name.c_str(), desc.c_str());
    
    if (!cmd) {
        throw std::runtime_error("Couldn't create command: " + name);
    }
    RegisteredCommand cmdInfo;
    cmdInfo.callback = cb;
    cmdInfo.inBefore = true;
    cmdInfo.refCon = this;

    commandHandlers.insert(std::make_pair(cmd, cmdInfo));

    XPLMRegisterCommandHandler(cmd, handleCommand, true, this);

    return cmd;
}

int XPlane::handleCommand(XPLMCommandRef cmd, XPLMCommandPhase phase, void* ref) {
    XPlane *us = reinterpret_cast<XPlane *>(ref);
    if (!us) {
        return 1;
    }

    CommandCallback f = us->commandHandlers[cmd].callback;
    if (f) {
        switch (phase) {
        case xplm_CommandBegin:     f(CommandState::START); break;
        case xplm_CommandContinue:  f(CommandState::CONTINUE); break;
        case xplm_CommandEnd:       f(CommandState::END); break;
        }
    }

    return 1;
}

void XPlane::destroyCommands() {
    
    for (auto &iter: commandHandlers) {
        XPLMUnregisterCommandHandler(iter.first, handleCommand, true, this);
    }
    commandHandlers.clear();
}

void XPlane::destroyCommand(XPLMCommandRef cmd) {
    
    XPLMUnregisterCommandHandler(cmd, handleCommand, true, this);
    commandHandlers.erase(cmd);
}

std::string XPlane::aircraftName() {
    
    return _aircraftStringName;
}

std::string XPlane::updateAircraftName() {

    int charCount;
    
    charCount = XPLMGetDatab(aircraftRef, _aircraftByteName, 0, 250);
    
    for (int i = 0; i < charCount; i++) {
        _aircraftCharName[i] = (char) _aircraftByteName[i];
    }
    _aircraftStringName = _aircraftCharName;
    return _aircraftStringName;
}


std::string XPlane::xplaneDirectory() {
    
    return _xplaneDirectoryString;
}
