//
// Created by JOSS0001 on 2025-12-03.
//

#include "ilo.h"
#include "Room.h"
#include "Game.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <memory>

#include <map>
#include <vector>

#include "CONSUMABLE.h"

using namespace std;

typedef struct {
    string name;
    int hp;
    int def;
    int atk;
    float crit, hit;
} Enemy;

void FileIO::readCatalog(string filename, vector<unique_ptr<ITEM>>& allItems, vector<unique_ptr<ENEMY>>& allEnemies) {
    string store_line;
    ifstream  file_to_read(filename);

    if (!file_to_read) {
        cerr << "Could not read file\n";
        return;
    }
    //vector<unique_ptr<ITEM>> items;

    while (getline(file_to_read, store_line)) {
        if (!store_line.empty()) {
            transform(store_line.begin(), store_line.end(), store_line.begin(), ::toupper);
            
            stringstream parts(store_line);
            string cat, name, type, id, damage;

            getline(parts, cat, ';');
            if (cat == "ITEM"){
                getline(parts, name, ';');
                getline(parts, type, ';');
                getline(parts, id, ';');
                getline(parts, damage);

                if (type == "WEAPON") allItems.push_back(move(make_unique<WEAPON>(type, name, id, stoi(damage))));
                if (type == "KEY") allItems.push_back(move(make_unique<KEY>(type, name, id)));
                if (type == "CONSUMABLE") allItems.push_back(move(make_unique<CONSUMABLE>(type, name, id)));
            }
            else if (cat == "ENEMY") {
                Enemy en;
                string stats;
                getline(parts, name, ';');
                getline(parts, stats);

                en.name = name;

                stringstream split_stats(stats);
                string split_comma;

                vector<string> m_stats;

                while (getline(split_stats, split_comma, ':')) {
                    m_stats.push_back(split_comma);
                }

                for (auto stat: m_stats) {
                    stringstream split_equal(stat);
                    string key, value;

                    getline(split_equal, key, '=');
                    getline(split_equal, value);

                    if (key == "HP") en.hp = stoi(value);
                    if (key == "CRIT") en.crit = stof(value);
                    if (key == "HIT") en.hit = stof(value);
                    if (key == "DEF") en.def = stoi(value);
                    if (key == "ATK") en.atk = stoi(value);
                }
                if (name == "GOBLIN") allEnemies.push_back(move(make_unique<GOBLIN>(en.name, en.hp, en.atk,en.def, en.hit, en.crit )));
                if (name == "SKELETON") allEnemies.push_back(move(make_unique<SKELETON>(en.name, en.hp, en.atk,en.def, en.hit, en.crit )));
                if (name == "BOSS") allEnemies.push_back(move(make_unique<BOSS>(en.name, en.hp, en.atk,en.def, en.hit, en.crit )));
            }
        }
    }
    file_to_read.close();
}

void FileIO::readRooms(string filename,
    vector<unique_ptr<ENEMY>>& all_enemies,
    map<string, shared_ptr<Room>>& game_rooms,
    vector<unique_ptr<ITEM>>& all_items)
{
    ifstream file(filename);
    if (!file) {
        cerr << "Could not read file\n";
        return;
    }

    string store;
    while (getline(file, store)) {
        if (!store.empty()) {
            transform(store.begin(), store.end(), store.begin(), ::toupper);

            stringstream first(store);

            string id, name, description, north, east, south, west, items, enemies;
            getline(first, id, ';');
            getline(first, name, ';');
            getline(first, description, ';');

            getline(first, north, ';');
            getline(first, east, ';');
            getline(first, south, ';');
            getline(first, west, ';');

            getline(first, items, ';');
            getline(first, enemies);

            string r_items, r_enemies;

            shared_ptr<Room> room = make_shared<Room>(name, description);

            if (north != " " && !north.empty()) room->addExit("n", north);
            if (east != " " && !east.empty()) room->addExit("e", east);
            if (south != " " && !south.empty()) room->addExit("s", south);
            if (west != " " && !west.empty()) room->addExit("w", west);
            
            if (enemies != " " && !enemies.empty()) r_enemies = enemies;
            if (items != " " && !items.empty()) r_items = items;

            if (r_items != " " && !r_items.empty()){
                string item_name;
                stringstream div_items(r_items);
                while (getline(div_items, item_name, '|')) {
                    for (auto it = all_items.begin(); it != all_items.end(); ++it) {
                        if (*it && (*it)->getName() == item_name) {
                            room->addItem(move(*it));
                            all_items.erase(it);
                            break;
                        }
                    }
                }
            }
            if (r_enemies != " " && !r_enemies.empty()){
                string en_name;
                stringstream div_enemies(r_enemies);
                while (getline(div_enemies, en_name, '|')) {
                    for (auto& enemy : all_enemies) {
                        if (!enemy) continue;
                        if (enemy->getName() == en_name) {
                            room->addEnemy(move(enemy));
                            break;
                        }
                    }
                }
            }
            game_rooms.insert({id, room}); //finally add room to game

        }
    }

}

