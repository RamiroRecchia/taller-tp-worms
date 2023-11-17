#include "beam.h"

using namespace SDL2pp;

Beam::Beam(int& tamano, float& pos_x, float& pos_y): _tamano(tamano), _pos_x(pos_x), _pos_y(pos_y) {}

void Beam::present(Renderer& renderer,
                    TextureManager& texture_manager,
                    float& x_scale,
                    float& y_scale,
                    float& camera_x,
                    float& camera_y) {

    // Obtengo la textura
    std::string texture_name("Beam");
	Texture& texture = texture_manager.get_texture(texture_name);

    int largo_sprite = _tamano == 6 ? 138 : 69;

    float pos_rel_x = _pos_x - camera_x;
    float pos_rel_y = _pos_y - camera_y;

    // Grafico la viga
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    renderer.Copy(
				texture,
				Rect(0, 0, largo_sprite, 20), // El sprite
				Rect(static_cast<int>(pos_rel_x * x_scale - largo_sprite / 2),
					renderer.GetOutputHeight() - static_cast<int>(pos_rel_y * y_scale - BEAM_WIDTH / 2),
					_tamano * x_scale, BEAM_WIDTH * y_scale), // Donde lo grafico
				0.0,        // Angulo
				NullOpt,
				SDL_FLIP_NONE        // Flip
			);
}