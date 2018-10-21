#ifndef _ITEM_H
#define _ITEM_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "trigger.hpp"
#include "executioner.hpp"

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