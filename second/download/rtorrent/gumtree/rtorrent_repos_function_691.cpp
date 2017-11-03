void
Frame::set_container_size(size_type size) {
  if ((m_type != TYPE_ROW && m_type != TYPE_COLUMN) || size >= max_size)
    throw torrent::internal_error("Frame::set_container_size(...) Bad state.");

  while (m_containerSize > size) {
    delete m_container[--m_containerSize];
    m_container[m_containerSize] = NULL;
  }

  while (m_containerSize < size) {
    m_container[m_containerSize++] = new Frame();
  }
}