void
ElementTransferList::receive_pageprev() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementTransferList::receive_pageprev(...) called on a disabled object");

  unsigned int visible = m_window->height() - 1;
  unsigned int scrollable = std::max<int>(m_window->rows() - visible, 0);

  if (m_focus > visible / 2)
    m_focus -= visible / 2;
  else if (scrollable > 0 && m_focus == 0)
    m_focus = scrollable;
  else
    m_focus = 0;

//   m_window->mark_dirty();
}