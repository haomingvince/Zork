#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "rapidxml.hpp"
#include "executioner.hpp"
#include "item.hpp"
#include "room.hpp"
#include "trigger.hpp"
#include "creature.hpp"
#include "container.hpp"
#include "attack.hpp"

using namespace std;

vector<Room*> rooms;
vector<Container*> containers;
vector<Creature*> creatures;
vector<Item*> items;
vector<String> inventory;