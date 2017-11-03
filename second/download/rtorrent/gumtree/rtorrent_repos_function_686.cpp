bool
Frame::is_width_dynamic() const {
  switch (m_type) {
  case TYPE_NONE:   return false;
  case TYPE_WINDOW: return m_window->is_active() && m_window->is_width_dynamic();

  case TYPE_ROW:
  case TYPE_COLUMN:
    for (size_type i = 0; i < m_containerSize; ++i)
      if (m_container[i]->is_width_dynamic())
        return true;

    return false;
  }

  return false;
}