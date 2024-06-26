//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"

#include <memory>
#include <utility>


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

void Room::addItem(Item* item) {
    items.push_back(item);
}

void Room::removeItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == itemName) {
            items.erase(it);
            break;
        }
    }
}


Item* Room::getItem(const std::string& itemName) {
    for (Item* item : items) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

std::vector<Item*> Room::getItems() {
    return items;
}

void Room::addCharacter(Character* character) {
    characters.push_back(character);
}

Character* Room::getCharacter(const std::string& characterName) {
    for (Character* character : characters) {  // Assuming 'characters' is a list of characters in the room
        if (character->getName() == characterName) {
            return character;
        }
    }
    return nullptr;  // Return nullptr if no character with the given name is found
}

std::list<Character*> Room::getCharacters() {
    return characters;  // Assuming 'characters' is a list of characters in the room
}

void Room::removeCharacter(const std::string& characterName) {
    for (auto it = characters.begin(); it != characters.end(); ++it) {
        if ((*it)->getName() == characterName) {
            characters.erase(it);
            std::cout << characterName << " has been removed from the room." << std::endl;
            return;
        }
    }
    std::cout << "No character named '" << characterName << "' found in the room." << std::endl;
}

bool Room::hasCharacter(const std::string& characterName) const {
    for (const auto& character : characters) {
        if (character->getName() == characterName) {
            return true;
        }
    }
    return false;
}



