#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>

class Player;  // Forward declaration

class Character : public GameObject {
public:
    Character(const std::string &, const std::string &);

    // Getters
    int getHealth() const;
    int getAttack() const;

    // Setters
    void setHealth(int);
    void setAttack(int);

    // Inventory management
    void addItem(Item*);
    void removeItem(const std::string&);
    Item* getItem(const std::string&);

    // Interaction methods
    virtual void talkTo(Player*);
    virtual void attackTo(Player*);
    void talk();

protected:
    std::vector<Item*> inventory;
    std::vector<std::string> tags;
    int health;
    int attack;
};

#endif //ZOORK_CHARACTER_H
