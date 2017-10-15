m_canvas->print(0, 1, "Peers: %i(%i) Min/Max: %i/%i Uploads: %i",
		  (int)m_download->get_download().get_peers_connected(),
		  (int)m_download->get_download().get_peers_not_connected(),
		  (int)m_download->get_download().get_peers_min(),
		  (int)m_download->get_download().get_peers_max(),
		  (int)m_download->get_download().get_uploads_max());