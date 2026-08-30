//
// Created by JOSS0001 on 2025-12-03.
//

#ifndef ILO_H
#define ILO_H

#include <memory>
#include <fstream>

#include "Room.h"

using namespace std;

class FileIO {
public:
    void readRooms(string filename,
        vector<unique_ptr<ENEMY>>& all_enemies,
        map<string, shared_ptr<Room>>& game_rooms,
        vector<unique_ptr<ITEM>>& all_items);

    void readCatalog(string filename,
        vector<unique_ptr<ITEM>>& allItems,
        vector<unique_ptr<ENEMY>>& allEnemies);
};

#endif //ILO_H
