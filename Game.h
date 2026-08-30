//
// Created by JOSS0001 on 2025-12-03.
//

#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <string>

#include "ITEM.h"
#include "WEAPON.h"
#include "Player.h"
#include "ENEMY.h"
#include "Room.h"


using namespace std;

class Game {
protected:
    map<string, shared_ptr<Room>> rooms; //roomId -> Room
    map<string, unique_ptr<ITEM>> items; //itemName -> item

    Player* player;
    shared_ptr<Room> currentRoom;

public:
    void initializeWorld(Player* p); //Create the amazing world
    void addItem(unique_ptr<ITEM> item);

    //OPTIONS
    void menu();
    void look(); //the describe in room class
    void go(string dir);// in Game class
    void pickUp(); //add items in room, calls addItem, to player inventory
    void inventory();//ready in player
    void equip(string id);//ready in player
    void use(string id); //the heal in player class
    void help(); //print menu
    void exit(bool* keep_playing); //Ends the game
    void youPlaying(bool keep_playing, int& num_turns, bool& turn); //Start
};
#endif //GAME_H
