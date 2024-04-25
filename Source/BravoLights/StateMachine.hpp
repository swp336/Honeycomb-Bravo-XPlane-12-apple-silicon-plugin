//
//  StateMachine.hpp
//  Honeycomb
//
//  Created by Steve Proctor on 07/07/2023.
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


#ifndef StateMachine_hpp
#define StateMachine_hpp

#define MAX_STATES 32

#include <cstddef>
#include <set>
#include <map>
#include <stdarg.h>
#include "APButtonLabel.hpp"

class LightState {

public:
    LightState(int state);
    int state();
    void addStateTransition(APButtonLabel thisButton, int moveToState);
    int nextState(APButtonLabel thisButton);
    void stateTransitionActions();
    void theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6, APButtonLabel Light7, APButtonLabel Light8);
    void theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6, APButtonLabel Light7);
    void theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6);
    void theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5);
    void theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4);
    void theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3);
    void theseLightsToTurnOn(APButtonLabel Light1, APButtonLabel Light2);
    void theseLightsToTurnOn(APButtonLabel Light1);
    
    void theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6, APButtonLabel Light7, APButtonLabel Light8);
    void theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6, APButtonLabel Light7);
    void theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5, APButtonLabel Light6);
    void theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4, APButtonLabel Light5);
    void theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3, APButtonLabel Light4);
    void theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2, APButtonLabel Light3);
    void theseLightsToTurnOff(APButtonLabel Light1, APButtonLabel Light2);
    void theseLightsToTurnOff(APButtonLabel Light1);
    
    std::tuple<bool, int> getTransitionValue(APButtonLabel thisButton, int fromThisState);
    std::set<APButtonLabel> getOnLights();
    std::set<APButtonLabel> getOffLights();

private:
    int _state;
    std::set<APButtonLabel> onLights;
    std::set<APButtonLabel> offLights;
    std::map<APButtonLabel, int> stateTransitions;
};


class StateMachine {
    
public:
    StateMachine();
    void addState(LightState* newState);
    void goToNextState(APButtonLabel thisButton);
    LightState* lightState(int thisState);

private:
    int currentState = 0;
    LightState* states[MAX_STATES];
};


#endif /* StateMachine_hpp */
