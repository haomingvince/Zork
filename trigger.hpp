#ifndef _TRIGGER_HPP
#define _TRIGGER_HPP

#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include "rapidxml.hpp"
#include "executioner.hpp"
#include <iostream>

class Trigger{
public:
    Trigger(rapidxml::xml_node<>* node);
    virtual ~Trigger();
    void setupTrigger(rapidxml::xml_node<>* node);
    void setupStatus(rapidxml::xml_node<>* node);
    void setupOwner(rapidxml::xml_node<>* node);
    int condition_count(rapidxml::xml_node<>* node);

    string type = "single";
    string command = "";
    string print = "";
    vector<string> action;
    int condition = 0;     //2 is status, 3 is owner
    int has_command = 0;
    int has_print = 0;
    int has_action = 0;
    Status status;
    Owner owner;
    int times = 0;//for single

};
#endif //_TRIGGER_HPP
