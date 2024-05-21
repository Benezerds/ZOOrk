// Door.cpp
#include "Door.h"
#include "Player.h"

bool Door::tryToOpen(Player* player) {
    Item* item = player->getItem(requiredItem->getName());

    if (item == nullptr) {
        std::cout << "You need a " << requiredItem->getName() << " to open this door.\n";
        return false;
    } else {
        std::cout << "You used the " << item->getName() << " to open the door.\n";
        return true;
    }
}
