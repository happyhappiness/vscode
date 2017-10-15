  m_canvas->erase();

  if (m_canvas->height() < 3 || m_canvas->width() < 18)
    return;

  m_canvas->print(2, 0, "Chunks seen: [C/A/D %i/%i/%.2f]",
                  (int)m_download->download()->peers_complete() + m_download->download()->file_list()->is_done(),
                  (int)m_download->download()->peers_accounted(),
                  std::floor(m_download->distributed_copies() * 100.0f) / 100.0f);

  const uint8_t* seen = m_download->download()->chunks_seen();

  if (seen == NULL || m_download->download()->file_list()->bitfield()->empty()) {
