void
ElementDownloadList::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error("ui::ElementDownloadList::activate(...) is_active().");

  control->input()->push_back(&m_bindings);

  m_window = new WDownloadList();
  m_window->set_active(true);
  m_window->set_view(m_view);

  m_frame = frame;
  m_frame->initialize_window(m_window);
}