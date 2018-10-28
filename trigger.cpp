#include "trigger.hpp"

Trigger::~Trigger() { }
Trigger::Trigger(rapidxml::xml_node<>* node){
    setupTrigger(node);
}

void Trigger::setupTrigger(rapidxml::xml_node<> *node) {
    rapidxml::xml_node<> *temp = node->first_node();
    while (temp != NULL){
        string tag = string(temp->name());
        if(tag == "type"){
            this->type = temp -> value();
        }
        if(tag == "print"){
            this->has_print = 1;
            this->print = temp -> value();
        }
        if(tag == "command"){
            this->has_command = 1;
            this->command = temp -> value();
        }
        if(tag == "action"){
            this->has_action = 1;
            string buffer = temp -> value();
            this->action.push_back(buffer);
        }
        if(tag == "condition"){
            rapidxml::xml_node<> *t = temp->first_node();
            while(t != NULL){
                this->condition++;
                t = t -> next_sibling();
            }
            if(this->condition == 2){
                // setup twoCondTrigger
                rapidxml::xml_node<> *temp2 = temp->first_node();
                while(temp2 != NULL){
                    string tag2 = string(temp2->name());
                    if(tag2 == "object"){
                        this->status.object = temp2 -> value();
                    }
                    if(tag2 == "status"){
                        this->status.status = temp2 -> value();
                    }
                    temp2 = temp2 -> next_sibling();
                }
            }
            else if(condition == 3) {
                // setup threeCondTrigger
                rapidxml::xml_node<> *temp2 = temp->first_node();
                while (temp2 != NULL) {
                    string tag2 = string(temp2->name());
                    if (tag2 == "object") {
                        this->owner.object = temp2->value();
                    }
                    if (tag2 == "has") {
                        this->owner.has = temp2->value();
                    }
                    if (tag2 == "owner") {
                        this->owner.owner = temp2->value();
                    }
                    temp2 = temp2->next_sibling();
                }
            }
        }
        temp = temp -> next_sibling();
    }
}
