void
ElementTrackerList::disable() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementTrackerList::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  m_frame->clear();
  m_frame = NULL;

  delete m_window;
  m_window = NULL;
}