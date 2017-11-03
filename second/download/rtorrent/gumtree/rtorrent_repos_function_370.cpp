void
ElementMenu::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error("ui::ElementMenu::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_focus = focus;
  focus_entry(m_entry);

  m_frame = frame;
  m_frame->initialize_window(m_window);

  m_window->set_active(true);
}