  first = print_buffer(first, last, " [S %i/%i/%i]",
                       torrent::total_handshakes(),
                       torrent::connection_manager()->size(),
                       torrent::connection_manager()->max_size());
                       
  first = print_buffer(first, last, " [F %i/%i]",
                       torrent::open_files(),
                       torrent::max_open_files());

  return first;
}

}
