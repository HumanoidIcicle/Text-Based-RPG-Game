//
// Created by JOSS0001 on 2025-12-03.
//

#include <iostream>
#include "Game.h"
#include "ilo.h"
#include "ENEMY.h"
#include "CONSUMABLE.h"


#define MAX_INV 8
using namespace std;

void Game::initializeWorld(Player* p) {
    player = p;
    vector<unique_ptr<ITEM>> all_items;
    vector<unique_ptr<ENEMY>> all_enemies;
    FileIO f;
    f.readCatalog("enCatalog.csv", all_items,all_enemies);
    f.readRooms("enRooms.csv",all_enemies, rooms, all_items);

    for (auto& item: all_items) {
        items.insert({item->getId(), move(item)});
    }

    currentRoom = rooms.at("R1");
    rooms.at("R5")->setLock(true);
    rooms.at("R5")->setKey("INGRID BERGMAN-KEY");

    rooms.at("R6")->setLock(true);
    rooms.at("R6")->setKey("AUDREY HEPBURN-KEY");

    rooms.at("R4")->setLock(true);
    rooms.at("R4")->setKey("ANNE HATHAWAY-KEY");
}
string lifeline(int l) {
    int i = (l < 0)? 0:l;
    string life = " | ";
    for (int k = 0; k<i; k++) life += "#";
    return life;
}
void Game::youPlaying(bool keep_playing, int& num_turns, bool& turn) {
    while (keep_playing){
        menu();
        char choice;
        cout << "Make a choice: ";
        cin >> choice;
        cout << "------------------------------------\n";

        switch (choice) {
            case '0': {
                player->stats();
                break;
            }
            case '1': {
                //look();
                currentRoom->describe();
                break;
            }
            case '2': {
                    pickUp();
                break;
            }
            case '3': {
                    inventory();
                break;
            }
            case '4': {
                auto& present = currentRoom->getEnemies();
                if (!present.empty()) {
                    for (int i = 0; i < present.size(); i++) {
                        auto& en = present[i];

                        //Apply poison on 3 turns
                        if (num_turns<3) {
                            player->damageTaken(5);
                            cout <<"\n << Poison trap active (-5hp) >>\n";
                        }

                        int php = player->getHp();
                        int ehp = en->getEnHP();

                        while (php > 0 && ehp > 0) {
                            if (turn){
                                player->playerAttack(*en);
                                ehp = en->getEnHP();
                                turn = false;
                                if (ehp <= 0) {
                                    cout << "\n-----------------------\n";
                                    cout << "You beat the enemy."<< endl;
                                    cout << "Turns taken: "<< num_turns << endl;
                                    cout <<"Player HP left "<< php << lifeline(php) << endl;
                                    cout << "-----------------------\n";
                                    en->dropLoot(*player);
                                    break;
                                }
                            }
                            else{
                                if (en->isBoss()) {
                                    en->setTurn(1);
                                    float angry = 0.6 * en->getMaxHp();
                                    float current = en->getEnHP();
                                    if (current > angry) {
                                        if (en->getTurn() >= 3 && en->getTurn() % 3 == 0) {
                                            en->specialAttack(*player);
                                        }
                                        else en->takeTurn(*player);
                                    }
                                    else if (current <= angry && en->getEnHP() > 0) {
                                        cout << "\nThe Boss becomes angry" << endl;
                                        en->phase2(*player);
                                    }
                                    else {
                                        cout << "\n========= Boss fight results ===========" << endl;
                                        cout << "You Defeated Vecna."<< endl;
                                        cout << "Player HP left "<< php << lifeline(php) << endl;
                                        en->dropLoot(*player);
                                        cout << "=============================" << endl;

                                    }

                                }
                                else{
                                    if (num_turns > 0 && num_turns % 2 == 0) {
                                        en->specialAttack(*player);
                                    }
                                    else {
                                        en->takeTurn(*player);
                                    }
                                }

                                php = player->getHp();
                                turn = true;
                                num_turns += 1;

                                cout << "\n............................." << endl;
                                cout << "Turn: "<< num_turns;
                                cout <<" | HP "<< (php < 0? 0:php) << lifeline(php) << endl;
                                cout << "............................." << endl;

                                if (php <= 0) {
                                    cout << "\n========= Summary ===========" << endl;
                                    cout << "You DIED. Game Over."<< endl;
                                    cout << "Turns taken: "<< num_turns << endl;
                                    cout <<"Your HP "<< (php < 0? 0:php) <<  lifeline(php) << endl;
                                    cout << "=============================" << endl;
                                    keep_playing = false;
                                }
                                break;
                            }

                        }

                        if (ehp <= 0) {
                            present.erase(present.begin()+i);
                            --i;
                        }
                    }
                }
                break;
            }
            case '5': {
                string id;
                while (id.empty()) {
                    cout << "Enter an ID: ";
                    cin >> id;
                }
                cout << "-------------------\n";
                equip(id);
                break;
            }
            case '6': {
                string id;
                cout << "Enter an ID: ";
                cin >> id;
                cout << "-------------------\n";
                use(id);
                break;
            }
            case '7': {
                string dir;
                cout << "Enter an direction to exit: ";
                cin >> dir;
                cout << "\n-------------------\n";
                go(dir);
                break;
            }
            case '8': {
                help();
                break;
            }
            case '9': {
                char why;
                cout << "Are you sure you want to quit game? (Y or N): " << endl;
                cin >> why;
                if (why == 'Y' || why == 'y') exit(&keep_playing);
                else cout << "Chose to continue playing" << endl;
                break;
            }
            default: cout << "\nEnter a valid choice.\n";
        }
        if (currentRoom == rooms.at("R6") && currentRoom->getEnemies().empty()) {
            cout << "\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"<<endl;
            cout << "\tSplendid gameplay. You WIN!!!."<< endl;
            cout << "You escaped Vecna's grasp through Dustin's gate."<< endl;
            cout << " Game summary:"<<endl;
            cout << "  - Total Brave attacks: "<< num_turns << endl;
            cout << "  - Your final HP: "<< player->getHp() << endl;
            cout <<"*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"<<endl;
            cout <<">>> Welcome again to play Dungeons Not Dragons <<<"<<endl;
            keep_playing = false;
        }
    }
}
void Game::addItem(unique_ptr<ITEM> item) { //adds item to game, not player
    items.insert({item->getId(),move(item)});
}
void Game::look() {
    currentRoom->describe();
}
void Game::pickUp() {
    auto& temp = currentRoom->getItems();
    for (auto it = temp.begin(); it != temp.end(); ++it) {
        if (player->getFull() < MAX_INV){
            player->addItem(move(*it));
            temp.erase(it);
            --it;
        }
        else {
            cout << "INVSIZE: " << player->getFull()<< endl;
            cout << "\n!!!!! Inventory full. !!!!!!" <<endl;
            break;
        }
    }
    cout << "\nCollectibles added to inventory." << endl;
}
void Game::go(string dir) {
    auto available = currentRoom->getExits();
    auto iter_in_available = available.find(dir);

    if (iter_in_available != available.end()){
        auto it_in_game_rooms = rooms.find(iter_in_available->second);
        auto room = it_in_game_rooms->second;

        if (room->isLocked()) {
            if (player->findKey(room->getKey())) {
                room->setLock(false);
            }
            else
                cout << "\nTo enter, you need: " << room->getKey() <<endl;
        }
        if (!room->isLocked()){
            currentRoom = room;
            cout << "\n >>>>> You are now in the: " << currentRoom->getName() <<endl;
        }
    }
    else cout << "\nNot an exit from this room.\n";
}
void Game::inventory() {
    player->showItems();
}
void Game::equip(string id) {
    player->equip(id);
}
void Game::use(string id) {
    player->heal(id);
}
void Game::help() {
    cout <<endl;
    cout << "Instruction Set"<<endl;
    cout << "  0 - View your status (HP, weapon, stats)" << endl;
    cout << "  1 - Look around the current room (enemies, items, exits)" << endl;
    cout << "  2 - Pick up items in the room" << endl;
    cout << "  3 - Show your inventory" << endl;
    cout << "  4 - Attack enemies in the room" << endl;
    cout << "  5 - Equip a weapon using its ID" << endl;
    cout << "  6 - Use a consumable using its ID" << endl;
    cout << "  7 - Move to another room (enter n, e, s, or w)" << endl;
    cout << "  8 - Help (How to play)" << endl;
    cout << "  9 - Exit the game" << endl;
    cout << "------------------------------------\n";
}
void Game::exit(bool* keep_playing) {
    cout << "\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"<<endl;
    cout << "Thank you for playing Dungeons Not Dragons." << endl;
    cout << "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n"<<endl;
    *keep_playing = false;
}
void Game::menu() {
    cout <<endl;
    cout << "    \t===== MENU =====" << endl;
    cout << "  0. My status." << endl;
    cout << "  1. Look around room." << endl;
    cout << "  2. Pick up items." << endl;
    cout << "  3. Show my inventory." << endl;
    cout << "  4. Attack." << endl;
    cout << "  5. Equip a weapon." << endl;
    cout << "  6. Use a consumable." << endl;
    cout << "  7. Go to another room." << endl;
    cout << "  8. Help." << endl;
    cout << "  9. Exit   " << endl;
    cout << "------------------------------------\n";
    cout << "" << endl;
}

