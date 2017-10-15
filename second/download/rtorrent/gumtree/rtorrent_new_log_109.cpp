m_canvas->print(0, 0, "Throttle U/D: %s  Rate: %5.1f / %5.1f KB  Listen: %s:%i%s",
		  buf,
		  (double)torrent::up_rate()->rate() / 1024.0,
		  (double)torrent::down_rate()->rate() / 1024.0,
		  !torrent::local_address().empty() ? torrent::local_address().c_str() : "<default>",
		  (int)torrent::listen_port(),
		  !torrent::bind_address().empty() ? ("  Bind: " + torrent::bind_address()).c_str() : "");