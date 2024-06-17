#ifndef ZOORK_INPC_H
#define ZOORK_INPC_H

#include "Player.h"

class INPC {
public:
    virtual ~INPC() = default; // Virtual destructor for proper cleanup

    // Interaction methods
    virtual void attackTo(Player* player) = 0; // Pure virtual function
};

#endif //ZOORK_INPC_H
