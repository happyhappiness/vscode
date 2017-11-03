void
ElementChunksSeen::receive_pagenext() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementChunksSeen::receive_pagenext(...) called on a disabled object");

  unsigned int visible = m_window->height() - 1;
  unsigned int maxFocus = m_window->max_focus();

  if (maxFocus == 0 || m_focus == maxFocus)
    m_focus = 0;
  else if (m_focus + visible / 2 < maxFocus)
    m_focus += visible / 2;
  else 
    m_focus = maxFocus;

  m_window->mark_dirty();
}