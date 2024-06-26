#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "Item.h"
#include "Door.h"
#include "Calcius.h"

int main() {
    //  Map List
    //  Start room
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                                                         "You are inside a dungeon cell, the room seems pretty empty. There is only a key and a locked prison door.\n");
    Item* prisonKey = new Item("prison-key", "A small brass key.");
    start->addItem(prisonKey);

    //  Prison Hallway
    std::shared_ptr<Room> empty_prison_hallway = std::make_shared<Room>("empty-hallway",
                                                                        "Great you're out, on the EAST of the hallway, there is a path through a pantry and assembly point room on the SOUTH.\n");

    //  Pantry
    std::shared_ptr<Room> pantry = std::make_shared<Room>("pantry",
                                                                "The pantry, maybe there is some left over foods around\n");
    Item* torch = new Item("torch", "A torch to light up the dark");
    Item* assembly_key = new Item("assembly-key", "A key to the assembly room.");

    pantry->addItem(torch);
    pantry->addItem(assembly_key);


    //  Vent
    std::shared_ptr<Room> vent = std::make_shared<Room>("vent", "This is a long dark vent, what could be on the end? Maybe you should turn back....\n");


    //  Assembly point
    std::shared_ptr<Room> assembly_point = std::make_shared<Room>("assembly", "What is this place? an assembly? This place kinds of creeps me out!\n");


    //  Storage
    std::shared_ptr<Room> storage = std::make_shared<Room>("storage", "The storage room! There could be a weapon I can use here\n");

    Item* steak = new Item("steak", "A delicious steak");
    Item* sword = new Item("sword", "You can definitely use this to defend myself");

    storage->addItem(steak);
    storage->addItem(sword);

    //  Main Hall
    std::shared_ptr<Room> main_hall = std::make_shared<Room>("main-hall", "This main hall is huge.\n");

    Item* main_hall_key = new Item("mysterious-key", "No one knows which starterDoor does this opens.\n");
    main_hall->addItem(main_hall_key);


    //  Disposal
    std::shared_ptr<Room> disposal = std::make_shared<Room>("disposal", "You're inside the disposal room. A place where they dispose dead prisoners, disgusting!\n");



    //  Final Room
    std::shared_ptr<Room> final_room = std::make_shared<Room>("final-room", "The door behind  that leads to the main hall is locked! You can't move back, is this the final room?\n");

    Item* gem = new Item("gem", "Shiny gem, maybe you can put it somewhere");
    final_room->addItem(gem);

    //  Inner Sanctum
    std::shared_ptr<Room> inner_sanctum = std::make_shared<Room>("inner-sanctum", "You're inside the inner sanctum. The air seems heavy here, what could be here?\n");


    //  Arena of fate
    std::shared_ptr<Room> arena_of_fate_room = std::make_shared<Room>("arena-of-fate", "This place... There is a lion.. You need to fight it!\n");

    //  Chamber of revelation
    std::shared_ptr<Room> chamber_of_revelation = std::make_shared<Room>("chamber-of-relevation", "You made it through... But who is it standing in the middle of the room?\n");


    // Create a Door object
    std::shared_ptr<Door> starterDoor = std::make_shared<Door>("starterDoor", "A locked starterDoor. You need a prison key", prisonKey);

    // Connect the starterDoor from the start room to the south_of_house room
    starterDoor->setFrom(start.get());
    starterDoor->setTo(empty_prison_hallway.get());

    // Add the starterDoor to the start room and the south_of_house room
    start->addPassage("east", starterDoor);
    empty_prison_hallway->addPassage("west", starterDoor);


    //  Assembly Door
    std::shared_ptr<Door> assemblyDoor = std::make_shared<Door>("assemblyDoor", "The door to the assembly is locked. Find the key", assembly_key);

    assemblyDoor->setFrom(empty_prison_hallway.get());
    assemblyDoor->setTo(assembly_point.get());

    empty_prison_hallway->addPassage("south", assemblyDoor);
    assembly_point->addPassage("north", assemblyDoor);


    //  Basic Passage
    Passage::createBasicPassage(empty_prison_hallway.get(), pantry.get(), "east", true);

    //  Pantry -> Vent
    Passage::createBasicPassage(pantry.get(), vent.get(), "east", true);

    //  Vent -> Main hall
    Passage::createBasicPassage(vent.get(), main_hall.get(), "south", true);

    //  Assembly -> Storage & Assembly -> Main Hall
    Passage::createBasicPassage(assembly_point.get(), storage.get(), "east", true);
    Passage::createBasicPassage(assembly_point.get(), main_hall.get(), "south", true);


    //  Disposal Room door
    std::shared_ptr<Door> disposalDoor = std::make_shared<Door>("disposalDoor", "The door to the disposal room is locked. Find the key", assembly_key);

    disposalDoor->setFrom(main_hall.get());
    disposalDoor->setTo(disposal.get());

    main_hall->addPassage("west", disposalDoor);
    disposal->addPassage("east", disposalDoor);


    //  Finale Room door, needs a button to be opened
    std::shared_ptr<Door> finaleDoor = std::make_shared<Door>("finaleDoor", "The door to the finale room is locked. Find a way to get in", assembly_key);

    //  Passage from Finale room -> Inner Sanctum -> Arena of Fate & Arena of Fate -> Chamber of Revelation
    Passage::createBasicPassage(main_hall.get(), final_room.get(), "east", true);
    Passage::createBasicPassage(final_room.get(), inner_sanctum.get(), "north", true);
    Passage::createBasicPassage(inner_sanctum.get(), arena_of_fate_room.get(), "east", true);
    Passage::createBasicPassage(arena_of_fate_room.get(), chamber_of_revelation.get(), "south", true);

    //  Character
    Character* lion = new Character("lion", "A lion inside a prison, odd, but the king of the jungle become the king of the cell.");
    Character* calcius = new Calcius();


    lion->setHealth(100);
    lion->setAttack(10);

    calcius->setHealth(50);
    calcius->setAttack(2);

    chamber_of_revelation->addCharacter(calcius);
    arena_of_fate_room->addCharacter(lion);

    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
