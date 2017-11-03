void
SCgiTask::event_write() {
  int bytes = ::send(m_fileDesc, m_position, m_bufferSize, 0);

  if (bytes == -1) {
    if (!rak::error_number::current().is_blocked_momentary())
      close();

    return;
  }

  m_position += bytes;
  m_bufferSize -= bytes;

  if (bytes == 0 || m_bufferSize == 0)
    return close();
}