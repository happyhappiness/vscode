void
ElementTrackerList::activate(display::Frame* frame, bool focus) {
  if (m_window != NULL)
    throw torrent::internal_error("ui::ElementTrackerList::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_window = new WTrackerList(m_download, &m_focus);
  m_window->set_active(true);
  m_window->set_focused(focus);

  m_frame = frame;
  m_frame->initialize_window(m_window);
}