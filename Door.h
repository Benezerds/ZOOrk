// Door.h
#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"
#include "Item.h"
#include "Player.h"

class Door : public Passage {
public:
    Door(const std::string& name, const std::string& description, Item* requiredItem)
            : Passage(name, description), requiredItem(requiredItem) {}

    bool tryToOpen(Player* player);

private:
    Item* requiredItem;
};

#endif //ZOORK_DOOR_H
