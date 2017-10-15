  m_list(l),
  m_focus(f) {
}

void
WindowPeerList::redraw() {
  if (Timer::cache() - m_lastDraw < 1000000)
    return;

  m_lastDraw = Timer::cache();
  m_canvas->erase();

  int x = 2;
  int y = 0;

  m_canvas->print(x, y, "DNS");   x += 16;
