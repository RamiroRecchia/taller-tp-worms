#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include <string>
#include "comunicacion/worm.h"
#include "comunicacion/beam.h"

#define BACKGROUND_WIDTH 576
#define BACKGROUND_HEIGHT 324

#define HUD_WIDTH 320
#define HUD_HEIGHT 64

class World {
    private:
    std::map<int, std::shared_ptr<Worm>> worms;
    std::vector<Beam> beams;
    int _id_camera;
    float _map_width;
    float _map_height;

    void present_background(Renderer& Renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale,
                        float& camera_x,
                        float& camera_y);

    void present_hud(Renderer& Renderer,
                        TextureManager& texture_manager,
                        float& x_scale,
                        float& y_scale);

    public:
    World(float map_width, float map_height);

    void update_camera(int id_camera);

    void add_worm(std::shared_ptr<Worm> worm, int id);

    void update_worm(const int& id, std::shared_ptr<Worm> worm);

    void add_beam(Beam beam);

    void present(int& it_inc,
                        Renderer& renderer,
                        TextureManager& texture_manager,
                        int& window_width,
                        int& window_height,
                        float& x_scale,
                        float& y_scale);
};

#endif