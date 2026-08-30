//
// Created by JOSS0001 on 2025-12-03.
//

#include "CONSUMABLE.h"

CONSUMABLE::CONSUMABLE(string type, string name, string id)
    : ITEM(type, name, id) {}

int CONSUMABLE::getValue() {
    return health;
}
//NEED REVISIT
void CONSUMABLE::use(Player& player) {
    int got = player.getHp();
    got += health;
    player.setHp(got <= player.getMaxHp()?got:player.getMaxHp());
}
