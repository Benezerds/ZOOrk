#ifndef ZOORK_CALCIUS_H
#define ZOORK_CALCIUS_H

#include "Character.h"
#include "INPC.h"

class Calcius : public Character, public INPC {
private:
    enum class DialogueState {
        Introduction,
        Question,
        Decision,
        GameOver
    };

    DialogueState state;
    int input;

public:
    Calcius() : Character("calcius", "The final mystical gatekeeper of the Prison Keep."),
                state(DialogueState::Introduction), input(0) {}

    void talk() override {
        int input;
        bool inConversation = true;

        while (inConversation) {
            switch (state) {
                case DialogueState::Introduction:
                    std::cout << "Calcius says: 'Well done, prisoner. You have defeated the lion, but one final challenge remains.'\n";
                    std::cout << "1. Continue\n2. Leave\n";
                    std::cin >> input;
                    if (input == 1) {
                        state = DialogueState::Question;
                    } else {
                        // Player chooses to leave, resulting in game over
                        state = DialogueState::GameOver;
                    }
                    break;
                case DialogueState::Question:
                    std::cout << "Calcius asks: 'Do you wish to be free or accept eternal guardianship of the Prison Keep?'\n";
                    std::cout << "1. Be free\n2. Accept guardianship\n";
                    std::cin >> input;
                    if (input == 1 || input == 2) {
                        state = DialogueState::Decision;
                    }
                    break;
                case DialogueState::Decision:
                    if (input == 1) {
                        std::cout << "Calcius says: 'You have chosen freedom. Go forth and live your life beyond these walls.'\n";
                        // Code to set the player free
                    } else if (input == 2) {
                        std::cout << "Calcius says: 'You have chosen guardianship. You will now take my place and watch over the Prison Keep for eternity.'\n";
                        // Code to make the player the new guardian (game over)
                    }
                    inConversation = false; // End conversation after decision
                    break;
                case DialogueState::GameOver:
                    std::cout << "Calcius says: 'So be it. Your journey ends here, traveler.'\n";
                    // Code to end the game
                    inConversation = false; // End conversation after game over
                    break;
            }
        }
    }

    void attackTo(Player *player) override {
        // Calcius doesn't attack
        std::cout << "Calcius says: 'I am here to guide, not to harm.'" << std::endl;
    }
};

#endif //ZOORK_CALCIUS_H
