m_canvas->print(0, 2, "[%c:%i] %s",
                  m_download->tracker_list()->is_busy() ? 'C' : ' ',
                  (int)(m_download->download()->tracker_list().timeout() / 1000000),
                  buffer);