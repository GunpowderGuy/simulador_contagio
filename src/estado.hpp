#include <centurion.hpp>

#include "grafo.hpp"

#include <iostream>

struct Estado {
  void draw(cen::renderer &ren) {
    ren.clear_with(cen::colors::light_coral);

    const auto &vertex = grafo.get_vertices();
    for (const Propiedad pelota : vertex) {
      const auto color = visit(
          overloaded{
              // pattern matching:
              // https://en.wikipedia.org/wiki/Pattern_matching
              [](const auto arg) { return cen::colors::green; },
              [](const Vivienda arg) { return cen::colors::blanched_almond; },
          },
          pelota.tipo); // retorna un color de acuerdo al tipo de cada vertice

      const auto &edges = grafo.get_aristas();

      ren.set_color(color); // actualiza color del renderer
      ren.fill_circle(cen::point(pelota.x, pelota.y), 75); // (coord, radius)
    }

    const auto &edges = grafo.get_aristas();

    for (const auto edge : edges) {
      const auto extremo1 = cen::point(edge.first.x, edge.first.y);
      const auto extremo2 =
          cen::point(edge.second.first.x, edge.second.first.y);

      ren.set_color(cen::colors::forest_green);
      ren.draw_line(extremo1, extremo2);
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

  // double pos_x = 0;
  // double pos_y = 100;
  // double direccion_x = 5;
  // double direccion_y = 5;
};