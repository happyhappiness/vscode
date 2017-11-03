void
Download::receive_next_priority() {
  m_download->set_priority((m_download->priority() + 1) % 4);
}