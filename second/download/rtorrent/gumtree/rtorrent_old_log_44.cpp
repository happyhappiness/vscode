m_canvas->print(0, 0, "Throttle: %i Listen: %s:%i Handshakes: %i",
		    (int)torrent::get(torrent::THROTTLE_ROOT_CONST_RATE) / 1024,
		    m_core->get_dns().empty() ? "<default>" : m_core->get_dns().c_str(),
		    (int)torrent::get(torrent::LISTEN_PORT),
		    (int)torrent::get(torrent::HANDSHAKES_TOTAL));