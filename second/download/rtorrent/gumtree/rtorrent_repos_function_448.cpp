void
Log::push_front(const std::string& msg) {
  if (!m_enabled)
    return;

  Base::push_front(Type(cachedTime, msg));

  if (size() > 50)
    Base::pop_back();

  m_signalUpdate.emit();
}