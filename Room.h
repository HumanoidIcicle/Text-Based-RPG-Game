//
// Created by JOSS0001 on 2025-12-03.
//

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "ENEMY.h"
#include "ITEM.h"
using namespace std;

class Room {
protected:
    string name;
    string description;
    map<string, string> exits; //"n" -> "R2"
    bool locked = false;
    string needKey;

    vector<unique_ptr<ITEM>> items;
    vector<unique_ptr<ENEMY>> enemies;
public:
    ~Room()= default;
    Room(string name, string desc);

    bool isLocked() const;
    string getKey() const;
    void setKey(string key);
    void setLock(bool yes);
    void describe() const;
    
    void addExit(string dir, string id);
    string getName() const;
    map<string, string>& getExits();
    vector<unique_ptr<ITEM>>& getItems();
    vector<unique_ptr<ENEMY>>& getEnemies();
    void showExits() const;
    void addItem(unique_ptr<ITEM> item);

    void addEnemy(unique_ptr<ENEMY> enemy);
    void showEnemies() const;
    void showItems() const;
};

#endif //ROOM_H
