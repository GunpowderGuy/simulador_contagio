#pragma once

#include <functional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

#include "propiedad.hpp"

#include <iostream>

using namespace std;

using Arista = pair<Propiedad, int>;

class Grafo { // grafo dirigido
  unordered_set<Propiedad> vertices;
  unordered_multimap<Propiedad, Arista> aristas;

// Vivienda -> Comercial
// Vivienda <- Comercial(key)

public:
  // encapsulamiento -> puede ser leido pero no alterado
  const unordered_set<Propiedad> &get_vertices() const { return vertices; }
  const unordered_multimap<Propiedad, Arista> &get_aristas() const {
    return aristas;
  }

  bool annadir_vertice(const Propiedad &prop) {
    // retorna falso si la insercion falla -> no permite 2 elementos con el
    // mismo hash
    return this->vertices.insert(prop).second;
  }

  void annadir_arista(const Propiedad &negocio, const Arista &vivienda) {
    this->aristas.insert(make_pair(negocio, vivienda));
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
      const int value =
          visit(overloaded{
                    [](auto arg) { return 0; },
                    [](Vivienda arg) { return arg.residentes; },
                },
                iterador->second.first.tipo) *
          (iterador->second.second); // residentes * ponderacion de arista

      result += value;
    }
    return result;
  }

  // parametro debe ser una propiedad comercial
  void back_propagate(const Propiedad &key) {
    const unsigned int clientes = this->afluencia(key);
    //cout << "clientes" << clientes << "clientes";
    const auto conx = this->conexiones(key);

    bool infeccion = clientes > get<Comercial>(key.tipo).aforo;

    for (auto iterador = conx.first; iterador != conx.second; iterador++) {
      auto arista = iterador->second;
      auto peso = arista.second;
      auto propiedad1 = arista.first;

      get<Vivienda>(propiedad1.tipo).infectados =
          get<Vivienda>(propiedad1.tipo).residentes * peso;
    }
  }
};

Grafo initGrafo() {
  Grafo grafo;

  const auto prop1 = Propiedad("DFDF", 100, 100);
  const auto prop2 = Propiedad("nanadn", 390, 250, Comercial());

  grafo.annadir_vertice(prop1);
  grafo.annadir_vertice(Propiedad("dfdfd", 700, 100));
  grafo.annadir_vertice(Propiedad("nanan", 390, 510));

  grafo.annadir_vertice(prop2);

  grafo.annadir_arista(prop2, make_pair(prop1, 50));

  grafo.back_propagate(prop2);

  //std::cout << get<Vivienda>(prop1.tipo).infectados;
  


  return grafo;
}