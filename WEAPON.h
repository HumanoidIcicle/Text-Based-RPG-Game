//
// Created by JOSS0001 on 2025-12-03.
//

#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "ITEM.h"
#include "Player.h"

using namespace std;

class WEAPON: public ITEM {
protected:
    int damage;

public:
    WEAPON(string type, string name, string id, int dam);
    int getValue() override;
    void use(Player& player) override;
    void itemInfo() const override;
};

#endif //WEAPON_H
