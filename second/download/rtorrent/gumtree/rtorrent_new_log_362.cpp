m_canvas->print(0, 2, "[%c:%i] %s",
                  m_download->tracker_list()->has_active() ? 'C' : ' ',
                  (int)(m_download->download()->tracker_controller()->seconds_to_next_timeout()),
                  buffer);