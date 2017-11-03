void
Frame::initialize_row(size_type size) {
  if (m_type != TYPE_NONE)
    throw torrent::internal_error("Frame::initialize_container(...) Invalid state.");

  if (size > max_size)
    throw torrent::internal_error("Frame::initialize_container(...) size >= max_size.");

  m_type = TYPE_ROW;
  m_containerSize = size;

  for (size_type i = 0; i < m_containerSize; ++i)
    m_container[i] = new Frame();
}