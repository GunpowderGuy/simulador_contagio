#include <centurion.hpp>

#include "estado.hpp"
#include "grafo.hpp"

using event_dispatcher =
    cen::event_dispatcher<cen::quit_event, cen::window_event,
                          cen::keyboard_event, cen::mouse_button_event>;
// observer -> recibe un evento mensaje el cual devuelve un comportamiento
// asignado

inline void mouse_button(const cen::mouse_button_event &event) {
  cen::log::info("mouse_button_event");
}

inline void window(const cen::window_event &event) {
  cen::log::info("window_event");
}

inline void keyboard(const cen::keyboard_event &event) {
  cen::log::info("keyboard_event");
}

class game final {
public:
  game() {
    m_dispatcher.bind<cen::quit_event>().to<&game::quit>(this);
    m_dispatcher.bind<cen::window_event>().to<&window>();
    m_dispatcher.bind<cen::mouse_button_event>().to<&mouse_button>();
    m_dispatcher.bind<cen::keyboard_event>().to<&keyboard>();
    // bind -> asigna una función para cada evento
  }

  void run() {
    ventana().show();

    while (m_running) {
      m_dispatcher.poll(); // recibe eventos y los pasa al dispatcher (*)
      estado.draw(
          renderizador()); // recibe un renderer y ejecuta comandos de dibujado
      estado.update();     // actualiza el estado del programa
    }

    ventana().hide();
  }

private:
  // ATRIBUTOS DE CLASE
  std::pair<cen::window, cen::renderer> motor = cen::make_window_and_renderer();
  cen::window &ventana() { return get<0>(motor); }
  cen::renderer &renderizador() { return get<1>(motor); }

  event_dispatcher m_dispatcher;

  Estado estado;

  bool m_running{true};

  // METODOS DE CLASE
  void quit(const cen::quit_event &event) { m_running = false; }
};

int main(int, char **) {
  cen::library centurion;
  // SDL2, SDL2_image, SDL2_mixer and SDL2_ttf are now initialized!

  game juego;

  juego.run();

  return 0;
}