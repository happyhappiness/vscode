    }
  }

  if ((unsigned int)std::distance(m_buffer, m_position) != m_bufferSize)
    return;

  control->poll()->remove_read(this);
  control->poll()->insert_write(this);

  // Close if the call failed, else stay open to write back data.
  if (!m_parent->receive_call(this, m_body, m_bufferSize - std::distance(m_buffer, m_body)))
    close();

  return;
