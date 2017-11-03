void
SignalHandler::set_ignore(unsigned int signum) {
  if (signum >= HIGHEST_SIGNAL)
    throw std::logic_error("SignalHandler::clear(...) received invalid signal value");

  signal(signum, SIG_IGN);
  m_handlers[signum].disconnect();
}