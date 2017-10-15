
  // TODO: Make a buffer with size = get_width?
  char buffer[m_canvas->width() + 1];
  char* position;
  char* last = buffer + m_canvas->width();

  position = print_status_info(buffer, last);
  m_canvas->print(0, 0, "%s", buffer);

  last = last - (position - buffer);

  if (last > buffer) {
