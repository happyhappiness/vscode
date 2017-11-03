void
ElementMenu::disable() {
  if (!is_active())
    throw torrent::internal_error("ui::ElementMenu::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  m_frame->clear();
  m_frame = NULL;

  m_window->set_active(false);
}