void
ElementChunksSeen::receive_next() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementChunksSeen::receive_next(...) called on a disabled object");

  if (++m_focus > m_window->max_focus())
    m_focus = 0;

  m_window->mark_dirty();
}