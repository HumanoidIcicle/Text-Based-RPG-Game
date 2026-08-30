//
// Created by JOSS0001 on 2025-12-03.
//

#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include <string>
#include "ITEM.h"
#include "Player.h"

using namespace std;

class CONSUMABLE: public ITEM{
protected:
    int health = 10;

public:
    CONSUMABLE(string type, string name, string id);
    int getValue()override;
    void use(Player& player) override;
};

#endif //CONSUMABLE_H
