void
Canvas::initialize() {
  if (m_isInitialized)
    return;
  
  m_isInitialized = true;

  initscr();
  raw();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
}