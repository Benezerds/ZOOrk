//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"
#include "Door.h"

#include <utility>
#include <algorithm>
#include <limits>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();

    player->setHealth(100);
    player->setAttack(5);
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (player->getHealth() <= 0) {
            std::cout << "Game Over...";
            gameOver = true;
        } else {
            if (command == "go") {
                handleGoCommand(arguments);
            } else if ((command == "look") || (command == "inspect")) {
                handleLookCommand(arguments);
            } else if ((command == "take") || (command == "get")) {
                handleTakeCommand(arguments);
            } else if (command == "drop") {
                handleDropCommand(arguments);
            } else if (command == "quit") {
                handleQuitCommand(arguments);
            } else if (command == "use") {
                handleUseCommand(arguments);
            } else if (command == "check") {
                handleCheckCommand();
            } else if (command == "fight") {
                handleFightCommand(arguments);
            } else if (command == "talk") {
                handleTalkCommand(arguments);
            } else {
                std::cout << "I don't understand that command.\n";
            }
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room *currentRoom = player->getCurrentRoom();
    std::shared_ptr<Passage> passage = currentRoom->getPassage(direction);

    // Try to cast the Passage to a Door
    std::shared_ptr<Door> doorPtr = std::dynamic_pointer_cast<Door>(passage);
    if (doorPtr && !doorPtr->tryToOpen(player)) {
        std::cout << "The door to the " << direction << " is locked.\n";
    } else if (passage) {
        Room *otherRoom = (currentRoom == passage->getFrom()) ? passage->getTo() : passage->getFrom();
        player->setCurrentRoom(otherRoom);
        std::cout << otherRoom->getDescription();
    } else {
        std::cout << "There is no passage to the " << direction << ".\n";
    }
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    // If no arguments were provided, print an error message
    if (arguments.empty()) {
        std::cout << "No arguments provided.\n";
        return;
    }

    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    // Get the player's current room
    Room *currentRoom = player->getCurrentRoom();

    // Try to get the passage in the specified direction
    std::shared_ptr<Passage> passage = currentRoom->getPassage(direction);

    // If the passage exists, print a simple message about the room it leads to
    if (passage != nullptr) {
        // Try to cast the Passage to a Door
        std::shared_ptr<Door> doorPtr = std::dynamic_pointer_cast<Door>(passage);
        if (doorPtr) {
            std::cout << "There is a door to the " << direction << ".\n";
        } else {
            // Get the room in the specified direction
            Room *nextRoom = passage->getTo();

            // If the next room exists and the passage leads from the current room to the next room, print out a simple message about the next room
            if (nextRoom != nullptr && passage->getFrom() == currentRoom && passage->getTo() == nextRoom) {
                std::cout << "You see a " << nextRoom->getName() << " on the " << direction << " side.\n";
            } else {
                std::cout << "Next room does not exist or passage does not lead from current room to next room.\n";
            }
        }
    } else {
        // If the passage does not exist, print an error message
        std::cout << "Passage does not exist.\n";
    }
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "You must specify an item to take.\n";
        return;
    }

    std::string itemName = arguments[0];
    Room *currentRoom = player->getCurrentRoom();
    Item *item = currentRoom->getItem(itemName);

    if (item == nullptr) {
        std::cout << "There is no item '" << itemName << "' here.\n";
    } else {
        player->addItem(item);
        currentRoom->removeItem(item->getName());
        std::cout << "You took the " << itemName << ".\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "You must specify an item to drop.\n";
        return;
    }

    std::string itemName = arguments[0];
    Item *item = player->getItem(itemName);

    if (item == nullptr) {
        std::cout << "You do not have an item '" << itemName << "'.\n";
    } else {
        player->removeItem(item->getName());
        Room *currentRoom = player->getCurrentRoom();
        currentRoom->addItem(item);
        std::cout << "You dropped the " << itemName << ".\n";
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}

