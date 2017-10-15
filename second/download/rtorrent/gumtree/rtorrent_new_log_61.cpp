m_canvas->print(0, 2, "[%c:%i] %s",
		  m_download->get_download().is_tracker_busy() ? 'C' : ' ',
		  (int)(m_download->get_download().get_tracker_timeout() / 1000000),
		  buffer);