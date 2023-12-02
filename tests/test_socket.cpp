#include "test_socket.h"

Socket::Socket(){

}


int Socket::recvall(void *data, unsigned int sz, bool *was_closed){
    unsigned int contador = 0;
    for (auto it = vector.begin(); it != vector.end();) {
        if (contador == sz) {
            break;
        }

        // Use a char variable to hold the byte
        char byte = *it;

        // Copy the byte to the destination
        memcpy(static_cast<char*>(data) + contador, &byte, 1);

        // Erase the byte from the buffer
        it = vector.erase(it);
        
        contador++;
    }
    return 1;
}


int Socket::sendall(const void *data, unsigned int sz, bool *was_closed){
    for (unsigned int i = 0; i < sz; i++){
        char buf;
        memcpy(&buf,static_cast<const char*>(data) + i,1);
        vector.push_back(buf);
    }
    return 1;   
}
