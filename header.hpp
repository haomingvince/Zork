#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "trigger.hpp"
#include "executioner.hpp"
#include "room.hpp"
#include "container.hpp"
#include "item.hpp"
#include "creature.hpp"

using namespace std;

//Global Declaration
vector<Room*> rooms;
vector<Container*> containers;
vector<Item*> items;
vector<Creature*> creatures;

vector<string> inventory;
bool END = false;
Room * current;
void checkInput(string);
string findType(string);

Room* findRoom(string specific)  {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->name == specific) {
            return rooms[i];
        }
    }
    return NULL;
}

Container* findContainer(string specific)  {
    for (int i = 0; i < containers.size(); i++) {
        if (containers[i]->name == specific) {
            return containers[i];
        }
    }
    return NULL;
}

Item* findItem(string specific)  {
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->name == specific) {
            return items[i];
        }
    }
    return NULL;
}

bool findContainerInRoom(string container) {
    for (int i = 0; i < current->container.size(); i++) {
        if (current->container[i] == container) {
            return true;
        }
    }
    return false;
}

bool existAccept(Container* container, string accept) {
    for (int i = 0; i < container->accept.size(); i++) {
        if (container->accept[i] == accept) {
            return true;
        }
    }

    return false;
}

bool existAttackee(string attackee) {
    for (int i = 0; i < current->creature.size(); i++) {
        if (current->creature[i] == attackee) {
            return true;
        }
    }
    return false;
}

bool existIteminInventory(string item) {
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == item) {
            return true;
        }
    }

    return false;
}

int existCreature(string creature) {
    for (int i = 0; i < creatures.size(); i++) {
        if (creatures[i]->name == creature) {
            return i;
        }
    }
    return -1;
}

bool matchVulner(int idx, string vulner) {
    for (int i = 0; i < creatures[idx]->vulnerability.size(); i++) {
        if (creatures[idx]->vulnerability[i] == vulner) {
            return true;
        }
    }
    return false;
}

Creature* findCreature(string specific)  {
    for (int i = 0; i < creatures.size(); i++) {
        if (creatures[i]->name == specific) {
            return creatures[i];
        }
    }
    return NULL;
}

int findBorderidx(string inpStr) {
    for (int i = 0; i < current->border.size(); i++) {
        if (current->border[i]->name == inpStr) {
            return i;
        }
    }

    return -1;
}

int findContainerInRoomidx(Room* room, string container) {
    for (int i = 0; i < room->container.size(); i++) {
        if (room->container[i] == container) {
            return i;
        }
    }
    return -1;
}

int findItemInRoomidx(Room* room, string item) {
    for (int i = 0; i < room->item.size(); i++) {
        if (room->item[i] == item) {
            return i;
        }
    }
    return -1;
}

int findCreatureInRoomidx(Room* room, string creature) {
    for (int i = 0; i < room->creature.size(); i++) {
        if (room->creature[i] == creature) {
            return i;
        }
    }
    return -1;
}

void toAnotherRoom(string inpStr) {
    int pass = 0;
    pass = current->border.size();

    int i = 0;
    int flagg = 0;
    for (i = 0; i < pass; i++) {
        if (current->border[i]->direction == inpStr) {
            Room* newRoom = findRoom(current->border[i]->name);
            if (newRoom != NULL) {
                flagg = 1;
                current = newRoom;
            }
            break;
        }
    }

    if (flagg == 1) {
        cout << current-> description << endl;
    }
    else {
        cout << "Can't go that way." << endl;
    }
}

/*************User Defined Functions - Behind scenes**************/
void Add(string inpStr) {
    string type = findType(inpStr.substr(0, inpStr.find(" to ")));
    if (type == "Item" ){
        Room* newRoom = findRoom(inpStr.substr(inpStr.find(" to ") + 4));
        if (newRoom != NULL) {
            newRoom->item.push_back(inpStr.substr(0, inpStr.find(" to ")));
            return;
        }
        Container* newContainer = findContainer(inpStr.substr(inpStr.find(" to ") + 4));
        if (newContainer != NULL) {
            newContainer->item.push_back(inpStr.substr(0, inpStr.find(" to ")));
            return;
        }
    }

    else if (type == "Creature") {
        Room* newRoom = findRoom(inpStr.substr(inpStr.find(" to ") + 4));
        if (newRoom != NULL) {
            newRoom->creature.push_back(inpStr.substr(0, inpStr.find(" to ")));
            return;
        }
    }

    else if (type == "Container") {
        Room* newRoom = findRoom(inpStr.substr(inpStr.find(" to ") + 4));
        if (newRoom != NULL) {
            newRoom->container.push_back(inpStr.substr(0, inpStr.find(" to ")));
            return;
        }
    }
}

