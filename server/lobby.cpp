#include "lobby.h"
#include "mapContainer.h"

Lobby::Lobby():id_actual(1), lista_mapas(MapContainer()){

}

uint32_t Lobby::crear_partida(std::string nombre, Queue<Mensaje>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    Partida *partida = new Partida(id_actual,nombre);
    partida->add_queue(snapshots);
    uint32_t id_actuali = this->id_actual;
    this->id_actual++;
    lista_partidas.insert({id_actuali,partida});
    partida->start();
    printf("Se crea una partida nueva\n");
    return id_actuali;
}


void Lobby::listar_partidas(Queue<Mensaje>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    std::map<uint32_t,std::string> lista;
    for (auto i = lista_partidas.begin(); i != lista_partidas.end(); i++){
        std::string nombre = i->second->get_nombre();
        std::cout << "El nombre de la partida es : " << nombre << std::endl;
        lista.insert({i->first,nombre});
    }
    Snapshot snap(lista);
    Mensaje msg(lista, COMANDO::CMD_LISTAR_PARTIDAS);
    snapshots->push(msg);
}

void Lobby::listar_mapas(Queue<Mensaje>* cliente){
    std::lock_guard<std::mutex> lock(lck);
    // MapContainer mapContainer;
    std::map<uint32_t,std::string> lista;
    int id = 1;

    for (auto it = lista_mapas.begin(); it != lista_mapas.end(); ++it) {
        // Accede a cada par clave-valor en el mapa aquí
        std::string nombre = it->first;
        // Realiza las operaciones que desees con el mapa
        lista.insert({id, nombre});
        id++;
    }
    Mensaje msg(lista, COMANDO::CMD_LISTAR_MAPAS);
    cliente->push(msg);
}

Queue<std::shared_ptr<Comando>>& Lobby::get_queue(uint32_t id_pedido){
    std::lock_guard<std::mutex> lock(lck);
    return lista_partidas.at(id_pedido)->get_queue();
}

// void Lobby::empezar_partida(uint32_t id){
//     std::lock_guard<std::mutex> lock(lck);
//     lista_partidas.at(id)->start();
// }

void Lobby::unirse_a_partida(uint32_t id_partida, Queue<Mensaje>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    printf("Se pide unirse un player\n");
    lista_partidas.at(id_partida)->add_queue(snapshots);

}

void Lobby::desconectarse_partida(uint32_t id,Queue<Mensaje>* snapshots){
    std::lock_guard<std::mutex> lock(lck);
    if(this->lista_partidas.find(id) != this->lista_partidas.end()){
        this->lista_partidas.at(id)->remover_player(snapshots);
    }
    
}


void Lobby::kill(){
    std::lock_guard<std::mutex> lock(lck);
    auto it = lista_partidas.begin();
    while(it != lista_partidas.end()){
        printf("se le hace kill al lobby\n");
        it->second->kill();
        it->second->join();
        delete it->second;
        it = lista_partidas.erase(it);
    }
}
