#include "creature.hpp"

Creature::~Creature() {}

Creature::Creature(rapidxml::xml_node<>* head) {
    setupCreature(head);
}

void Creature::setupCreature(rapidxml::xml_node<>* head) {
    rapidxml::xml_node<>* temp = head->first_node();

    while(temp != NULL) {
        string tag = string(temp->name());
        if (tag == "name") {
            this->name = temp->value();
        }
        else if (tag == "status") {
            this->status = temp->value();
        }
        else if (tag == "description") {
            this->description = temp->value();
        }
        else if (tag == "vulnerability") {
            (this->vulnerability).push_back(temp->value());
        }
        else if (tag == "attack") {
            this->attack = new Attack(temp);
        }
        else if (tag == "trigger") {
            (this->trigger).push_back(new Trigger(temp));
        }
        temp = temp -> next_sibling();
    }
}


