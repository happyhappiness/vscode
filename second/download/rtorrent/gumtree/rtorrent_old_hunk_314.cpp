  m_position = m_buffer;
  m_bufferSize = length + headerSize;
  
  std::memcpy(m_buffer + headerSize, buffer, length);

  if (m_parent->log_fd() >= 0) {
    // Clean up logging, this is just plain ugly...
    //    write(m_logFd, "\n---\n", sizeof("\n---\n"));
    write(m_parent->log_fd(), m_buffer, m_bufferSize);
    write(m_parent->log_fd(), "\n---\n", sizeof("\n---\n"));
  }

  event_write();
  return true;
}

}
