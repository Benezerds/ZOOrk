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
    // For now, let's just print a message when an NPC talks to the player
    std::cout << "NPC " << this->getName() << " says: 'Hello, player!'" << std::endl;
}

void Character::attackTo(Player* player) {
    // Let's make the NPC attack the player by reducing the player's health
    int playerHealth = player->getHealth();
    int npcAttack = this->getAttack();

    // Calculate the new health after the attack
    int newHealth = playerHealth - npcAttack;

    // Make sure health doesn't go below 0
    if (newHealth < 0) {
        newHealth = 0;
    }

    // Set the player's new health
    player->setHealth(newHealth);

    std::cout << "NPC " << this->getName() << " attacks player, causing " << npcAttack << " damage!" << std::endl;
}
