bool
Frame::has_bottom_frame() const {
  switch (m_type) {
  case TYPE_NONE:
  case TYPE_COLUMN: return false;
  case TYPE_WINDOW: return m_window->is_active() && m_window->is_bottom();

  case TYPE_ROW:
    for (size_type i = 0; i < m_containerSize; ++i)
      if (m_container[i]->has_bottom_frame())
        return true;

    return false;
  }

  return false;
}