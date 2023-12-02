#include "snapshot.h"

SnapshotCliente::SnapshotCliente(int id_camera): _id_camera(id_camera) {}


void SnapshotCliente::add_worm(std::shared_ptr<Worm> worm, int id) {
    worms.emplace(id, worm);
}

void SnapshotCliente::add_beam(Beam beam) {
    beams.push_back(beam);
}

void SnapshotCliente::add_projectile(std::unique_ptr<ProjectileClient> proyectil){
    projectiles.push_back(std::move(proyectil));
}

void SnapshotCliente::add_sound(int sound) {
    sonidos.push_back(sound);
}

void SnapshotCliente::add_explosion(ExplosionCliente explosion){
    explosiones.push_back(explosion);
}

void SnapshotCliente::set_weapon_power(int& power) {
    weapon_power = power;
}

void SnapshotCliente::set_tp(bool& _has_tp, float& pos_x, float& pos_y) {
    has_tp = _has_tp;
    tp_x = pos_x;
    tp_y = pos_y;
}

void SnapshotCliente::set_air_attack(bool& _has_air_attack, float& pos_x, float& pos_y) {
    has_air_attack = _has_air_attack;
    air_attack_x = pos_x;
    air_attack_y = pos_y;
}
void SnapshotCliente::set_timer(bool& _has_timer, int& _timer) {
    has_timer = _has_timer;
    timer = _timer;
}

void SnapshotCliente::set_ammo(int& weapon, int& _ammo) {
    ammo[weapon] = _ammo;
}

void SnapshotCliente::apply_to_world(World& world) {
    // Actualizo camara
    world.update_camera(_id_camera);
    // Actualizo el turno
    world.update_turn(id_turno_actual);
    // Actualizo gusanos
    for (const auto& pair: worms) {
        world.update_worm(pair.first, std::move(pair.second));
    }
    // Actualizo proyectiles
    for(auto &c:projectiles){
        world.add_projectile(std::move(c));
    }
    // Actualizo explosiones
    for (auto& e: explosiones) {
        world.add_explosion(e);
    }
    // Actualizo sonidos
    while (!sonidos.empty()) {
        world.add_sound(sonidos.back());
        sonidos.pop_back();
    }
    // Actualizo datos especiales
    world.set_weapon_power(weapon_power);
    world.set_tp(has_tp, tp_x, tp_y);
    world.set_air_attack(has_air_attack, air_attack_x, air_attack_y);
    world.set_timer(has_timer, timer);
    
    // Actualizo municion
    for (auto& pair: ammo) {
        world.set_ammo(pair.first, pair.second);
    }
}

bool SnapshotCliente::turn_change(World& world) {
    return id_turno_actual == world.get_turn();
}


/*
void SnapshotCliente::present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        int& window_width,
                        int& window_height,
                        float& x_scale,
                        float& y_scale){
    // Obtengo la posicion de la camara:
    float pos_foco_x = worms.at(_id_camera)->get_x();    //Por ahora solo enfoca gusanos
    float pos_foco_y = worms.at(_id_camera)->get_y();

    float camera_x = pos_foco_x - (window_width / (2 * x_scale));
    float camera_y = pos_foco_y - (window_height / (2 * y_scale));

    if (camera_x < 0) camera_x = 0;
    if (camera_y < 0) camera_y = 0;

    for (auto& worm : worms) {
        worm.second->present(it_inc, renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);
    }

    for (auto& beam : beams) {
        beam.present(renderer, texture_manager, x_scale, y_scale, camera_x, camera_y);
    }

    renderer.Present();
}
*/
void SnapshotCliente::agregar_turno_actual(uint32_t turno){
    this->id_turno_actual = turno;
}

void SnapshotCliente::imprimir_posiciones(){
    for (auto &worm : worms){
        printf("La posicion x es = %f\n",worm.second->get_x());
    }
}

std::map<int, std::shared_ptr<Worm>> SnapshotCliente::get_worms(){
    return this->worms;
}

void SnapshotCliente::actulizar_camara(uint32_t id){
    this->_id_camera = id;
}