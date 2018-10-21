#include "item.hpp"

Item::~Item() {}

Item::Item(rapidxml::xml_node<>* head) {
    setupItem(head);
}

void Item::setupItem(rapidxml::xml_node<>* head) {
    rapidxml::xml_node<>* temp = head->first_node();

    while(temp != NULL) {
        string tag = string(temp->name());
        if (tag == "name") {
            this->name = temp->value();
        }
        else if (tag == "status") {
            this->status = temp->value();
        }
        /*else if (tag == "description") {
            this->description = temp->value();
        }*/
        else if (tag == "writing") {
            this->writing = temp->value();
        }
        else if (tag == "trigger") {
            (this->trigger).push_back(new Trigger(temp));
        }
        else if (tag == "turnon") {
            turnon_flagg = 1;
            rapidxml::xml_node<>* temp2 = temp->first_node();
            while (temp2 != NULL) {
                string tag1 = string(temp2->name());
                if (tag1 == "print") {
                    this->turnon.print = temp2->value();
                }
                else if (tag1 == "action") {
                    this->turnon.action = temp2->value();
                }
                temp2 = temp2->next_sibling();
            }
        }
        temp = temp -> next_sibling();
    }
}


