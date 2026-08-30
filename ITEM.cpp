//
// Created by JOSS0001 on 2025-12-03.
//

#include <iostream>
#include "ITEM.h"
#include "Player.h"

using namespace std;

ITEM::ITEM(string type, string name, string id)
    : type(move(type)), name(move(name)), id(move(id)){}

KEY::KEY(string type, string name, string id) : ITEM(type, name, id){}
void KEY::use(Player &player) {
    cout << endl << name <<" key was used.\n";
}

void ITEM::itemInfo() const{
    cout <<endl;
    cout << "->Type: " << type << endl;
    cout << "  Name: " << name << endl;
    cout << "  ID: " << id << endl;
}

string ITEM::getId() const {
    return id;
}
string ITEM::getName() const {
    return name;
}
string ITEM::getType() const {
    return type;
}
int ITEM::getValue() {
    return 0;
}
