void
Canvas::resize(int x, int y, int w, int h) {
  wresize(m_window, h, w);
  mvwin(m_window, y, x);
}