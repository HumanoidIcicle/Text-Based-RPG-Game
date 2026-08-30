//
// Created by JOSS0001 on 2025-12-03.
//

#include "Room.h"
#include "ITEM.h"


#include <string>
#include <map>
#include <iostream>
#include <memory>

using namespace std;

Room::Room(string name, string desc)
    : name(move(name)), description(move(desc)) {}

void Room::describe() const {
    cout << "\n=*=*=*=*=*=*=*=*=*=*=*=*";
    cout << "\nCurrent room: " << name << endl;
    cout << " -> " << description << endl;
    showItems();
    showEnemies();
    showExits();
}
map<string, string>& Room::getExits() {
    return exits;
}
bool Room::isLocked() const{
    return locked;
}
string Room::getKey() const {
    return needKey;
}
void Room::setKey(string key) {
    needKey = move(key);
}

void Room::setLock(bool yes) {
    locked = yes;
}
vector<unique_ptr<ITEM>>& Room::getItems() {
    return items;
}
vector<unique_ptr<ENEMY>>& Room::getEnemies() {
    return enemies;
}
string Room::getName() const {
    return name;
}
void Room::addItem(unique_ptr<ITEM> item) {
    items.push_back(move(item));
}
void Room::addEnemy(unique_ptr<ENEMY> enemy) {
    enemies.push_back(move(enemy));
}
void Room::addExit(string dir, string id) {
    exits.insert({dir, id});
}
void Room::showExits() const {
    cout << "\n--------------------";
    cout << "\nAvailable exits: " << endl;
    for (auto exit: exits) {
        cout << " - " << exit.second << "(" << exit.first << ")\n";
    }
}
void Room::showItems() const {
    if (!items.empty()){
        cout << "\n--------------------";
        cout << "\nItems in room:";
        for (auto& item: items) {
            if ( item == nullptr) continue;
            item->itemInfo();
        }
    }
    else cout << "\n > This room has no collectibles.\n";
}
void Room::showEnemies() const {
    if (!enemies.empty()) {
        cout << "\n--------------------";
        cout << "\nCurrent residents: ";
        for (auto& enemy: enemies) {
            enemy->description();
        }
    }
    else cout << "\n > No threats in this room." << endl;
}

