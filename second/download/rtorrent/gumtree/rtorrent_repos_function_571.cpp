void
Manager::push_log(const char* msg) {
  m_logImportant.push_front(msg);
  m_logComplete.push_front(msg);
}