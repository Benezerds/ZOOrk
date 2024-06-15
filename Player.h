#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include <vector>

class Player : public Character {
public:
    static Player *instance() {
        // Note: lazy instantiation of the singleton Player object
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);

    Room* getCurrentRoom() const;

    void addItem(Item*);
    void removeItem(const std::string&);
    Item* getItem(const std::string&);

    void attack(Character* character);  // Add this line

    Player(const Player &) = delete;

    void useItem(const std::string&);

    bool hasItem(const std::string&);

    Player &operator=(const Player &) = delete;

    int getInventorySize() const;


private:
    static Player *playerInstance;
    Room* currentRoom;
    std::vector<Item*> inventory;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}
};

#endif //ZOORK_PLAYER_H
