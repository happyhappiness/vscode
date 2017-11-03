void
ElementTrackerList::receive_next() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementTrackerList::receive_next(...) called on a disabled object");

  if (++m_focus >= m_download->download()->tracker_list().size())
    m_focus = 0;

  m_window->mark_dirty();
}