void Delete(string inpStr) {
    if (findRoom(inpStr) != NULL) {
        int idx = findBorderidx(inpStr);
        if (idx != -1) {
            current->border.erase(current->border.begin()+idx);
            return;
        }
    }

    if (findContainer(inpStr) != NULL) {
        for (int i = 0; i < rooms.size(); i++) {
            int idx = findContainerInRoomidx(rooms[i], inpStr);
            if (idx != -1) {
                rooms[i]->container.erase(rooms[i]->container.begin()+idx);
                return;
            }
        }
    }

    if (findItem(inpStr) != NULL) {
        for (int i = 0; i < rooms.size(); i++) {
            int idx = findItemInRoomidx(rooms[i], inpStr);
            if (idx != -1) {
                rooms[i]->item.erase(rooms[i]->item.begin()+idx);
                return;
            }
        }
    }

    if (findCreature(inpStr) != NULL) {
        for (int i = 0; i < rooms.size(); i++) {
            int idx = findCreatureInRoomidx(rooms[i], inpStr);
            if (idx != -1) {
                rooms[i]->creature.erase(rooms[i]->creature.begin()+idx);
                return;
            }
        }
    }
}

void Update(string inpStr) {
    Room* newRoom = findRoom(inpStr.substr(0, inpStr.find(" to ")));
    if (newRoom != NULL) {
        newRoom->status = inpStr.substr(inpStr.find(" to ") + 4);
        return;
    }

    Container* newContainer = findContainer(inpStr.substr(0, inpStr.find(" to ")));
    if (newContainer != NULL) {
        newContainer->status = inpStr.substr(inpStr.find(" to ") + 4);
        return;
    }

    Item* newItem = findItem(inpStr.substr(0, inpStr.find(" to ")));
    if (newItem != NULL) {
        newItem->status = inpStr.substr(inpStr.find(" to ") + 4);
        return;
    }

    Creature* newCreature = findCreature(inpStr.substr(0, inpStr.find(" to ")));
    if (newCreature != NULL) {
        newCreature->status = inpStr.substr(inpStr.find(" to ") + 4);
        return;
    }
}

void checkAction(string action){
    if(action.find("Add") != string::npos){
        Add(action.erase(0,4));
        return;
    }
    if(action.find("Delete") != string::npos){
        Delete(action.erase(0,7));
        return;
    }
    if(action.find("Update") != string::npos){
        Update(action.erase(0,7));
        return;
    }
    if(action == "Game Over"){
        END = true;
        cout << "Game Over!" << endl;
        return;
    }
    checkInput(action);
}

/*************User Defined Functions - Handle inputs**************/

void chkInventory() {
    if (inventory.size() == 0) {
        cout << "Inventory: empty" << endl;
    }
    else {
        cout << "Inventory: ";
        for(int i = 0; i < inventory.size(); i++) {
            cout << inventory[i];
            if (i != (inventory.size() - 1)) {
                cout << ", ";}

        }
        cout << endl;
    }
}

void grab(string inpStr) {
    for (int i = 0; i < current->item.size(); i++) {
        if (current->item[i] == inpStr) {
            inventory.push_back(current->item[i]);
            current->item.erase(current->item.begin() + i);
            cout << "Item " << inpStr << " added to inventory." << endl;
            return;
        }
    }

    for (int i = 0; i < current->container.size(); i++) {
        Container* newContainer = findContainer(current->container[i]);
        if (newContainer != NULL && newContainer->status == "unlocked") {
            for (int j = 0; j < newContainer->item.size(); j++) {
                if (newContainer->item[j] == inpStr) {
                    current->item.push_back(newContainer->item[j]);
                    newContainer->item.erase(newContainer->item.begin()+j);
                    grab(inpStr);
                    return;
                }
            }
        }
    }

    cout << "Error" << endl;
}

