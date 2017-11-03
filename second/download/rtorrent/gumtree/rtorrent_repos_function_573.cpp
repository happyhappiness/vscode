void
Manager::initialize_first() {
  if ((m_pollManager = PollManagerEPoll::create(sysconf(_SC_OPEN_MAX))) != NULL)
    m_logImportant.push_front("Using 'epoll' based polling.");

  else if ((m_pollManager = PollManagerKQueue::create(sysconf(_SC_OPEN_MAX))) != NULL)
    m_logImportant.push_front("Using 'kqueue' based polling.");

  else if ((m_pollManager = PollManagerSelect::create(sysconf(_SC_OPEN_MAX))) != NULL)
    m_logImportant.push_front("Using 'select' based polling.");

  else
    throw std::runtime_error("Could not create any PollManager.");

  // Need to initialize this before parseing options.
  torrent::initialize(m_pollManager->get_torrent_poll());
}