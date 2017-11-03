void
ElementLogComplete::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error("ui::ElementLogComplete::activate(...) is_active().");

  control->input()->push_back(&m_bindings);

  m_window = new WLogComplete(m_log);
  m_window->set_active(true);

  m_frame = frame;
  m_frame->initialize_window(m_window);
}