void drop(string inpStr) {
    int flagg = 0;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == inpStr) {
            flagg = 1;
            current->item.push_back(inventory[i]);
            inventory.erase(inventory.begin() + i);
            cout << inventory[i] << " dropped." << endl;
            break;
        }
        if(i == inventory.size()-1 && flagg == 0) {
            cout << "Error" << endl;
        }
    }

    return;
}

void read(string inpStr) {
    int flagg = 0;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == inpStr) {
            flagg = 1;
            Item* newItem = findItem(inpStr);
            if (newItem != NULL && newItem->writing.size() > 0) {
                cout << newItem->writing << endl;
                return;
            }
            else {
                cout << "Nothing written." << endl;
                return;
            }
            break;
        }
        if(i == inventory.size()-1 && flagg == 0) {
            cout << "Error" << endl;
            return;
        }
    }

    cout << "Error" << endl;

    return;
}

void put(string item, string container) {
    int flagg_exist = 0;
    int idx = 0;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == item) {
            flagg_exist = 1;
            idx = i;
        }
    }

    if (flagg_exist == 1) {
        if (current->name == container) {
            drop(item);
            return;
        }
        if (findContainerInRoom(container)) {
            Container* newContainer = findContainer(container);
            if (newContainer != NULL && newContainer->accept.size() == 0) {
                inventory.erase(inventory.begin() + idx);
                newContainer->item.push_back(item);
                if (newContainer->status == "" ) {
                    newContainer->status = "unlocked";
                }
                cout << "Item " << item << " added to " << container << "." << endl;
                return;
            }
            else if (newContainer != NULL) {
                if (existAccept(newContainer, item)) {
                    newContainer->item.push_back(item);
                    inventory.erase(inventory.begin() + idx);
                    if (newContainer->status == "" ) {
                        newContainer->status = "unlocked";
                    }
                    cout << "Item " << item << " added to " << container << "." << endl;
                    return;
                }
            }
            else {
                cout << "Error" << endl;
            }
        }
        else {
            cout << "Error" << endl;
            return;
        }
    }
    cout << "Error" << endl;
    return;
}

void turnon(string inpStr) {
    if (existIteminInventory(inpStr)) {
        Item* newItem = findItem(inpStr);
        if (newItem != NULL && newItem->turnon_flagg) {
            cout << "You activite the " << newItem->name << "." << endl;
            cout << newItem->turnon.print << endl;
            checkAction(newItem->turnon.action);
            return;
        }
    }
    cout << "Error" << endl;
    return;
}

void open(string inpStr) {
    if (!findContainerInRoom(inpStr)) {
        cout << "Error" << endl;
        return;
    }

    Container* newContainer = findContainer(inpStr);
    if (newContainer != NULL && newContainer->status == "locked") {
        cout << newContainer->name << " is locked." << endl;
        return;
    }
    if (newContainer != NULL && newContainer->item.size() == 0) {
        cout << newContainer->name << " is empty." << endl;
        return;
    }

    if (newContainer->status == "") {
        newContainer->status = "unlocked";
    }

    cout << newContainer->name << " contains ";
    for (int i = 0; i < newContainer->item.size(); i++) {
        if (i == newContainer->item.size() - 1) {
            cout << newContainer->item[i] << "." << endl;
        }
        else {
            cout << newContainer->item[i] << ", ";
        }
    }

    return;
}

