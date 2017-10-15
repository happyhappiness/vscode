print_buffer(first, last, " [S %i/%i/%i]",
                       torrent::total_handshakes(),
                       torrent::open_sockets(),
                       torrent::max_open_sockets());