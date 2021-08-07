#pragma once

#include <functional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

#include "propiedad.hpp"

using namespace std;

using Arista = pair<Propiedad, int>;

class Grafo { // grafo dirigido
  unordered_set<Propiedad> vertices;
  unordered_multimap<Propiedad, Arista> aristas;

public:
  // encapsulamiento -> puede ser leido pero no alterado
  const unordered_set<Propiedad> &get_vertices() const { return vertices; }


  bool annadir_vertice(const Propiedad &prop) {
    // retorna falso si la insercion falla -> no permite 2 elementos con el mismo hash
    return this->vertices.insert(prop).second;
  }

  void annadir_arista(const Propiedad &key, const Arista &conexion) {
    this->aristas.insert(make_pair(key, conexion));
  }

  // dormitorio : (utec,9) ; (tambo,8) ; (mercado,7),*

  auto conexiones(const Propiedad key) {
    const auto rango = this->aristas.equal_range(key);
    // pair<iterator,iterator>
    return rango;
  }

  int afluencia(const Propiedad &key) {
    int result;
    const auto conx = conexiones(key);

    for (auto iterador = conx.first; iterador != conx.second; iterador++) {
      const int value = visit(overloaded{                   
                                  [](auto arg) { return 0; },
                                  [](Vivienda arg) { return arg.residentes; },
                              },
                              iterador->second.first.tipo) *
                        (iterador->second.second);        // residentes * ponderacion de arista

      result += value;
    }
    return result;
  }
};

Grafo initGrafo() {
  Grafo grafo;

  grafo.annadir_vertice(Propiedad("DFDF", 400, 400));
  grafo.annadir_vertice(Propiedad("dfdfd", 900, 400));
  grafo.annadir_vertice(Propiedad("nanan",100,100,Comercial()));

  return grafo;
}