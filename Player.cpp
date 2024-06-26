#include <algorithm>
#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(Item* item) {
    inventory.push_back(item);
}

void Player::removeItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            inventory.erase(it);
            break;
        }
    }
}


Item* Player::getItem(const std::string& itemName) {
    for (Item* item : inventory) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

void Player::attack(Character* character) {
    // Calculate damage based on the player's attack value
    int damage = this->getAttack();

    // Increase damage by 10 if the player has a sword
    if (hasItem("sword")) {
        damage += 10;
    }

    // Reduce the character's health by the damage amount
    int characterHealth = character->getHealth();
    character->setHealth(characterHealth - damage);
}


void Player::useItem(const std::string& itemName) {
    // Find the item in the inventory
    Item* item = getItem(itemName);

    // Check if the item exists in the inventory
    if (!item) {
        std::cout << "You don't have an item named '" << itemName << "' in your inventory!" << std::endl;
        return;
    }

    // Assuming 'currentRoom' is a pointer to the current room the player is in
    Character* enemy = currentRoom->getCharacter("lion");

    // Check if there is a lion in the room and the item used is a steak
    if (itemName == "steak" && currentRoom->hasCharacter("lion")) {
        std::cout << "You have tamed the lion with the steak!" << std::endl;
        currentRoom->removeCharacter("lion");
        enemyTamedOrRemoved = true; // Set the flag
    }

    // Use the item
    std::cout << "You used the item '" << itemName << "'." << std::endl;

    // Remove the item from the inventory after use
    removeItem(itemName);
}


bool Player::hasItem(const std::string& itemName) {
    for (Item* item : inventory) {
        if (item->getName() == itemName) {
            return true;
        }
    }
    return false;
}

int Player::getInventorySize() const {
    return inventory.size();
}

std::vector<Item*> Player::getInventory() const {
    return inventory;
}

bool Player::isEnemyTamedOrRemoved() const {
    return enemyTamedOrRemoved;
}



