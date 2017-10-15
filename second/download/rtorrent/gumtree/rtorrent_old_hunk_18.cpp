#include "config.h"

#include <stdexcept>

#include "canvas.h"
#include "window_peer_list.h"

namespace display {

WindowPeerList::WindowPeerList(PList* l, PList::iterator* f) :
  Window(new Canvas, true),
  m_list(l),
  m_focus(f) {
}

void
WindowPeerList::redraw() {
  if (utils::Timer::cache() - m_lastDraw < 1000000)
    return;

  m_lastDraw = utils::Timer::cache();
  m_canvas->erase();

  int x = 2;
  int y = 0;

  m_canvas->print(x, y, "DNS");   x += 16;
