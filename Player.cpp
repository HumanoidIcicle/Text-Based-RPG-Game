//
// Created by JOSS0001 on 2025-12-03.
//

#include <algorithm>
#include <iostream>
#include <utility>

#include "Player.h"
#include "ITEM.h"
#include "ENEMY.h"

using namespace std;


class ITEM;
int Player::getHp() const {
    return hp;
}
int Player::getDefense() const {
    return defense;
}
void Player::setHp(int newHp) {
    hp = newHp;
}
void Player::damageTaken(int d) {
    hp -= d;
}
void Player::setWeapon(string w) {
    weaponName = move(w);
}
void Player::setAttack(int dam) {
    baseAttack = dam;
}
string Player::getWeapon() const {
    return weaponName;
}
int Player::getMaxHp() const {
    return maxHp;
}
int Player::getFull() {
    return invSize;
}
void Player::setSize(int f) {
    invSize -= f;
}
void Player::addItem(unique_ptr<ITEM> item) {
    inventory.push_back(move(item));
    invSize = inventory.size();
}
void Player::stats() {
    cout <<endl
    << "-----------------"<< endl
    << "My stats: \n"
    << "  HP: " << hp << endl
    << "  Max HP: " << maxHp << endl
    << "  Shield: " << defense << endl
    << "  Base attack: " << baseAttack << endl
    << "  Weapon: " << weaponName << endl
    << "-----------------"<< endl; 
    
}
void Player::playerAttack(ENEMY& enemy) {
    enemy.setEnHP(max(1, baseAttack-enemy.getDef()));
    cout << "\nYou hit the enemy. \nEnemy hp: " << ((enemy.getEnHP()< 0)? 0: enemy.getEnHP()) <<endl;
}
void Player::showItems() {
    if (!inventory.empty()){
        cout << "\n    - Items in inventory:\n";
        for (auto& item: inventory)
            item->itemInfo();
        cout << "\nNumber of items in inventory: " << inventory.size() << endl;
    }
    else cout << "\nOops! Your inventory is empty.\n";
}
bool Player::findKey(const string& name) {
    for (auto iter = inventory.begin(); iter != inventory.end(); ++iter){
        if ((*iter)->getName() == name && (*iter)->getType() == "KEY") {
            (*iter)->use(*this);
            setSize(1);
            inventory.erase(iter);
            return true;
        }
    }
    return false;
}
void Player::heal(const string& id) {
    string found;
    for (auto iter = inventory.begin(); iter != inventory.end(); ++iter){
        if ((*iter)->getId() == id && (*iter)->getType() == "CONSUMABLE") {
            found = (*iter)->getName();
            (*iter)->use(*this);
            inventory.erase(iter);
            setSize(1);
            cout << "\nHealth restored (a little bit)." <<endl;
            break;
        }
    }
    if (found.empty()) cout << "Consumable not available in inventory.\n";
}

void Player::equip(const string& id) {
    string found;
    for (auto& item: inventory) {
        if (item->getId() == id && item->getType() == "WEAPON") {
            found = item->getName();
            item->use(*this);
            cout << "\nWeapon equipped." << endl;
            break;
        }
    }
    if (found.empty()) cout << "\nNo weapon with given ID in inventory.\n";
}


