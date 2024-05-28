#include "Character.h"
#include "Player.h"

Character::Character(const std::string &n, const std::string &d) : GameObject(n, d) {}

int Character::getHealth() const {
    return health;
}

int Character::getAttack() const {
    return attack;
}

void Character::setHealth(int h) {
    health = h;
}

void Character::setAttack(int a) {
    attack = a;
}

void Character::addItem(Item* item) {
    inventory.push_back(item);
}

void Character::removeItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            inventory.erase(it);
            break;
        }
    }
}

Item* Character::getItem(const std::string& itemName) {
    for (Item* item : inventory) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

void Character::talkTo(Player* player) {
    // Implement this method based on how you want NPCs to interact with the player
}

void Character::attackTo(Player* player) {
    // Implement this method based on how you want NPCs to attack the player
}
