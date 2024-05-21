#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "Item.h"
#include "Door.h"

int main() {
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                                                         "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                                                                  "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                                                                "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    // Create an Item object
    Item* apple = new Item("apple", "A juicy red apple.");
    Item* key = new Item("key", "A small brass key.");

    // Add the items to the start room
    start->addItem(apple);
    start->addItem(key);

    // Create a Door object
    std::shared_ptr<Door> door = std::make_shared<Door>("door", "A locked door.", key);

    // Connect the door from the start room to the south_of_house room
    door->setFrom(start.get());
    door->setTo(south_of_house.get());

    // Add the door to the start room and the south_of_house room
    start->addPassage("south", door);
    south_of_house->addPassage("north", door);

    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", true);

    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
