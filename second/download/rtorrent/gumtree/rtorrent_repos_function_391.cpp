void
ElementTrackerList::receive_prev() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementTrackerList::receive_prev(...) called on a disabled object");

  if (m_download->download()->tracker_list().size() == 0)
    return;

  if (m_focus != 0)
    --m_focus;
  else 
    m_focus = m_download->download()->tracker_list().size() - 1;

  m_window->mark_dirty();
}