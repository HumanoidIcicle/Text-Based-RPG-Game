//
// Created by JOSS0001 on 2025-12-03.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "ENEMY.h"

using namespace std;

class ITEM;

class Player{
protected:
    int hp = 30;
    int maxHp = 30;
    int baseAttack = 2;
    int defense = 1;
    string weaponName = "None";

    vector<unique_ptr<ITEM> > inventory;
    int invSize = 0;
public:
    int getHp() const;
    int getMaxHp() const;
    int getFull();
    void setSize(int f) ;
    int getDefense() const;
    string getWeapon() const;
    void setHp(int newHp);
    void setWeapon(string w);
    void setAttack(int dam);
    void addItem(unique_ptr<ITEM> item);

    void stats();
    void showItems();
    bool findKey(const string& name);
    void equip(const string& id);
    void heal(const string& id);
    void playerAttack(ENEMY& enemy);

    void damageTaken(int d);
};

#endif //PLAYER_H
