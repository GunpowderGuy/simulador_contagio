#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "propiedad.hpp"

using namespace std;

using Arista = pair<Propiedad, int>;

class Grafo { // grafo dirigido
  unordered_set<Propiedad> vertices;
  unordered_multimap<Propiedad, Arista> aristas;

public:
  bool annadir_vertice(const Propiedad &prop) {
    // retorna falso si la insercion falla
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
      const int value =
          iterador->second.first.residentes * (iterador->second.second);
      result += value;
    }
    return result;
  }
};
