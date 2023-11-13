#include "mensaje.h"


Mensaje::Mensaje(std::shared_ptr<Snapshot> snap_):snap(snap_),tipo_comando(COMANDO::CMD_ENVIAR_SNAPSHOT){

}

Mensaje::Mensaje(uint8_t tipo):tipo_comando(tipo){

}

Mensaje::Mensaje(std::shared_ptr<Comando> cmd_):tipo_comando(COMANDO::CMD_ACCION_JUGADOR),cmd(cmd_){

}


Mensaje::Mensaje(std::map<uint32_t,std::string> mapa_):tipo_comando(COMANDO::CMD_LISTAR_PARTIDAS),lista_partidas(mapa_){

}

Mensaje::Mensaje(uint32_t id_player_, std::vector<uint32_t> id_gusanos_):tipo_comando(COMANDO::CMD_HANDSHAKE),id_player(id_player_),id_gusanos(id_gusanos_){

}