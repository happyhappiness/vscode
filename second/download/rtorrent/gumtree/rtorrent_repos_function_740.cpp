void
InputEvent::event_read() {
  int c;

  while ((c = getch()) != ERR)
    m_slotPressed(c);
}