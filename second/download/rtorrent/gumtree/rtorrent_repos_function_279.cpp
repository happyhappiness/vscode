void
ElementStringList::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error("ui::ElementStringList::activate(...) is_active().");

  control->input()->push_back(&m_bindings);

  m_window = new WStringList();
  m_window->set_active(true);

  m_frame = frame;
  m_frame->initialize_window(m_window);
}