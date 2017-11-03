void
ElementPeerList::disable() {
  if (!is_active())
    throw torrent::internal_error("ui::ElementPeerList::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  activate_display(DISPLAY_MAX_SIZE);

  m_frame->clear();
  m_frame = NULL;
}