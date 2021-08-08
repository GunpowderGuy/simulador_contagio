#include <string>
#include <variant> // TIPO que puede contener 2 TIPOS

// Metaprogramacion y Programacion generica
template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

struct Vivienda {
  int residentes = 0;
};

struct Comercial {
  int apertura;
  int cierre;

  int aforo;
};

using Tipo =
    std::variant<Vivienda,
                 Comercial>; // https://en.wikipedia.org/wiki/Tagged_union

struct Propiedad {
  float x;
  float y;
  std::string nombre;
  Tipo tipo;

  bool operator==(const Propiedad &p) const { return this->nombre == p.nombre; }

  Propiedad(std::string mi_nombre, float x1, float y1, Tipo pipo = Vivienda())
      : nombre(mi_nombre), x(x1), y(y1), tipo(pipo) {}
  Propiedad() = default;
};

// Sobrecarga
namespace std {
template <> struct hash<Propiedad> {
  size_t operator()(const Propiedad &x) const {
    return hash<string>{}(x.nombre);
  }
};
} // namespace std