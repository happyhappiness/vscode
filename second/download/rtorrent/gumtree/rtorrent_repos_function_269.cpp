void
SCgiTask::open(SCgi* parent, int fd) {
  m_parent   = parent;
  m_fileDesc = fd;
  m_buffer   = new char[(m_bufferSize = default_buffer_size) + 1];
  m_position = m_buffer;
  m_body     = NULL;

  control->poll()->open(this);
  control->poll()->insert_read(this);
  control->poll()->insert_error(this);

//   scgiTimer = rak::timer::current();
}