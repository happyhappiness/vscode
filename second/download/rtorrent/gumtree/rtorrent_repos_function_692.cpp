void
Frame::initialize_window(Window* window) {
  if (m_type != TYPE_NONE)
    throw torrent::internal_error("Frame::initialize_window(...) m_type != TYPE_NONE.");

  m_type = TYPE_WINDOW;
  m_window = window;
}