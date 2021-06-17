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
    renderizador().fill_circle(cen::point(pos_x, pos_y), 75);

    renderizador().present();
  }

  void update() {
    pos_x = pos_x + direccion_x;
    pos_y = pos_y + direccion_y;

    if (pos_x > 800 || pos_x < -1) {
      direccion_x = direccion_x * -1;
    };

    if (pos_y < -1 || pos_y > 600) {
      direccion_y = direccion_y * -1;
    };
  }

  void run() {
    ventana().show();

    while (m_running) {
      m_dispatcher.poll();
      draw();
      update();
    }

    ventana().hide();
  }

private:
  std::pair<cen::window, cen::renderer> motor = cen::make_window_and_renderer();
  cen::window &ventana() { return get<0>(motor); }
  cen::renderer &renderizador() { return get<1>(motor); }

  double pos_x = 0;
  double pos_y = 100;
  double direccion_x = 5;
  double direccion_y = 5;

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