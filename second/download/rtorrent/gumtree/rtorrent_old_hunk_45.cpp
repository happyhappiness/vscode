  m_list(l),
  m_focus(f) {
}

void
WindowPeerList::redraw() {
  m_nextDraw = utils::Timer::cache().round_seconds() + 1000000;
  m_canvas->erase();

  int x = 2;
  int y = 0;

  m_canvas->print(x, y, "DNS");   x += 16;
