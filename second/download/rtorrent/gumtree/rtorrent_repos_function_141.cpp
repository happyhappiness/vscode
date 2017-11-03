void
SignalHandler::set_handler(unsigned int signum, Slot slot) {
  if (signum >= HIGHEST_SIGNAL)
    throw std::logic_error("SignalHandler::handle(...) received invalid signal value");

  if (slot.empty())
    throw std::logic_error("SignalHandler::handle(...) received an empty slot");

  signal(signum, &SignalHandler::caught);
  m_handlers[signum] = slot;
}