#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include "rapidxml.hpp"
#include "trigger.hpp"
#include "executioner.hpp"
#include <iostream>

using namespace std;

class Item {
public:
    Item(rapidxml::xml_node<>*);
    virtual ~Item();
    void setupItem(rapidxml::xml_node<>* node);

    string name = "";
    string status = "";
    //string description = "";
    string writing = "";
    Turnon turnon;
    vector<Trigger*> trigger;

    int turnon_flagg = 0;
};

#endif