void
SignalHandler::caught(int signum) {
  if ((unsigned)signum >= HIGHEST_SIGNAL)
    throw std::logic_error("SignalHandler::caught(...) received invalid signal from the kernel, bork bork bork");

  if (m_handlers[signum].empty())
    throw std::logic_error("SignalHandler::caught(...) received a signal we don't have a handler for");

  m_handlers[signum]();
}