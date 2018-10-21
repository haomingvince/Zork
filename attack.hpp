#ifndef _ATTACK_HPP
#define _ATTACK_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "executioner.hpp"

using namespace std;

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
