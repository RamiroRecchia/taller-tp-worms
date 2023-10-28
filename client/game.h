#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include "protocolo/protocoloCliente.h"
#include <vector>
#include "../../common/queue.h"
#include "snapshot.h"

class Game {
    private:
    Protocolo ptcl;
    Queue<Snapshot> snapshots;

    public:
    Game(Protocolo& protocol);

    int run();

};

#endif