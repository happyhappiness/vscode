void
ElementChunksSeen::receive_pageprev() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementChunksSeen::receive_pageprev(...) called on a disabled object");

  unsigned int visible = m_window->height() - 1;
  unsigned int maxFocus = m_window->max_focus();

  if (m_focus > visible / 2)
    m_focus -= visible / 2;
  else if (maxFocus > 0 && m_focus == 0)
    m_focus = maxFocus;
  else
    m_focus = 0;

  m_window->mark_dirty();
}