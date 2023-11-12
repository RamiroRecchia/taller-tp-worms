#include "threadEnviador.h"


Enviador::Enviador(Socket &peer, Queue<Mensaje> *snapshots):skt(peer),snapshots_a_enviar(snapshots){

}


void Enviador::run(){
    bool was_closed = false;
    ServerProtocolo ptcl(skt);
    while(!was_closed){
        Mensaje msg = snapshots_a_enviar->pop();
        if(msg.tipo_comando == COMANDO::CMD_ENVIAR_SNAPSHOT){
            Snapshot snap = msg.snap;
            ptcl.enviar_snapshot(snap);
        }
        if(msg.tipo_comando == COMANDO::CMD_LISTAR_PARTIDAS){
            printf("En el enviador se estan por mandar partidas\n");
            ptcl.enviar_partidas(msg.lista_mapas);
        }
        if(msg.tipo_mensaje() == COMANDO::CMD_EMPEZAR_PARTIDA){
            printf("Se envia mensaje de que la partida empezo\n");
            ptcl.check_partida_empezada();
        }

        if(msg.tipo_mensaje() == COMANDO::CMD_HANDSHAKE){
            printf("Se envia un handshake\n");
            ptcl.enviar_handshake(msg.gusanos_por_player);
        }
        
    }
}
