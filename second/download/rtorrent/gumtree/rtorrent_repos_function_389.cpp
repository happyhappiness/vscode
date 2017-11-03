void
ElementTrackerList::receive_disable() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementTrackerList::receive_disable(...) called on a disabled object");

  torrent::Tracker t = m_download->download()->tracker_list().get(m_focus);

  if (t.is_enabled())
    t.disable();
  else
    t.enable();

  m_window->mark_dirty();
}