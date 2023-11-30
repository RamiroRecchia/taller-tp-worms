#include "grave.h"

using namespace SDL2pp;

Grave::Grave(bool& facing_right, float& worm_angle){
    this->texture_name = "Grave";
    this->frames = 16;
    this->shot_angle = 0.0;
    this->facing_right = facing_right;
    this->worm_angle = worm_angle;
    this->finished = true;
}

void Grave::present(int& it_inc,
                    SDL2pp::Renderer& renderer,
                    TextureManager& texture_manager,
                    float& pos_x,
                    float& pos_y,
                    float& x_scale,
                    float& y_scale,
                    int& vida,
					uint32_t& equipo) {
    
	iteration += it_inc;

	int src_x = 0;
	int src_y = 60 * (iteration % frames);

    //Voltear el sprite dependiendo para que lado mire
    int flip = facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    //Obtengo la textura
	Texture& texture = texture_manager.get_texture(texture_name);

	//Grafico
    texture.SetAlphaMod(255); // El sprite es totalmente opaco
    // printf("la posicion del gusano es %f %f\n",pos_x,pos_y);

	renderer.Copy(
				texture,
				Rect(src_x, src_y, 60, 60), // El sprite
				Rect(static_cast<int>((pos_x - WORM_WIDTH / 2) * x_scale),
					static_cast<int>((pos_y - WORM_HEIGHT / 2) * y_scale),
					WORM_WIDTH * x_scale, WORM_HEIGHT * y_scale), // Donde lo grafico
				worm_angle,        // Angulo
				NullOpt,
				flip        // Flip
			);

}
