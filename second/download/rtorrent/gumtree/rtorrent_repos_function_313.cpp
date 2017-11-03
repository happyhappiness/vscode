void
Download::receive_prev_priority() {
  m_download->set_priority((m_download->priority() - 1) % 4);
}