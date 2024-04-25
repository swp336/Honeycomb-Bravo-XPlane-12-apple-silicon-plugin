//
//  ToggleSet.cpp
//  Honeycomb
//
//  Created by Steve Proctor on 20/04/2023.
//

#include "ToggleSet.hpp"

/*
namespace std {

    template <>                 // required to enable a toggleLabel to be uniquely hashed so it can fprovide a unique key for the map
    struct hash<toggleLabel>
        { size_t operator()(const toggleLabel key)
            { switch (key) {
                case TG1:
                    return 1;
                    break;
                case TG2:
                    return 2;
                    break;
                case TG3:
                    return 3;
                    break;
                case TG4:
                    return 4;
                    break;
                case TG5:
                    return 5;
                    break;
                case TG6:
                    return 6;
                    break;
                case TG7:
                    return 7;
                    break;
                    return 0;
                }
            }
        };
}

ToggleSet::ToggleSet() {
    
}

ToggleSet::~ToggleSet() {
    
}

void ToggleSet::addToggle(Toggle* newToggle) {
    
    toggleSet.insert(std::make_pair(newToggle->toggleID(), newToggle));
}

Toggle*  ToggleSet::getToggle(toggleLabel toggleToGet) {
    return toggleSet[toggleToGet];
}

bool ToggleSet::isActive() {
    
    bool foundActive = false;
    
    for(it = toggleSet.begin(); it != toggleSet.end(); ++it) {
        try {
            foundActive = foundActive || it -> second -> toggleIsOn();
        }
        catch (...)
        {
        }
    }
    return foundActive;
}

Toggle* ToggleSet::activeToggle() {
    
    bool found = false;
    Toggle* foundToggle = NULL;
    
    for(it = toggleSet.begin(); ((it != toggleSet.end()) && (!found)); ++it) {
        try {
            if (it -> second != NULL) {
                found = it -> second -> toggleIsOn();
                if (found) foundToggle = it ->second;
            }
        }
        catch (...)
        {
        }
    }

    return foundToggle;
}



CommandToggleSet::CommandToggleSet() {
    
}

CommandToggleSet::~CommandToggleSet() {
    
}

void CommandToggleSet::addToggle(CommandToggle* newToggle) {
    
    toggleSet.insert(std::make_pair(newToggle->toggleID(), newToggle));
}

CommandToggle*  CommandToggleSet::getToggle(toggleLabel toggleToGet) {
    return toggleSet[toggleToGet];
}

bool CommandToggleSet::isActive() {
    
    bool foundActive = false;
    
    for(it = toggleSet.begin(); it != toggleSet.end(); ++it) {
        try {
            foundActive = foundActive || it -> second -> toggleIsOn();
        }
        catch (...)
        {
        }
    }
    return foundActive;
}

CommandToggle* CommandToggleSet::activeToggle() {
    
    bool found = false;
    CommandToggle* foundToggle = NULL;
    
    for(it = toggleSet.begin(); ((it != toggleSet.end()) && (!found)); ++it) {
        try {
            if (it -> second != NULL) {
                found = it -> second -> toggleIsOn();
                if (found) foundToggle = it ->second;
            }
        }
        catch (...)
        {
        }
    }

    return foundToggle;
}

*/

