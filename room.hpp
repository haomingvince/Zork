#ifndef _ROOM_HPP
#define _ROOM_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "trigger.hpp"
#include "executioner.hpp"

using namespace std;

class Room{
public:
    Room(rapidxml::xml_node<>*);
    virtual ~Room();
    void setupRoom(rapidxml::xml_node<>* node);

    string name = "";
    string status = "";
    string type = "";
    string description = "";
    vector<Border *> border;
    vector<string> container;
    vector<string> item;
    vector<string> creature;
    vector<Trigger*> trigger;

};

#endif //_ROOM_HPP
