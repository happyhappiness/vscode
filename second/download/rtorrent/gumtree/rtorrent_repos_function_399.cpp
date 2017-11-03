void
ElementTransferList::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error("ui::ElementTransferList::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_window = new WTransferList(m_download, &m_focus);
  m_window->set_active(true);

  m_frame = frame;
  m_frame->initialize_window(m_window);
}