//
//  Switches.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 08/04/2023.
//

#ifndef Switches_hpp
#define Switches_hpp

#include <stdio.h>
#include <memory>
#include "XPCommand.hpp"
#include "XPlane.hpp"
#include "XPlaneEnvironment.hpp"
#include "Switch.hpp"
#include "Toggle.hpp"

/*
enum switchState {on, off};

enum switchLabel { SW1, SW2, SW3, SW4, SW5, SW6, SW7, SW8, SW9, SW10, SW11, SW12, SW13, SW14 };

enum toggleLabel { TG1, TG2, TG3, TG4, TG5, TG6, TG7 };

 */

/*
class BasicSwitch {

public:
    BasicSwitch(switchLabel switchID, switchState defaultState);
    ~BasicSwitch();
    void toggle();
    void delegateHandler();
    int switchID();
    switchState status();
    std::string userReference();
    std::string userDescription();

protected:
    void switchHandler();
    switchState ownState;
    switchState myDefault;
    switchLabel mySwitchID;
    std::string userRef;
    std::string userDesc;
    XPLMCommandRef handlerRef;
};



class CommandSwitch : public Switch {
  
public:
    
    CommandSwitch(switchLabel switchID);
    virtual void setCommand(XPCommand *newXPCommand);
    void delegateCommand();
    ~CommandSwitch();
    
protected:
    void           switchHandler();
    bool           commandIsNull = true;
    XPCommand*     myCommand     = NULL;
    XPLMCommandRef handlerRef;
};

*/

/*
class BasicToggle {
    
public:
    BasicToggle(toggleLabel toggleID);
    bool isActive();
    void delegateCommand();
    Switch *onControl();
    Switch *offControl();
    ~BasicToggle();

protected:
    virtual void onCommandHandler();
    virtual void offCommandHandler();
    switchState toggleState;
    Switch *onSwitch = NULL;
    Switch *offSwitch = NULL;
    XPLMCommandRef onHandlerRef;
    XPLMCommandRef offHandlerRef;
};
*/
/*
class CommandToggle {
    
public:
    CommandToggle(toggleLabel toggleID);
    CommandToggle(toggleLabel toggleID, XPTwinCommands* newCommands);
    CommandToggle(toggleLabel toggleID, XPCommand* newCommand1, XPCommand* newCommand2);
    CommandToggle(toggleLabel toggleID, const char* newCommand1, XPCommand* newCommand2);
    CommandToggle(toggleLabel toggleID, XPCommand* newCommand1, const char* newCommand2);
    CommandToggle(toggleLabel toggleID, const char* newCommand1, const char* newCommand2);
    void setCommands(XPTwinCommands *newCommands);
    void setCommands(XPCommand* newCommand1, XPCommand* newCommand2);
    void setCommands(const char* newCommand1, XPCommand* newCommand2);
    void setCommands(XPCommand* newCommand1, const char* newCommand2);
    void setCommands(const char* newCommand1, const char* newCommand2);
    bool toggleIsOn();
    XPTwinCommands* commands();
    toggleLabel toggleID();
    void delegateCommand();
    Switch *upperControl();
    Switch *lowerControl();
    ~CommandToggle();
    
protected:
    void            toggleOffHandler();
    void            toggleOnHandler();
    Switch*    upperSwitch = NULL;
    Switch*    lowerSwitch = NULL;
    XPTwinCommands* myCommands  = NULL;
    toggleLabel     myToggleID;
    bool            toggleOnStatus = false;
    XPLMCommandRef  offHandlerRef = NULL;
    XPLMCommandRef  onHandlerRef = NULL;
};
*/

#endif /* Switches_hpp */
