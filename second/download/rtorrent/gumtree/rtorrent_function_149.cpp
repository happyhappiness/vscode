char*
print_status_extra(char* first, char* last, Control* c) {
  first = print_buffer(first, last, " [U %i/%i]",
		       torrent::currently_unchoked(),
		       torrent::max_unchoked());

  first = print_buffer(first, last, " [S %i/%i/%i]",
		       torrent::total_handshakes(),
		       torrent::open_sockets(),
		       torrent::max_open_sockets());
		       
  first = print_buffer(first, last, " [F %i/%i]",
		       torrent::open_files(),
		       torrent::max_open_files());

  return first;
}