void
PollManager::check_error() {
  if (rak::error_number::current().value() != rak::error_number::e_intr)
    throw std::runtime_error("Poll::work(): " + std::string(rak::error_number::current().c_str()));
}