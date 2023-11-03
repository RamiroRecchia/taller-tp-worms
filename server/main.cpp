//#include "poc.h"
#include "threads/threadAceptador.h"
#include "monitorBroadcaster.h"
#include "partida.h"
#include "mapContainer.h"

int main(int argc, char* argv[]) {

    const char* name = "8080";
    BroadCaster broadcaster;
    Queue<std::shared_ptr<Comando>> acciones_a_realizar;
    Aceptador skt(name,broadcaster,acciones_a_realizar);
    skt.start();
    //MapContainer mapContainer;
    Partida partida(acciones_a_realizar,broadcaster);
    partida.run();
    //Box2dPoC poc;
    //poc.run();
    skt.join();
    return 0;
}