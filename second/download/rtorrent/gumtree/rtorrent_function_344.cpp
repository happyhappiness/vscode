void
SCgiTask::event_read() {
  int bytes = ::recv(m_fileDesc, m_position, m_bufferSize - (m_position - m_buffer), 0);

  if (bytes <= 0) {
    if (bytes == 0 || !rak::error_number::current().is_blocked_momentary())
      close();

    return;
  }

  // The buffer has space to nul-terminate to ease the parsing below.
  m_position += bytes;
  *m_position = '\0';

  if (m_body == NULL) {
    // Don't bother caching the parsed values, as we're likely to
    // receive all the data we need the first time.
    char* current;

    int contentSize;
    int headerSize = strtol(m_buffer, &current, 0);

    if (current == m_position)
      return;

    // If the request doesn't start with an integer or if it didn't
    // end in ':', then close the connection.
    if (current == m_buffer || *current != ':' || headerSize < 17 || headerSize > max_header_size)
      goto event_read_failed;

    if (std::distance(++current, m_position) < headerSize + 1)
      return;

    if (std::memcmp(current, "CONTENT_LENGTH", 15) != 0)
      goto event_read_failed;

    char* contentPos;
    contentSize = strtol(current + 15, &contentPos, 0);

    if (*contentPos != '\0' || contentSize <= 0 || contentSize > max_content_size)
      goto event_read_failed;

    m_body = current + headerSize + 1;
    headerSize = std::distance(m_buffer, m_body);

    if ((unsigned int)(contentSize + headerSize) < m_bufferSize) {
      m_bufferSize = contentSize + headerSize;

    } else if ((unsigned int)contentSize <= default_buffer_size) {
      m_bufferSize = contentSize;

      std::memmove(m_buffer, m_body, std::distance(m_body, m_position));
      m_position = m_buffer + std::distance(m_body, m_position);
      m_body = m_buffer;

    } else {
      realloc_buffer((m_bufferSize = contentSize) + 1, m_body, std::distance(m_body, m_position));

      m_position = m_buffer + std::distance(m_body, m_position);
      m_body = m_buffer;
    }
  }

  if ((unsigned int)std::distance(m_buffer, m_position) != m_bufferSize)
    return;

  this_thread->poll()->remove_read(this);
  this_thread->poll()->insert_write(this);

  if (m_parent->log_fd() >= 0) {
    // Clean up logging, this is just plain ugly...
    //    write(m_logFd, "\n---\n", sizeof("\n---\n"));
    write(m_parent->log_fd(), m_buffer, m_bufferSize);
    write(m_parent->log_fd(), "\n---\n", sizeof("\n---\n"));
  }

  // Close if the call failed, else stay open to write back data.
  if (!m_parent->receive_call(this, m_body, m_bufferSize - std::distance(m_buffer, m_body)))
    close();

  return;

 event_read_failed:
//   throw torrent::internal_error("SCgiTask::event_read() fault not handled.");
  close();
}