inline void
Frame::balance_window(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  // Ensure that we don't draw windows that are offscreen or have
  // zero extent.
  if (width == 0 || height == 0 || !m_window->is_active()) {
    m_window->set_offscreen(true);
    return;
  }

  if (width > m_window->max_width()) {
    if (m_window->is_left())
      x += width - m_window->max_width();

    width = m_window->max_width();
  }

  if (height > m_window->max_height()) {
    if (m_window->is_bottom())
      y += height - m_window->max_height();

    height = m_window->max_height();
  }

  m_window->set_offscreen(false);
  m_window->resize(x, y, width, height);
  m_window->mark_dirty();
}