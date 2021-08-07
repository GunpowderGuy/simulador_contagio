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

struct Propiedad {
  float x;
  float y;
  std::string nombre;
  std::variant<Vivienda, Comercial> tipo;

  bool operator==(const Propiedad &p) const { return this->nombre == p.nombre; }

    Propiedad( float x1, float y1) : x(x1), y(y1) {}
  Propiedad() = default;
};

namespace std {
template <> struct hash<Propiedad> {
  size_t operator()(const Propiedad &x) const {
    return hash<string>{}(x.nombre);
  }
};
} // namespace std