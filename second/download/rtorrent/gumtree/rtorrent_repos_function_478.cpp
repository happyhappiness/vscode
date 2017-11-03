void
PollManagerSelect::poll(rak::timer timeout) {
  torrent::perform();
  timeout = std::min(timeout, rak::timer(torrent::next_timeout())) + 1000;

#if defined USE_VARIABLE_FDSET
  std::memset(m_readSet, 0, m_setSize);
  std::memset(m_writeSet, 0, m_setSize);
  std::memset(m_errorSet, 0, m_setSize);
#else
  FD_ZERO(m_readSet);
  FD_ZERO(m_writeSet);
  FD_ZERO(m_errorSet);
#endif    

  unsigned int maxFd = static_cast<torrent::PollSelect*>(m_poll)->fdset(m_readSet, m_writeSet, m_errorSet);

  if (!m_httpStack.empty())
    maxFd = std::max(maxFd, m_httpStack.fdset(m_readSet, m_writeSet, m_errorSet));

  timeval t = timeout.tval();

  if (select(maxFd + 1, m_readSet, m_writeSet, m_errorSet, &t) == -1)
    return check_error();

  if (!m_httpStack.empty())
    m_httpStack.perform();

  torrent::perform();
  static_cast<torrent::PollSelect*>(m_poll)->perform(m_readSet, m_writeSet, m_errorSet);
}