void attack(string attakee, string weapon) {
    if (!existAttackee(attakee)) {
        cout << "Error" << endl;
        return;
    }

    if (!existIteminInventory(weapon)) {
        cout << "Error"  << endl;
        return;
    }

    if (existCreature(attakee) == -1) {
        cout << "Error"  << endl;
        return;
    }

    if (existCreature(attakee) != -1 && !matchVulner(existCreature(attakee), weapon)) {
        cout << "Error"  << endl;
        return;
    }

    cout << "You assault the " << attakee << " with the " << weapon << "." << endl;

    int idx = existCreature(attakee);
    if (creatures[idx]->attack == NULL) {
        //cout << "Error"  << endl;
        return;
    }



    int flagg_has_item = 0;
    int flagg_match_status = 0;
    if (creatures[idx]->attack->has_condition) {
        Item *newItem = findItem(creatures[idx]->attack->condition.object);
        if (newItem != NULL) {
            flagg_has_item = 1;
            if (newItem->status == creatures[idx]->attack->condition.status) {
                flagg_match_status = 1;
            }
        }

        if (flagg_has_item == 0) {
            Room *newRoom = findRoom(creatures[idx]->attack->condition.object);
            if (newRoom != NULL) {
                flagg_has_item = 1;
                if (newRoom->status == creatures[idx]->attack->condition.status) {
                    flagg_match_status = 1;
                }
            }

            Container *newContainer = findContainer(creatures[idx]->attack->condition.object);
            if (newContainer != NULL) {
                flagg_has_item = 1;
                if (newContainer->status == creatures[idx]->attack->condition.status) {
                    flagg_match_status = 1;
                }
            }

            Creature *newCreature = findCreature(creatures[idx]->attack->condition.object);
            if (newCreature != NULL) {
                flagg_has_item = 1;
                if (newCreature->status == creatures[idx]->attack->condition.status) {
                    flagg_match_status = 1;
                }
            }
        }

        if (flagg_match_status == 0) {
            cout << "Useless" << endl;
            return;
        }
    }



    if (creatures[idx]->attack->has_action) {
        for (int i = 0; i < creatures[idx]->attack->action.size(); i++) {
            checkAction(creatures[idx]->attack->action[i]);
        }
    }

    if(creatures[idx]->attack->has_print){
        cout << creatures[idx]->attack->print << endl;
    }
}

/*void attack(string monster, string weapon){
    //first, check if we have the monster in this room
    int i,j;
    for(i = 0; i < current -> creature.size(); i++){
        if(current -> creature[i] == monster){ break; }
    }
    //if yes, continue, if no, error message
    if(i == current -> creature.size()){
        cout<<"There is no such creature called "<<monster<<" here."<<endl;
        return;
    }
    //second, check if we have the weapon
    for(i = 0; i<inventory.size(); i++){
        if(inventory[i] == weapon){ break; }
    }
    //if yes, continue, if no, error message
    if(i == inventory.size()){
        cout<<"There is no such thing called "<<weapon<<" in your inventory."<<endl;
        return;
    }
    cout<<"You assault the "<<monster<<" with the "<<weapon<<endl;
    //third, check if weapon matches the vulnerability
    for(i = 0; i<creatures.size(); i++){
        if(creatures[i]->name == monster){ break;}
    }
    for(j = 0; j < creatures[i]->vulnerability.size();j++){
        if(creatures[i]->vulnerability[j] == weapon){ break;}
    }
    //if yes, continue, if no, error message
    if(j == creatures[i]->vulnerability.size()){
        cout<<"It seems "<<weapon<<" is useless to "<<monster<<endl;
        return;
    }
    //forth, check if we meet the condition
    if(creatures[i]->attack == NULL){
        return;
    }
    if(creatures[i]->attack->has_condition){
        //-object - can be room/container/creature/item
        string object = creatures[i]->attack->condition.object;
        //-status
        string status = creatures[i]->attack->condition.status;
        bool found = false;
        bool match = false;
        for(j = 0; j < items.size(); j++){
            if(items[j]->name == object){
                found = true;
                match = items[j]->status == status;
                break;
            }
        }
        if(!found){
            for(j = 0; j < rooms.size(); j++){
                if(rooms[j]->name == object){
                    found = true;
                    match = rooms[j]->status == status;
                    break;
                }
            }
        }
        if(!found){
            for(j = 0; j < containers.size(); j++){
                if(containers[j]->name == object){
                    found = true;
                    match = containers[j]->status == status;
                    break;
                }
            }
        }
        if(!found){
            for(j = 0; j < creatures.size(); j++){
                if(creatures[j]->name == object){
                    found = true;
                    match = creatures[j]->status == status;
                    break;
                }
            }
        }
        //if yes, continue, if no, error message
        if(!match){
            cout<<"You need make sure "<<object<<" is "<<status<<endl;
            return;
        }
    }
    //finally, print and take actions(plural)
    if(creatures[i]->attack->has_print){
        cout<<creatures[i]->attack->print<<endl;
    }
    if(creatures[i]->attack->has_action){
        for(j = 0; j<creatures[i]->attack->action.size();j++){
            checkAction(creatures[i]->attack->action[j]);
        }
    }
}*/


