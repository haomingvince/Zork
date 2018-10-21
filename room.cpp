#include "room.hpp"

Room::~Room() { }

Room::Room(rapidxml::xml_node<>* node) {
    setupRoom(node);
}

void Room::setupRoom(rapidxml::xml_node<>* node) {
    rapidxml::xml_node<> *temp1 = node->first_node();

    while (temp1 != NULL) {
        string tag1 = string(temp1->name());
        if (tag1 == "name") {
            this->name = temp1->value();
        }
        if (tag1 == "status") {
            this->status = temp1->value();
        }
        if (tag1 == "type") {
            this->type = temp1->value();
        }
        if (tag1 == "description") {
            this->description = temp1->value();
        }
        if (tag1 == "border") {
            Border *newborder = new Border();
            string bdname, direction;
            rapidxml::xml_node<>* temp2 = temp1->first_node();
            while(temp2 != NULL) {
                string tag2 = string(temp2->name());
                if (tag2 == "name") {
                    bdname = temp2->value();
                }
                if (tag2 == "direction") {
                    direction = temp2->value();
                    if (direction == "north") {
                        direction = "n";
                    }
                    if (direction == "south") {
                        direction = "s";
                    }
                    if (direction == "west") {
                        direction = "w";
                    }
                    if (direction == "east") {
                        direction = "e";
                    }
                }
                temp2 = temp2 -> next_sibling();
            }
            newborder->direction = direction;
            newborder->name = bdname;
            this->border.push_back(newborder);

        }
        string buffer;
        if (tag1 == "container") {
            buffer = temp1->value();
            this->container.push_back(buffer);
        }
        if (tag1 == "item") {
            buffer = temp1->value();
            this->item.push_back(buffer);
        }
        if (tag1 == "creature") {
            buffer = temp1->value();
            this->creature.push_back(buffer);
        }
        if (tag1 == "trigger") {
            Trigger *t = new Trigger(temp1);
            this->trigger.push_back(t);
        }
        temp1 = temp1 -> next_sibling();
    }
}