                  (int)m_download->download()->peers_complete(),
                  (int)m_download->download()->peers_accounted(),
                  std::floor(m_download->distributed_copies() * 100.0f) / 100.0f);

  const uint8_t* seen = m_download->download()->chunks_seen();

  if (seen == NULL || m_download->download()->bitfield()->empty()) {
    m_canvas->print(2, 2, "Not available.");
    return;
  }

  if (!m_download->is_done()) { 
    m_canvas->print(36, 0, "X downloaded    missing    queued    downloading");
