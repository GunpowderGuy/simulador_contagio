#include <centurion.hpp>

using event_dispatcher =
    cen::event_dispatcher<cen::quit_event, cen::window_event,
                          cen::keyboard_event, cen::mouse_button_event>;

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
  }

  void draw() {
    renderizador().clear_with(cen::colors::light_coral);

    renderizador().set_color(cen::colors::red);
    renderizador().fill_circle(cen::point(150.0, 150.0), 75);

    renderizador().present();
  }

  void run() {
    ventana().show();

    while (m_running) {
      m_dispatcher.poll();
      draw();
    }

    ventana().hide();
  }

private:
  std::pair<cen::window, cen::renderer> motor = cen::make_window_and_renderer();
  cen::window &ventana() { return get<0>(motor); }
  cen::renderer &renderizador() { return get<1>(motor); }

  event_dispatcher m_dispatcher;

  bool m_running{true};
  void quit(const cen::quit_event &event) { m_running = false; }
};

int main(int, char **) {
  cen::library centurion;
  // SDL2, SDL2_image, SDL2_mixer and SDL2_ttf are now initialized!

  game juego;

  juego.run();

  return 0;
}