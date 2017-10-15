m_canvas->print(0, 0, "Throttle U/D: %s  Rate: %5.1f / %5.1f KiB  Listen: %s:%i%s",
		  buf,
		  (double)torrent::get_write_rate().rate() / 1024.0,
		  (double)torrent::get_read_rate().rate() / 1024.0,
		  !torrent::get_address().empty() ? torrent::get_address().c_str() : "<default>",
		  (int)torrent::get_listen_port(),
		  !torrent::get_bind_address().empty() ? ("  Bind: " + torrent::get_bind_address()).c_str() : "");