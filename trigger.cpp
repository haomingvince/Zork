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
            this->condition = condition_count(temp);
            /*
            rapidxml::xml_node<> *temp2 = node->first_node();
            while(temp2 != NULL){
                this->condition++;
                temp2 = temp2 -> next_sibling();
            }
             */
            if(this->condition == 2){
                setupStatus(temp);
            }else if(condition == 3){
                setupOwner(temp);
            }
        }
        temp = temp -> next_sibling();
    }
}

int Trigger::condition_count(rapidxml::xml_node<>* node){
    int num = 0;
    for(rapidxml::xml_node<>* kid = node -> first_node();
        kid; kid = kid -> next_sibling()){
        num++;
    }
    return num;
}
void Trigger::setupStatus(rapidxml::xml_node<>* node){
    rapidxml::xml_node<> *temp = node->first_node();
    while(temp != NULL){
        string tag = string(temp->name());
        if(tag == "object"){
            this->status.object = temp -> value();
        }
        if(tag == "status"){
            this->status.status = temp -> value();
        }
        temp = temp -> next_sibling();
    }
}
void Trigger::setupOwner(rapidxml::xml_node<>* node){
    rapidxml::xml_node<> *temp = node->first_node();
    while (temp != NULL){
        string tag = string(temp->name());
        if(tag == "object"){
            this->owner.object = temp -> value();
        }
        if(tag == "has"){
            this->owner.has = temp -> value();
        }
        if(tag == "owner"){
            this->owner.owner = temp -> value();
        }
        temp = temp -> next_sibling();
    }
}