/********************User input manager***************************/
void checkInput(string input){
    if(input == "n" || input == "s" || input == "w" || input == "e"){
        toAnotherRoom(input);
        return;
    }
    if(input == "i"){
        chkInventory();
        return;
    }
    //take
    if(input == "take"){
        cout<<"What do you want to take? ";
        getline(cin, input);
        grab(input);
        return;
    }
    if(input.find("take") != string::npos){
        input.erase(0,5);
        grab(input);
        return;
    }
    //drop
    if(input == "drop"){
        cout<<"What do you want to drop? ";
        getline(cin, input);
        drop(input);
        return;
    }
    if(input.find("drop") != string::npos){
        input.erase(0,5);
        drop(input);
        return;
    }
    //read
    if(input == "read"){
        cout<<"What do you want to read? ";
        getline(cin, input);
        read(input);
        return;
    }
    if(input.find("read") != string::npos){
        input.erase(0,5);
        read(input);
        return;
    }
    //open
    if(input == "open"){
        cout<<"What do you want to open? ";
        getline(cin, input);
        if(input == "exit"){
            if(current -> type == "exit"){
                END = true;
                cout << "Game Over" << endl;
            }
            else {
                cout << "Error" << endl;
            }
            return;
        }
        open(input);
        return;
    }
    if(input.find("open") != string::npos){
        input.erase(0,5);
        if(input == "exit"){
            if(current -> type == "exit"){
                END = true;
                cout << "Game Over" << endl;
            }
            else {
                cout << "Error" << endl;
            }
            return;
        }
        open(input);
        return;
    }
    //put
    if(input == "put"){
        cout << "What do you want to put? ";
        getline(cin, input);
        string put_item = input;
        cout << "Where do you want to put in? ";
        getline(cin, input);
        string put_into = input;
        put(put_item, put_into);
        return;
    }
    if(input.find("put") != string::npos){
        input.erase(0,4);
        int space_pos = input.find(" "); //it's also size of item string
        string put_item = input.substr(0, space_pos);
        input.erase(0, space_pos + 4);
        string put_into = input;
        put(put_item, put_into);
        return;
    }
    //turn on
    if(input == "turn on"){
        cout<<"What do you want to turn on? ";
        getline(cin, input);
        turnon(input);
        return;
    }
    if(input.find("turn on") != string::npos){
        input.erase(0,8);
        turnon(input);
        return;
    }
    //attack
    if(input == "attack"){
        cout << "What do you want to attack? ";
        getline(cin, input);
        string monster = input;
        cout << "What do you want to attack with? ";
        getline(cin, input);
        string weapon = input;
        attack(monster, weapon);
        return;
    }
    if(input.find("attack") != string::npos){
        input.erase(0,7);
        int space_pos = input.find(" "); //it's also size of item string
        string monster = input.substr(0, space_pos);
        input.erase(0, space_pos + 6);
        string weapon = input;
        attack(monster, weapon);
        return;
    }
    cout << "Error" << endl;
}

/***********************For my triggers***************************/
string findType(string inpStr){
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i] -> name == inpStr){
            return "Room";
        }
    }
    for(i = 0; i < items.size(); i++){
        if(items[i] -> name == inpStr){
            return "Item";
        }
    }
    for(i = 0; i < containers.size(); i++){
        if(containers[i] -> name == inpStr){
            return "Container";
        }
    }
    for(i = 0; i < creatures.size(); i++){
        if(creatures[i] -> name == inpStr){
            return "Creature";
        }
    }
    return NULL;
}

void has_pa(Trigger* t){
    int i = 0;
    if(t->has_print){
        cout << t->print << endl;
    }
    if(t->has_action){
        for(i = 0; i < t->action.size(); i++){
            checkAction(t->action[i]);
        }
    }
}

bool findRoomTwoTrigger(Trigger* t){
    int i = 0;
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i]->name == t->status.object){
            if(rooms[i]->status == t->status.status){
                has_pa(t);
                return true;
            }
        }
    }
    return false;
}

bool findItemTwoTrigger(Trigger* t){
    int i = 0;
    for(i = 0; i < items.size(); i++){
        if(items[i]->name == t->status.object){
            if(items[i]->status == t->status.status){
                has_pa(t);
                return true;
            }
        }
    }
    return false;
}

bool findContainerTwoTrigger(Trigger* t){
    int i = 0;
    for(i = 0; i < containers.size(); i++){
        if(containers[i]->name == t->status.object){
            if(containers[i]->status == t->status.status){
                has_pa(t);
                return true;
            }
        }
    }
    return false;
}

