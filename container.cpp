#include "container.hpp"

Container::~Container() {}

Container::Container(rapidxml::xml_node<>* head) {
    setupContainer(head);
}

void Container::setupContainer(rapidxml::xml_node<>* head) {
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
        else if (tag == "accept") {
            (this->accept).push_back(temp->value());
        }
        else if (tag == "item") {
            (this->item).push_back(temp->value());
        }
        else if (tag == "trigger") {
            (this->trigger).push_back(new Trigger(temp));
        }
        temp = temp -> next_sibling();
    }
}


