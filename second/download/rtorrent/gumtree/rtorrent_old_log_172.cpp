print_buffer(first, last, " [Listen %s:%u]",
		       torrent::local_address().c_str(),
		       (unsigned int)torrent::listen_port());