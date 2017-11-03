void
ElementTransferList::disable() {
  if (!is_active())
    throw torrent::internal_error("ui::ElementTransferList::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  m_frame->clear();
  m_frame = NULL;

  delete m_window;
  m_window = NULL;
}