bool findCreatureTwoTrigger(Trigger* t){
    int i = 0;
    for(i = 0; i < creatures.size(); i++){
        if(creatures[i]->name == t->status.object){
            if(creatures[i]->status == t->status.status){
                has_pa(t);
                return true;
            }
        }
    }
    return false;
}

bool twoCondTrigger(Trigger* t){
    bool output = false;
    string object_type = findType(t->status.object);
    if(object_type == "Room"){
        output = findRoomTwoTrigger(t);
    }
    if(object_type == "Item"){
        output = findItemTwoTrigger(t);
    }
    if(object_type == "Container"){
        output = findContainerTwoTrigger(t);
    }
    if(object_type == "Creature"){
        output = findCreatureTwoTrigger(t);
    }
    return output;
}

bool findRoomThreeTrigger(Trigger* t){
    int i = 0;
    int j = 0;
    string object_type = findType(t->owner.object);
    for(i = 0; i < rooms.size(); i++){
        if(rooms[i] -> name == t->owner.owner){
            if(object_type == "Item"){
                for(j = 0; j < rooms[i] -> item.size(); j++) {
                    if (rooms[i]->item[j] == t->owner.object && t->owner.has == "yes") {
                        has_pa(t);
                        return true;
                    }
                    if (rooms[i]->item[j] == t->owner.object && t->owner.has == "no") {
                        return false;
                    }
                }
                if(j == rooms[i]->item.size() && t->owner.has == "no") {
                    has_pa(t);
                    return true;
                }
                if(j == rooms[i]->item.size() && t->owner.has == "yes") {
                    return false;
                }
            }
            if(object_type == "Container"){
                for(j = 0; j < rooms[i] -> container.size(); j++){
                    if(rooms[i]->container[j]== t->owner.object && t->owner.has == "yes") {
                        has_pa(t);
                        return true;
                    }
                    if(rooms[i]->container[j]== t->owner.object && t->owner.has == "no"){
                        return false;
                    }
                }
                if(j == rooms[i]->container.size() && t->owner.has == "no") {
                    has_pa(t);
                    return true;
                }
                if(j == rooms[i]->container.size() && t->owner.has == "yes"){
                    return false;
                }
            }
            if(object_type == "Creature"){
                for(j = 0; j < rooms[i] -> creature.size(); j++){
                    if(rooms[i]->creature[j]== t->owner.object && t->owner.has == "yes") {
                        has_pa(t);
                        return true;
                    }
                    if(rooms[i]->creature[j]== t->owner.object && t->owner.has == "no"){
                        return false;
                    }
                }
                if(j == rooms[i]->creature.size() && t->owner.has == "no") {
                    has_pa(t);
                    return true;
                }
                if(j == rooms[i]->creature.size() && t->owner.has == "yes"){
                    return false;
                }
            }
        }
    }
    return false;
}

bool findContainerThreeTrigger(Trigger* t){
    int i = 0;
    int j = 0;
    for(i = 0; i < containers.size(); i++){
        if(containers[i]->name == t->owner.owner){
            for(j = 0; j < containers[i] -> item.size(); j++){
                if(containers[i]->item[j]== t->owner.object && t->owner.has == "yes") {
                    has_pa(t);
                    return true;
                }
                if(containers[i]->item[j]== t->owner.object && t->owner.has == "no"){
                    return false;
                }
            }
            if(j == containers[i]->item.size() && t->owner.has == "no") {
                has_pa(t);
                return true;
            }
            if(j == containers[i]->item.size() && t->owner.has == "yes"){
                return false;
            }
        }
    }
    return false;
}

bool threeCondTrigger(Trigger * t){
    //if owner == object && has == yes || owner != object && has == no -> trigger activated
    int i = 0;
    bool output = false;
    if(t->owner.owner == "inventory"){
        for(i = 0; i < inventory.size(); i++){
            if(inventory[i] == t->owner.object && t->owner.has == "yes") {
                has_pa(t);
                return true;
            }
            if (inventory[i] == t->owner.object && t->owner.has == "no"){
                return false;
            }
        }
        if(i == inventory.size() && t->owner.has == "no") {   // owner != object
            has_pa(t);
            return true;
        }
        if (i == inventory.size() && t->owner.has == "yes"){
            return false;
        }
    }
    string owner_type = findType(t->owner.owner);
    if(owner_type == "Room"){
        output = findRoomThreeTrigger(t);
    }
    if(owner_type == "Container") {
        output = findContainerThreeTrigger(t);
    }
    return output;
}

