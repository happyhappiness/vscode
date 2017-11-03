void
ElementPeerList::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error("ui::ElementPeerList::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_frame = frame;
  m_focus = focus;

  activate_display(DISPLAY_LIST);
}