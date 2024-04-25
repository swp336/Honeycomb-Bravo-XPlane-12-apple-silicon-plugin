//
//  Switches.cpp
//  Honeycomb
//
//  Created by Steve Proctor on 08/04/2023.
//

#include "Switch.hpp"
#include "Switches.hpp"
#include <map>

/*
std::string switchRef(int switchNumber) {
 
    return std::string("Honeycomb/Bravo/Switch/") + std::to_string(switchNumber);
}

std::string switchDescr(int switchNumber) {
 
    return std::string("Switch ") + std::to_string(switchNumber);
}


std::map<toggleLabel, switchLabel> upperSwitchMap { {TG1,SW1}, {TG2,SW3}, {TG3,SW5}, {TG4,SW7}, {TG5,SW9}, {TG6,SW11}, {TG7,SW13} };
std::map<toggleLabel, switchLabel> lowerSwitchMap { {TG1,SW2}, {TG2,SW4}, {TG3,SW6}, {TG4,SW8}, {TG5,SW10}, {TG6,SW12}, {TG7,SW14} };

std::map<switchLabel, int> switchMap { {SW1,13}, {SW2,14}, {SW3,15}, { SW4,16},  {SW5,17},  {SW6,18},  {SW7,19},
                                       {SW8,20}, {SW9,21}, {SW10,22}, {SW11,23}, {SW12,24}, {SW13,25}, {SW14,26} };

switchLabel upperSwitchID(toggleLabel toggleID) {
    return upperSwitchMap[toggleID];
}

switchLabel lowerSwitchID(toggleLabel toggleID) {
    return lowerSwitchMap[toggleID];
}

int switchNumber(switchLabel switchID) {
    return switchMap[switchID];
}

 */

/***************************************************************
 *
 *  Basic switch for honeycomb bravo
 *
 *  Tracks on / off switch status updated with each button press event
 *  For use when monitoring single switch status in some broader function
 *
 *  The commandHandler can be replaced by another object using the delegate
 *  method to remove the built in handler and then creating their own version
 *
 *********************************************************************************************/

/*
BasicSwitch::BasicSwitch(switchLabel switchID, switchState defaultState) : mySwitchID(switchID), myDefault(defaultState), userRef(switchRef(switchNumber(switchID))), userDesc(switchDescr(switchNumber(switchID))) {
    
    ownState = myDefault;
    handlerRef = xplane -> createCommandAndTellMe(userRef.c_str(), userDesc.c_str(), [this] (CommandState s) {if ((s == CommandState::START) || (s == CommandState::END)) switchHandler(); });
}

std::string BasicSwitch::userReference() {
    return userRef;
}

std::string BasicSwitch::userDescription() {
    return userDesc;
}

int BasicSwitch::switchID() {
    return mySwitchID;
}

switchState BasicSwitch::status() {
    return ownState;
}

void BasicSwitch::toggle() {
    if (ownState == on) ownState = off; else ownState = on;
}

void BasicSwitch::delegateHandler() {
    xplane -> destroyCommand(handlerRef);
}

void BasicSwitch::switchHandler() {
    if (ownState == on) ownState = off; else ownState = on;
}

BasicSwitch::~BasicSwitch() {
    xplane -> destroyCommand(handlerRef);
}

*/

/***************************************************************
 *
 *  Command switch for honeycomb bravo
 *
 *  Executes a sim command each time it's pressed
 *
 *  Command handler is invoked at the start of the switch event
 *
 *  The commandHandler can be replaced by another object using the delegate
 *  method to remove the built in handler and then creating their own version
 *
 *********************************************************************************************/
/*

CommandSwitch::CommandSwitch(switchLabel switchID) : Switch(switchID, off) {
    
}

void CommandSwitch::setCommand(XPCommand *newXPCommand) {
    
    myCommand = newXPCommand;
    
    Switch::delegateHandler();
    handlerRef = xplane -> createCommandAndTellMe(userRef.c_str(), userDesc.c_str(), [this] (CommandState s) { if (s == CommandState::START) CommandSwitch::switchHandler(); });
}

void CommandSwitch::delegateCommand() {    
    xplane -> destroyCommand(handlerRef);
}

CommandSwitch::~CommandSwitch() {
    xplane -> destroyCommand(handlerRef);
}

void CommandSwitch::switchHandler() {
    if (!myCommand -> isNull()) {
        XPLMCommandOnce(myCommand -> commandRef());
    }
}

*/

/***************************************************************
 *
 *  Basic Rocker switch for honeycomb bravo
 *
 *  Tracks on / off switch status updated with each button press event
 *  For use when monitoring switch status in some broader function
 *
 *  Command handler is invoked at the start of each switch press switch event
 *
 *  The commandHandler can be replaced by another object using the delegate
 *  method to remove the built in handler and then creating their own version
 *
 *********************************************************************************************/

