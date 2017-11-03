void
ElementTransferList::receive_pagenext() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementTransferList::receive_pagenext(...) called on a disabled object");

  unsigned int visible = m_window->height() - 1;
  unsigned int scrollable = std::max<int>(m_window->rows() - visible, 0);

  if (scrollable == 0 || m_focus == scrollable)
    m_focus = 0;
  else if (m_focus + visible / 2 < scrollable)
    m_focus += visible / 2;
  else 
    m_focus = scrollable;

//   m_window->mark_dirty();
}