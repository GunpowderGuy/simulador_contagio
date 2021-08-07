#include <string>
#include <variant>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

struct Vivienda {
  int residentes = 0;
};

struct Comercial {
  int apertura;
  int cierre;
};

using Tipo = std::variant<Vivienda, Comercial>;

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

namespace std {
template <> struct hash<Propiedad> {
  size_t operator()(const Propiedad &x) const {
    return hash<string>{}(x.nombre);
  }
};
} // namespace std