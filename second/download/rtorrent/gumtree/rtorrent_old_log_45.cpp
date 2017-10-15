m_canvas->print(0, 0, "Throttle U/D: %s Listen: %s:%i Handshakes: %i",
		  buf,
		  m_core->get_dns().empty() ? "<default>" : m_core->get_dns().c_str(),
		  (int)torrent::get(torrent::LISTEN_PORT),
		  (int)torrent::get(torrent::HANDSHAKES_TOTAL));