/*
BasicToggle::BasicToggle(toggleLabel toggleID) {
    
    toggleState = off;
    switchLabel offSwitchID = upperSwitchID(toggleID);
    switchLabel onSwitchID  = lowerSwitchID(toggleID);
    offSwitch = new BasicSwitch(offSwitchID, off);
    onSwitch  = new BasicSwitch(onSwitchID, on);
    offSwitch -> delegateHandler();
    onSwitch -> delegateHandler();
    offHandlerRef =  xplane -> createCommandAndTellMe(offSwitch->userReference().c_str(), offSwitch->userDescription().c_str(), [this] (CommandState s) { if (s == CommandState::START) offCommandHandler(); });
    onHandlerRef = xplane -> createCommandAndTellMe(onSwitch->userReference().c_str(), onSwitch->userDescription().c_str(), [this] (CommandState s) { if (s == CommandState::START) onCommandHandler(); });
}

bool BasicToggle::isActive() {
    return (toggleState == true);
}

BasicSwitch* BasicToggle::onControl() {
    return onSwitch;
}

BasicSwitch* BasicToggle::offControl() {
    return offSwitch;
}

void BasicToggle::delegateCommand() {
    xplane -> destroyCommand(offHandlerRef);
    xplane -> destroyCommand(onHandlerRef);
}

void BasicToggle::offCommandHandler() {
    
    switch (toggleState) {
            
        case on:  toggleState = off;
                  onSwitch -> toggle();
                  break;
        case off: toggleState = off;
                  break;
    }
}

void BasicToggle::onCommandHandler() {
    
    switch (toggleState) {
            
        case on:  toggleState = on;
                  break;
        case off: toggleState = on;
                  offSwitch -> toggle();
                  break;
    }
}

BasicToggle::~BasicToggle() {
    xplane -> destroyCommand(offHandlerRef);
    xplane -> destroyCommand(onHandlerRef);
    delete offSwitch;
    delete onSwitch;
}

*/


/***************************************************************
 *
 *  Command Toggle switch for honeycomb bravo
 *
 *  Executes a sim command for each of the upport and lower switch press events
 *  For use with two related commands that toggles a feature between two states
 *
 *  Can also used as a simplex toggle when bothe commands are the same
 *
 *  Command handler is invoked at the start of each switch press switch event
 *
 *  The commandHandler can be replaced by another object using the delegate
 *  method to remove the built in handler and then creating their own version
 *
 *********************************************************************************************/
/*
CommandToggle::CommandToggle (toggleLabel toggleID) : myToggleID(toggleID) {
        
    switchLabel offSwitchID = upperSwitchID(toggleID);
    switchLabel onSwitchID  = lowerSwitchID(toggleID);
    upperSwitch = new Switch(offSwitchID, off);
    lowerSwitch = new Switch(onSwitchID, on);
}

CommandToggle::CommandToggle(toggleLabel toggleID, XPTwinCommands* newCommands) : CommandToggle(toggleID) {
    setCommands (newCommands);
}

CommandToggle::CommandToggle(toggleLabel toggleID, XPCommand* newCommand1, XPCommand* newCommand2) : CommandToggle(toggleID) {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

CommandToggle::CommandToggle(toggleLabel toggleID, const char* newCommand1, XPCommand* newCommand2) : CommandToggle(toggleID) {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

CommandToggle::CommandToggle(toggleLabel toggleID, XPCommand* newCommand1, const char* newCommand2) : CommandToggle(toggleID) {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

CommandToggle::CommandToggle(toggleLabel toggleID, const char* newCommand1, const char* newCommand2) : CommandToggle(toggleID)  {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

void CommandToggle::setCommands(XPTwinCommands *newCommands) {
    
    myCommands = newCommands;
    
    if ((onHandlerRef == NULL) && (offHandlerRef == NULL)) {
        upperSwitch -> delegateHandler();
        lowerSwitch  -> delegateHandler();
        offHandlerRef = xplane -> createCommandAndTellMe(upperSwitch->userReference().c_str(), upperSwitch->userDescription().c_str(), [this] (CommandState s) { if (s == CommandState::START) toggleOffHandler(); });
        onHandlerRef = xplane -> createCommandAndTellMe(lowerSwitch->userReference().c_str(), lowerSwitch->userDescription().c_str(), [this] (CommandState s) { if (s == CommandState::START) toggleOnHandler(); });
    }
}

void CommandToggle::setCommands(XPCommand* newCommand1, XPCommand* newCommand2) {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

void CommandToggle::setCommands(const char* newCommand1, XPCommand* newCommand2) {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

void CommandToggle::setCommands(XPCommand* newCommand1, const char* newCommand2) {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

void CommandToggle::setCommands(const char* newCommand1, const char* newCommand2) {
    setCommands(new XPTwinCommands(newCommand1, newCommand2));
}

bool CommandToggle::toggleIsOn() {
    return toggleOnStatus;
}

XPTwinCommands* CommandToggle::commands() {
    return myCommands;
}

toggleLabel CommandToggle::toggleID() {
    return myToggleID;
}

void CommandToggle::delegateCommand() {
    xplane -> destroyCommand(offHandlerRef);
    xplane -> destroyCommand(onHandlerRef);
}

Switch *CommandToggle::upperControl() {
    return upperSwitch;
}

Switch* CommandToggle::lowerControl () {
    return lowerSwitch;
}

void CommandToggle::toggleOffHandler() {
    toggleOnStatus = false;
}

void CommandToggle::toggleOnHandler()  {
    toggleOnStatus = true;
}

CommandToggle::~CommandToggle() {
    xplane -> destroyCommand(offHandlerRef);
    xplane -> destroyCommand(onHandlerRef);
    delete upperSwitch;
    delete lowerSwitch;
}

*/
