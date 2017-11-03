void
Frame::clear() {
  switch (m_type) {
  case TYPE_WINDOW:
    if (m_window != NULL)
      m_window->set_offscreen(true);

    break;
    
  case TYPE_ROW:
  case TYPE_COLUMN:
    for (size_type i = 0; i < m_containerSize; ++i) {
      m_container[i]->clear();
      delete m_container[i];
    }
    break;

  default:
    break;
  }

  m_type = TYPE_NONE;
}