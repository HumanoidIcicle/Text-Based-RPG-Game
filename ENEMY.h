//
// Created by JOSS0001 on 2025-12-03.
//
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using namespace std;

class Player;

class ENEMY {
protected:
    int enemyHp;
    int enemyAttack;
    string ID;
    int defence;
    int maxHp;
    int turn;

    float hitChance ;//= 0.8f;
    float critChance ;// = 0.2f;
public:
    virtual ~ENEMY() = default;
    ENEMY(string id, int hp, int attack, int def, float hit, float crit);
    virtual bool isBoss() {return false;}

    int getEnHP() const;
    int getDef() const;
    virtual int getTurn() { return 0; }
    virtual void setTurn(int t) {}
    int getMaxHp() const {return maxHp;}
    string getName() const { return ID;}
    void setEnHP(int taken);
    bool attackHit(float chance);
    bool criticalHit(float chance);
    void description() const;
    virtual void takeTurn(Player& player) = 0;
    virtual void dropLoot(Player& p) = 0;
    virtual void specialAttack(Player& p) = 0;
    virtual void phase2(Player& p){}
};

class GOBLIN: public ENEMY {
public:
    GOBLIN(string id, int hp, int attack, int def, float hit, float crit);
    void dropLoot(Player &p) override;
    void takeTurn(Player &player) override;
    void specialAttack(Player &p) override;
};

class SKELETON: public ENEMY {
public:
    SKELETON(string id, int hp, int attack, int def, float hit, float crit);
    void dropLoot(Player &p) override;
    void takeTurn(Player &player) override;
    void specialAttack(Player &p) override;
};

class BOSS: public ENEMY {
    int bossTurn;
public:
    BOSS(string id, int hp, int attack, int def, float hit, float crit);

    bool isBoss() override;
    int getTurn() override ;
    void setTurn(int t) override;
    void dropLoot(Player &p) override;
    void takeTurn(Player &player) override;
    void specialAttack(Player &p) override;
    void phase2(Player& p) override;
};
#endif //ENEMY_H
