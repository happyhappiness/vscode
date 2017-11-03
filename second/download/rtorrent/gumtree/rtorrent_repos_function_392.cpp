void
ElementTrackerList::receive_cycle_group() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementTrackerList::receive_group_cycle(...) called on a disabled object");

  torrent::TrackerList tl = m_download->download()->tracker_list();

  if (m_focus >= tl.size())
    throw torrent::internal_error("ui::ElementTrackerList::receive_group_cycle(...) called with an invalid focus");

  tl.cycle_group(tl.get(m_focus).group());

  m_window->mark_dirty();
}