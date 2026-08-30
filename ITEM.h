//
// Created by JOSS0001 on 2025-12-03.
//

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using namespace std;
class Player;

class ITEM {
protected:
    string type;
    string name;
    string id;
public:
    ITEM(string type, string name, string id);
    virtual ~ITEM() = default;

    virtual void itemInfo() const;
    string getName() const ;
    string getId() const ;
    string getType() const ;
    virtual int getValue();

    virtual void use(Player& player) = 0;
};

class KEY: public ITEM{
public:
    KEY(string type, string name, string id);
    void use(Player &player) override;
};

#endif //ITEM_H
