#ifndef _ATTACK_HPP
#define _ATTACK_HPP

#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include "rapidxml.hpp"
#include "executioner.hpp"
//#include "trigger.hpp"
#include <iostream>

class Attack{
public:
    Attack(rapidxml::xml_node<>*);
    virtual ~Attack();
    void setupAttack(rapidxml::xml_node<>* node);

    Condition condition;
    string print = "";
    vector<string> action;
    int have_condition = 0;
    int have_print = 0;
    int have_action = 0;
};
#endif
