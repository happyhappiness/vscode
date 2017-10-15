		  (int)m_download->get_download().get_peers_connected(),
		  (int)m_download->get_download().get_peers_not_connected(),
		  (int)m_download->get_download().get_peers_min(),
		  (int)m_download->get_download().get_peers_max(),
		  (int)m_download->get_download().get_uploads_max());

  m_canvas->print(0, 2, "Tracker: [%c:%i] %s",
		  m_download->get_download().is_tracker_busy() ? 'C' : ' ',
		  (int)(m_download->get_download().get_tracker_timeout() / 1000000),
		  m_download->get_tracker_msg().c_str());
}

}
