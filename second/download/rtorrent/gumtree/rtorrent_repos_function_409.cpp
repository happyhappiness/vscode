void
PollManagerEPoll::poll(rak::timer timeout) {
  // Add 1ms to ensure we don't idle loop due to the lack of
  // resolution.
  torrent::perform();
  timeout = std::min(timeout, rak::timer(torrent::next_timeout())) + 1000;

  if (!m_httpStack.empty()) {
    // When we're using libcurl we need to use select, but as this is
    // inefficient we try avoiding it whenever possible.
#if defined USE_VARIABLE_FDSET
    std::memset(m_readSet, 0, m_setSize);
    std::memset(m_writeSet, 0, m_setSize);
    std::memset(m_errorSet, 0, m_setSize);
#else
    FD_ZERO(m_readSet);
    FD_ZERO(m_writeSet);
    FD_ZERO(m_errorSet);
#endif    
    FD_SET(static_cast<torrent::PollEPoll*>(m_poll)->file_descriptor(), m_readSet);

    unsigned int maxFd = std::max((unsigned int)static_cast<torrent::PollEPoll*>(m_poll)->file_descriptor(),
                                  m_httpStack.fdset(m_readSet, m_writeSet, m_errorSet));

    timeval t = timeout.tval();

    if (select(maxFd + 1, m_readSet, m_writeSet, m_errorSet, &t) == -1)
      return check_error();

    m_httpStack.perform();

    if (!FD_ISSET(static_cast<torrent::PollEPoll*>(m_poll)->file_descriptor(), m_readSet)) {
      // Need to call perform here so that scheduled task get done
      // even if there's no socket events outside of the http stuff.
      torrent::perform();
      return;
    }

    // Clear the timeout since we've already used it in the select call.
    timeout = rak::timer();
  }

  // Yes, below is how much code really *should* have been in this
  // function. ;)

  if (static_cast<torrent::PollEPoll*>(m_poll)->poll((timeout.usec() + 999) / 1000) == -1)
    return check_error();

  torrent::perform();
  static_cast<torrent::PollEPoll*>(m_poll)->perform();
}