#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "Item.h"
#include "Door.h"

int main() {
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                                                         "You are inside a dungeon cell, the room seems pretty empty. There is only a key and door to the east of the room.\n");

    std::shared_ptr<Room> empty_prison_hallway = std::make_shared<Room>("empty-prison-hallway",
                                                                  "The hallway seems empty. You can see the pantry to the east and assembly room to the south\n");

    std::shared_ptr<Room> pantry = std::make_shared<Room>("pantry",
                                                                "The pantry, maybe there is some left over foods around\n");

    std::shared_ptr<Room> assembly_point = std::make_shared<Room>("assembly", "What is this place? an assembly? This place kinds of creeps me out!");

    std::shared_ptr<Room> storage = std::make_shared<Room>("storage", "The storage room! There could be a weapon I can use here");

    std::shared_ptr<Room> main_hall = std::make_shared<Room>("main-hall", "This main hall is huge");

    std::shared_ptr<Room> disposal = std::make_shared<Room>("disposal", "You're inside the disposal room. A place where they dispose dead prisoners, disgusting!");

    std::shared_ptr<Room> final_room = std::make_shared<Room>("final-room", "The door behind is locked! You can't move back, is this the final room?");

    std::shared_ptr<Room> vent = std::make_shared<Room>("vent", "This is a long dark vent, what could be on the end? Maybe you should turn back...");

    std::shared_ptr<Room> inner_sanctum = std::make_shared<Room>("inner-sanctum", "You're inside the inner sanctum. The air seems heavy here, what could be here?");

    // Create an Item object
    Item* prisonKey = new Item("prison key", "A small brass key.");

    // Add the items to the start room
    start->addItem(prisonKey);

    // Create a Door object
    std::shared_ptr<Door> door = std::make_shared<Door>("door", "A locked door. You need a prison key", prisonKey);

    // Connect the door from the start room to the south_of_house room
    door->setFrom(start.get());
//    door->setTo(south_of_house.get());

    // Add the door to the start room and the south_of_house room
    start->addPassage("south", door);
//    south_of_house->addPassage("north", door);

//    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", true);

    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
