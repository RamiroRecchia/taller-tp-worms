#ifndef _RECIBIDOR
#define _RECIBIDOR

#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../../common/queue.h"
#include "../protocolo/protocoloServer.h"
#include "../lobby.h"


struct Lobby;
struct Recibidor:public Thread{


    Socket &skt;
    std::atomic<bool> is_alive;
    Queue<std::shared_ptr<Comando>> &acciones_a_realizar;
    uint32_t id;
    Queue<std::shared_ptr<MensajeServer>>* snapshots;
    uint32_t id_partida;
    Lobby &lobby;
    uint8_t id_gusano;
    std::vector<uint32_t> id_gusanos;

    Recibidor(Socket &peer, Queue<std::shared_ptr<Comando>> &acciones,Queue<std::shared_ptr<MensajeServer>>* snapshots,Lobby &lobby);

    void run() override;

    bool is_dead();

    void kill_thread();

};

#endif