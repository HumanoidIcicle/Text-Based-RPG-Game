//
// Created by JOSS0001 on 2025-12-03.
//

#include "WEAPON.h"

WEAPON::WEAPON(string type, string name, string id, int dam)
    : ITEM(type, name, id), damage(dam) {}

int WEAPON::getValue() {
    return damage;
}
//NEED REVISIT
void WEAPON::use(Player& player) {
    player.setAttack(damage);
    player.setWeapon(name);
}

void WEAPON::itemInfo() const {
    cout <<endl;
    cout << "->Type: " << type << endl;
    cout << "  Name: " << name << endl;
    cout << "  Damage: " << damage << endl;
    cout << "  ID: " << id << endl;
}

