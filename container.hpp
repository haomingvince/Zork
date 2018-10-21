#ifndef _CONTAINER_H
#define _CONTAINER_H

#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include "rapidxml.hpp"
#include "trigger.hpp"
#include <iostream>

using namespace std;

class Container {
public:
    Container(rapidxml::xml_node<>*);
    virtual ~Container();
    void setupContainer(rapidxml::xml_node<>* node);

    string name = "";
    string status = "";
    string description = "";
    vector<string> accept;
    vector<string> item;
    vector<Trigger*> trigger;
};

#endif