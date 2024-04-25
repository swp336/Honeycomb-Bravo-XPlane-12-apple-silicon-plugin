//
//  XPlane.hpp
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


#ifndef XPlane_hpp
#define XPlane_hpp


#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include <XPLMUtilities.h>
#include <XPLMMenus.h>
#include <DataRef.h>



enum class CommandState {
    START,
    CONTINUE,
    END
};


class XPlane {
    
public:
    XPlane();
    
    using MenuCallback = std::function<void()>;
    using CommandCallback = std::function<void(CommandState)>;
    
    // Must be called from the environment thread - do not call from GUI thread!
    void createMenu(const std::string &name);
    void addMenuEntry(const std::string &label, MenuCallback cb);
    void destroyMenu();
//    void showAbout();
    void createCommand(const std::string &name, const std::string &desc, CommandCallback cb);
    XPLMCommandRef createCommandAndTellMe(const std::string &name, const std::string &desc, CommandCallback cb);
    void destroyCommands();
    void destroyCommand(XPLMCommandRef cmd);
    std::string aircraftName();
    std::string updateAircraftName();
    std::string xplaneDirectory();

    // Can be called from any thread
//    void setIsInMenu(bool menu);

    ~XPlane();
private:
    struct RegisteredCommand {
        CommandCallback callback;
        bool inBefore;
        void *refCon;
    };

    std::vector<MenuCallback> menuCallbacks;
    std::map<XPLMCommandRef, RegisteredCommand> commandHandlers;
    int subMenuIdx = -1;
    XPLMMenuID subMenu = nullptr;
    bool isInMenu = false;

    XPLMDataRef aircraftRef = NULL;
    std::byte _aircraftByteName[250];
    char _aircraftCharName[250];
    std::string _aircraftStringName;
    char _xplaneDirectoryChar[513];
    std::string _xplaneDirectoryString;
    static int handleCommand(XPLMCommandRef cmd, XPLMCommandPhase phase, void *ref);
};


#endif /* XPlane_hpp */
