void
ElementChunksSeen::disable() {
  if (!is_active())
    throw torrent::internal_error("ui::ElementChunksSeen::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  m_frame->clear();
  m_frame = NULL;

  delete m_window;
  m_window = NULL;
}