bool chkRoomTrigger(Trigger* t){
    bool chkRoom = false;
    if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
        if(t->condition == 2) {
            chkRoom = twoCondTrigger(t);
        }
        else if(t->condition == 3) {
            chkRoom = threeCondTrigger(t);
        }
        if(chkRoom){
            t->times++;
        }
    }
    return chkRoom;
}

bool chkItemTrigger(Trigger* t){
    bool chkItem = false;
    if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
        if(t->condition == 2) {
            chkItem = twoCondTrigger(t);
        }
        else if(t->condition == 3) {
            chkItem = threeCondTrigger(t);
        }
        if(chkItem){
            t->times++;
        }
    }
    return chkItem;
}

bool chkContainerTrigger(Trigger* t){
    bool chkContainer = false;
    if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
        if(t->condition == 2) {
            chkContainer = twoCondTrigger(t);
        }
        else if(t->condition == 3) {
            chkContainer = threeCondTrigger(t);
        }
        if(chkContainer){
            t->times++;
        }
    }
    return chkContainer;
}

bool chkCreatureTrigger(Trigger* t){
    bool chkCreature = false;
    if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
        if(t->condition == 2) {
            chkCreature = twoCondTrigger(t);
        }
        else if(t->condition == 3) {
            chkCreature = threeCondTrigger(t);
        }
        if(chkCreature){
            t->times++;
        }
    }
    return chkCreature;
}

bool findTrigger(int cmd, string input){
     /*
      * cmd = 0 -> no command; cmd = 1 -> with command
      * Check all with command triggers
      * if type == "permanent" || type == "single" && has not been accessed before
      * check the condition, go to twoCondTrigger or threeCondTrigger
      */
    int i = 0;
    int j = 0;
    int k = 0;
    bool chkRoom = false;
    bool chkItem = false;
    bool chkContainer = false;
    bool chkCreature = false;
    Trigger *t;
    //current room trigger
    if(current -> trigger.size() != 0){
        for(j = 0; j < current->trigger.size(); j++){
            t = current->trigger[j];
            if(cmd == 0){
                if(!t->has_command){
                    chkRoom = chkRoomTrigger(t);
                }
            }
            else if(cmd == 1) {
                if (t->has_command && input == t->command) {
                    chkRoom = chkRoomTrigger(t);
                }
            }
        }
    }
    //inventory's item trigger
    for(i = 0; i < inventory.size(); i++){
        string target = inventory[i];
        for(j = 0; j < items.size(); j++){
            if(items[j] -> name == target){
                for(k = 0; k < items[j] -> trigger.size(); k++) {
                    t = items[j]->trigger[k];
                    if(cmd == 0){
                        if(!t->has_command){
                            chkItem = chkItemTrigger(t);
                        }
                    }
                    else if (cmd == 1) {
                        if (t->has_command && input == t->command) {
                            chkItem = chkItemTrigger(t);
                        }
                    }
                }
            }
        }
    }
    //current room's container trigger
    for(i = 0; i < current -> container.size(); i++){
        string target = current -> container[i];
        for(j = 0; j < containers.size(); j++){
            if(containers[j] -> name == target){
                for(k = 0; k < containers[j] -> trigger.size(); k++){
                    t = containers[j] -> trigger[k];
                    if(cmd == 0){
                        if(!t->has_command){
                            chkContainer = chkContainerTrigger(t);
                        }
                    }
                    else if(cmd == 1) {
                        if (t->has_command && input == t->command) {
                            chkContainer = chkContainerTrigger(t);
                        }
                    }
                }
            }
        }
    }
    //current room's creature trigger
    for(i = 0; i < current -> creature.size(); i++){
        string target = current -> creature[i];
        for(j = 0; j < creatures.size(); j++){
            if(creatures[j] -> name == target){
                for(k = 0; k < creatures[j] -> trigger.size(); k++){
                    t = creatures[j] -> trigger[k];
                    if(cmd == 0){
                        if(!t->has_command) {
                            chkCreature = chkCreatureTrigger(t);
                        }
                    }
                    else if(cmd == 1) {
                        if (t->has_command && input == t->command) {
                            chkCreature = chkCreatureTrigger(t);
                        }
                    }
                }
            }
        }
    }
    return (chkRoom||chkItem||chkContainer||chkCreature);
}

#endif