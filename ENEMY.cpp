//
// Created by JOSS0001 on 2025-12-03.
//

#include <iostream>
#include <random>

#include "ENEMY.h"

#include "CONSUMABLE.h"
#include "Player.h"
#include "ITEM.h"
#include "WEAPON.h"

class Player;
using namespace std;

random_device rd;
mt19937 rng(rd());
uniform_real_distribution<double> dist(0.0,1.0);

bool ENEMY::attackHit(float chance) {
    return dist(rng) < chance;
}
bool ENEMY::criticalHit(float chance) {
    return dist(rng) < chance;
}
bool drop() {
    return dist(rng) < 0.5;
}

int ENEMY::getEnHP() const {
    return enemyHp;
}
int ENEMY::getDef() const {
    return defence;
}
void ENEMY::setEnHP(int taken) {
    enemyHp -= taken;
}
ENEMY::ENEMY(string id, int hp, int attack, int def, float hit, float crit)
    : ID(move(id)), enemyHp(hp), maxHp(hp),enemyAttack(attack),
defence(def), hitChance(hit), critChance(crit){}

GOBLIN::GOBLIN(string id, int hp, int attack, int def, float hit, float crit)
    : ENEMY(id, hp,attack, def, hit, crit){}
SKELETON::SKELETON(string id, int hp, int attack, int def, float hit, float crit)
    : ENEMY(id, hp,attack, def, hit, crit){}

void ENEMY::description() const{
    cout <<endl;
    cout << ">>Rank: " << ID << endl;
    cout << "  HP: " << enemyHp << endl;
    cout << "  Attack damage: " << enemyAttack << endl;
}

void GOBLIN::dropLoot(Player &p) {
    if (drop()) {
        p.addItem(make_unique<CONSUMABLE>("CONSUMABLE", "CLARICE'S SILENT LAMB", "31"));
        cout << "\nGoblin dropped surprise in your inventory.\n";
    }
}
void GOBLIN::takeTurn(Player &player) {
    if (!attackHit(hitChance)) {
        cout << "\n*** Phew...A swing and miss by Goblin. ***"<< endl;
        return;
    }
    int attack = enemyAttack;
    if (criticalHit(critChance)) {
        attack *= 1.3;
        cout << "\n->Woooaaaah!!! Critical hit.";
    }
    else cout << "\n*** Oof! Skilled enemy. You got hit. ***";
    player.damageTaken(max(1, attack-player.getDefense()));
}
void GOBLIN::specialAttack(Player &p) {
    int attack = 0.7 * enemyAttack;
    for (int i = 0; i < 2; i++) {
        p.damageTaken(attack);
    }
    cout << "\n*** Angry goblin double hit combooooo ***"<< endl;
}

void SKELETON::dropLoot(Player &p) {
    if (drop) {
        p.addItem(make_unique<CONSUMABLE>("CONSUMABLE", "HANNIBAL LECTER-CUISINE", "30"));
        cout << "\nSkeleton enemy dropped consumable to your inventory.\n";
    }
}
void SKELETON::takeTurn(Player &player) {
    if (!attackHit(hitChance)) {
        cout << "\n*** Tsst...Luck or skill? Skeleton missed. ***"<< endl;
        return;
    }
    int attack = enemyAttack;
    if (criticalHit(critChance)) {
        attack *= 1.2;
        cout << "\n->Woooaaaah!!! Critical hit.";
    }
    else cout << "\n*** Oof! Not so quick...You got hit. ***";
    player.damageTaken(max(1, attack-player.getDefense()));
}
void SKELETON::specialAttack(Player &p) {
    if (criticalHit(critChance)) {
        int attack = 1.4 * enemyAttack;
        p.damageTaken(attack);
        cout << "\n*** SPECIAL-OPS: Skeleton got a bone to pick  ***"<< endl;
    }
    else
        takeTurn(p);
}

/*The boss attacks*/
BOSS::BOSS(string id, int hp, int attack, int def, float hit, float crit)
: ENEMY(id, hp,attack, def, hit, crit){}

bool BOSS::isBoss() {
    return true;
}
int BOSS::getTurn() {
    return bossTurn;
}
void BOSS::setTurn(int t) {
    bossTurn += t;
}
void BOSS::dropLoot(Player &p) {
    p.addItem(make_unique<KEY>("KEY", "AUDREY HEPBURN-KEY", "90"));
    cout << "\n ->> You have acquired the AUDREY HEPBURN-KEY <<-\n";
}
void BOSS::takeTurn(Player &player) {
    if (!attackHit(hitChance)) {
        cout << "\n*** Phew...Enemy missed. ***"<< endl;
        return;
    }
    int attack = enemyAttack;
    if (criticalHit(critChance)) {
        attack *= 1.5;
        cout << "\n->Woooaaaah!!! Critical hit.";
    }
    else
        cout << "\n*** Oof! Boss be like: Got you back, Mwaaahahaha. ***";
    player.damageTaken(max(1, attack-player.getDefense()));
}
void BOSS::specialAttack(Player &p) {
    int attack = 1.2 * enemyAttack;
    p.damageTaken(attack);
    cout << "\n*>*>* Special boss atk: The Silent Killer. *<*<*"<< endl;
}
void BOSS::phase2(Player &p) {
    if (!attackHit(hitChance)) {//Increase hit chance
        cout << "\n*** Not so Bossy...He missed. ***"<< endl;
        return;
    }
    int attack = enemyAttack;
    if (criticalHit(critChance)) { //increase critical hit chance
        attack *= 1.4; //And increase damage
        cout << "\n->Woooaaaah!!! Critical hit (Improved).";
    }
    else
        cout << "\n*** Oof! Boss be like: Got you back, Mwaaahahaha. ***";
    p.damageTaken(max(1, attack-p.getDefense()));
}




