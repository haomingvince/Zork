#include "attack.hpp"

Attack::~Attack() {}

Attack::Attack(rapidxml::xml_node<>* node) {
    setupAttack(node);
}

void Attack::setupAttack(rapidxml::xml_node<>* node) {
    rapidxml::xml_node<>* temp1 = node->first_node();

    while(temp1 != NULL) {
        string tag1 = string(temp1->name());
        if(tag1 == "condition") {
            this->has_condition = 1;
            rapidxml::xml_node<>* temp2 = temp1->first_node();
            while(temp2 != NULL) {
                string tag2 = string(temp2->name());
                if(tag2 == "object") {
                    (this->condition).object = temp2->value();
                }
                if(tag2 == "status") {
                    (this->condition).status = temp2->value();
                }
                temp2 = temp2 -> next_sibling();
            }
        }
        if(tag1 == "print") {
            this->has_print = 1;
            this->print = temp1 -> value();
        }
        if(tag1 == "action") {
            this->has_action = 1;
            string buffer = temp1 -> value();
            this->action.push_back(buffer);
        }
        temp1 = temp1 -> next_sibling();
    }
}