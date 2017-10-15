  first = print_buffer(first, last, " [S %i/%i/%i]",
                       torrent::total_handshakes(),
                       torrent::connection_manager()->size(),
                       torrent::connection_manager()->max_size());
                       
  first = print_buffer(first, last, " [F %i/%i]",
                       torrent::file_manager()->open_files(),
                       torrent::file_manager()->max_open_files());

  return first;
}

}