void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "You must specify an item to use.\n";
        return;
    }

    std::string itemName = arguments[0];
    Item *item = player->getItem(itemName);

    if (item == nullptr) {
        std::cout << "You do not have an item '" << itemName << "'.\n";
    } else {
        // Get the current room and the door passage
        Room *currentRoom = player->getCurrentRoom();
        std::shared_ptr<Passage> door = currentRoom->getPassage("door");

        // Try to cast the Passage to a Door
        std::shared_ptr<Door> doorPtr = std::dynamic_pointer_cast<Door>(door);
        if (doorPtr && doorPtr->tryToOpen(player)) {
            std::cout << "You used the " << itemName << " to open the door.\n";
        } else {
            std::cout << "You can't use the " << itemName << " here.\n";
        }
    }
}

void ZOOrkEngine::handleCheckCommand() {
    Room *currentRoom = player->getCurrentRoom();
    std::vector<Item *> items = currentRoom->getItems();
    std::list<Character *> characters = currentRoom->getCharacters();  // Get the characters in the room

    if (items.empty()) {
        std::cout << "There are no items in this room.\n";
    } else {
        std::cout << "You see the following items:\n";
        for (Item *item: items) {
            std::cout << "- " << item->getName() << ": " << item->getDescription() << "\n";
        }
    }

    if (characters.empty()) {
        std::cout << "There are no characters in this room.\n";
    } else {
        std::cout << "You see the following characters:\n";
        for (Character *character: characters) {
            std::cout << "- " << character->getName() << "\n";
        }
    }
}


void ZOOrkEngine::handleFightCommand(std::vector<std::string> arguments) {
    // Check if the user specified an enemy to fight
    if (arguments.empty()) {
        std::cout << "You must specify an enemy to fight.\n";
        return;
    }

    // Get the enemy name from the arguments
    std::string enemyName = arguments[0];

    // Get the enemy character from the current room
    Character *enemy = player->getCurrentRoom()->getCharacter(enemyName); // You need to implement this function

    // Check if the enemy exists in the current room
    if (!enemy) {
        std::cout << "There's no enemy named '" << enemyName << "' here to fight!" << std::endl;
        return;
    }

    // The fight continues until either the player or the enemy dies
    bool isPlayerTurn = true; // Variable to keep track of whose turn it is
    std::string itemName; // Declare itemName here
    while (player->getHealth() > 0 && enemy->getHealth() > 0) {
        if (isPlayerTurn) {
            // Display options to the player
            std::cout << "Choose an action:\n1. Attack\n2. Use Item\n3. Run\n";
            int choice;
            std::cin >> choice;

            // Ignore the newline character
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1: // The player attacks the enemy
                    player->attack(enemy);

                    // Check if the enemy is dead
                    if (enemy->getHealth() <= 0) {
                        std::cout << "You have defeated the enemy '" << enemyName << "'!" << std::endl;
                        return;
                    }
                    break;
                case 2: // The player uses an item
                    std::cout << "Enter the name of the item you want to use: ";
                    std::getline(std::cin, itemName);
                    player->useItem(itemName);
                    break;
                case 3: // The player runs away
                    std::cout << "You ran away from the enemy '" << enemyName << "'!" << std::endl;
                    return;
                default:
                    std::cout << "Invalid choice. Please choose a valid action.\n";
                    continue;
            }
        } else {
            // The enemy attacks the player
            enemy->attackTo(player);

            // Check if the player is dead
            if (player->getHealth() <= 0) {
                std::cout << "You have been defeated by the enemy '" << enemyName << "'!" << std::endl;
                return;
            }
        }

        // Switch turns
        isPlayerTurn = !isPlayerTurn;
    }
}

void ZOOrkEngine::handleTalkCommand(std::vector<std::string> arguments) {
    // Check if the user specified a character to talk to
    if (arguments.empty()) {
        std::cout << "You must specify a character to talk to.\n";
        return;
    }

    // Get the character name from the arguments
    std::string characterName = arguments[0];

    // Get the character from the current room
    Character *character = player->getCurrentRoom()->getCharacter(characterName);

    // Check if the character exists in the current room
    if (!character) {
        std::cout << "There's no character named '" << characterName << "' here to talk to!" << std::endl;
        return;
    }

    // Have the character talk
    character->talk();
}
