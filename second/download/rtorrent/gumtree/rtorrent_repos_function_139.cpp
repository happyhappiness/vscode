void
SignalHandler::set_default(unsigned int signum) {
  if (signum >= HIGHEST_SIGNAL)
    throw std::logic_error("SignalHandler::clear(...) received invalid signal value");

  signal(signum, SIG_DFL);
  m_handlers[signum].disconnect();
}