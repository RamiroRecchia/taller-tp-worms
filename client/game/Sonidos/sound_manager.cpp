#include "sound_manager.h"

#include <fstream>

using namespace SDL2pp;


SoundManager::SoundManager() {
    /*
    // Cargo el YAML de sonidos
    YAML::Node sounds_font = YAML::LoadFile(PROJECT_SOURCE_DIR "/client/game/Sonidos/sounds.yaml");


    for (const auto& nodo : sounds_font) {
        std::string name = nodo["nombre"].as<std::string>();
        std::string rute = PROJECT_SOURCE_DIR + nodo["ruta"].as<std::string>();

        std::unique_ptr<SDL2pp::Chunk> chunk = std::make_unique<Chunk>(rute);
        sounds.emplace(name, chunk);
    }
    */
}

std::unique_ptr<SDL2pp::Chunk> SoundManager::get_sound(std::string& sound_name) {
    return std::move(sounds.at(sound_name));
}