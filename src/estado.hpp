#include <centurion.hpp>

#include "grafo.hpp"

#include <iostream>

struct Estado {
  void draw(cen::renderer &ren) {
    ren.clear_with(cen::colors::light_coral);

    const auto &vertex = grafo.get_vertices();

    for (const Propiedad pelota : vertex) {
      ren.set_color(cen::colors::red);
      ren.fill_circle(cen::point(pelota.x, pelota.y), 75);
    }

    ren.present();
  }

  void update() {
    /*
    pos_x = pos_x + direccion_x;
    pos_y = pos_y + direccion_y;

    if (pos_x > 800 || pos_x < -1) {
      direccion_x = direccion_x * -1;
    };

    if (pos_y < -1 || pos_y > 600) {
      direccion_y = direccion_y * -1;
    };
    */
  }

private:
  Grafo grafo = initGrafo();

  //  double pos_x = 0;
  // double pos_y = 100;
  // double direccion_x = 5;
  // double direccion_y = 5;
};