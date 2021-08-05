#include <iostream>

#include<string>
#include <unordered_map>
#include<unordered_set>
#include<functional>

#include <ranges>

using namespace std;

struct Propiedad{
  string Nombre;
  enum class Tipo { vivienda, comercial, trabajo };

  int residentes = 0;


  int Apertura;
  int Cierre;

//https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-user-defined-class-in-cpp/
  bool operator==(const Propiedad& p) const
    {

        return this->Nombre == p.Nombre;
    }
};
//"euhkkjhkjhste es hiuhiuhouhohlkljl lkjl kj lkj lkun string largo" size_t 64 bits long int x2
namespace std {
// https://stackoverflow.com/questions/8157937/how-to-specialize-stdhashkeyoperator-for-user-defined-type-in-unordered
  template <> struct hash<Propiedad>
  {
    size_t operator()(const Propiedad & x) const
    {
      return hash<string>{}(x.Nombre);
    }
  };
}

using Arista = pair<Propiedad,int>;

class Grafo { // grafo dirigido
unordered_set<Propiedad> vertices;
unordered_multimap<Propiedad,Arista> aristas;
// mapa.insert(Dormitorios,)
public:

bool annadir_vertice(const Propiedad prop){ // retorna falso si la insercion falla
//this->vertices.insert(prop);
 return (this->vertices.insert(prop)).second;
}

void annadir_arista(const Propiedad key, const Arista conexion){
this->aristas.insert(make_pair(key,conexion));
}

//dormitorio : (utec,9) ; (tambo,8) ; (mercado,7),*

auto conexiones(const Propiedad key){ // grafo.conexiones(dormitorio);
   //return this->aristas | views::filter( [ ](auto x){return true; });

const   auto rango = this->aristas.equal_range(key);
//pair<iterator,iterator>

return rango;
}

int afluencia(const Propiedad &key){
return 5;
}



};


int main() {
    std::cout << "Hello, world!";
    return 0;
}
