#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>
#include <list>
#include <vector>

class Passage;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);

    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    void addItem(Item*);
    void removeItem(const std::string&);
    Item* getItem(const std::string&);
    std::vector<Item*> getItems();

    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);

    std::shared_ptr<Passage> getPassage(const std::string &);

    void addCharacter(Character *character);

    Character* getCharacter(const std::string& characterName);

    std::list<Character*> getCharacters();

protected:
    std::vector<Item*> items;
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    std::list<Character*> characters;  // Add this member

};

#endif //ZOORK_ROOM_H
