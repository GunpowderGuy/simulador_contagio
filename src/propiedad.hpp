#include <string>
#include <variant>

struct Vivienda {
  int residentes = 0;
};

struct Comercial {
  int apertura;
  int cierre;
};

struct Propiedad {
  std::string Nombre;
  // enum class Tipo { vivienda, comercial, trabajo };
  variant<Vivienda, Comercial> tipo;

  // https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-user-defined-class-in-cpp/
  bool operator==(const Propiedad &p) const { return this->Nombre == p.Nombre; }
};

namespace std {

template <> struct hash<Propiedad> {
  size_t operator()(const Propiedad &x) const {
    return hash<string>{}(x.Nombre);
  }
};
// https://stackoverflow.com/questions/8157937/how-to-specialize-stdhashkeyoperator-for-user-defined-type-in-unordered
} // namespace std