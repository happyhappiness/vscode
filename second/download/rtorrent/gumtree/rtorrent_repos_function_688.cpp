bool
Frame::has_left_frame() const {
  switch (m_type) {
  case TYPE_NONE:
  case TYPE_ROW:    return false;
  case TYPE_WINDOW: return m_window->is_active() && m_window->is_left();

  case TYPE_COLUMN:
    for (size_type i = 0; i < m_containerSize; ++i)
      if (m_container[i]->has_left_frame())
        return true;

    return false;
  }

  return false;
}