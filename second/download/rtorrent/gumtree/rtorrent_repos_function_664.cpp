void
Canvas::cleanup() {
  if (!m_isInitialized)
    return;
  
  m_isInitialized = false;

  noraw();
  endwin();
}