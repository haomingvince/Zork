#ifndef _CREATURE_H
#define _CREATURE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "attack.hpp"
#include "trigger.hpp"

using namespace std;

class Creature {
public:
    Creature(rapidxml::xml_node<>*);
    virtual ~Creature();
    void setupCreature(rapidxml::xml_node<>* node);

    string name = "";
    string status = "";
    string description = "";
    vector<string> vulnerability;
    Attack* attack;
    vector<Trigger*> trigger;
};

#endif