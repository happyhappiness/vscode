m_canvas->print(2, 0, "Chunks seen: [C/A/D %i/%i/%.2f]",
                  (int)m_download->download()->peers_complete() + m_download->download()->file_list()->is_done(),
                  (int)m_download->download()->peers_accounted(),
                  std::floor(m_download->distributed_copies() * 100.0f) / 100.0f);