void
Frame::refresh() {
  switch (m_type) {
  case TYPE_NONE:
    break;

  case TYPE_WINDOW:
    if (m_window->is_active() && !m_window->is_offscreen())
      m_window->refresh();

    break;

  case TYPE_ROW:
  case TYPE_COLUMN:
    for (Frame **itr = m_container, **last = m_container + m_containerSize; itr != last; ++itr)
      (*itr)->refresh();

    break;
  }
}