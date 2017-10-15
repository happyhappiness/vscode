void
DownloadFactory::receive_failed(const std::string& msg) {
  // Add message to log.
  if (m_printLog)
    m_manager->push_log_std(msg + ": \"" + m_uri + "\"");

  m_slotFinished();
}