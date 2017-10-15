char*
print_status_extra(char* first, char* last) {
  first = print_buffer(first, last, " [U %i/%i]",
                       torrent::currently_unchoked(),
                       torrent::max_unchoked());

  first = print_buffer(first, last, " [D %i/%i]",
                       torrent::download_unchoked(),
                       torrent::max_download_unchoked());

  first = print_buffer(first, last, " [H %u/%u]",
                       control->core()->http_stack()->active(),
                       control->core()->http_stack()->max_active());                       

  first = print_buffer(first, last, " [S %i/%i/%i]",
                       torrent::total_handshakes(),
                       torrent::connection_manager()->size(),
                       torrent::connection_manager()->max_size());
                       
  first = print_buffer(first, last, " [F %i/%i]",
                       torrent::file_manager()->open_files(),
                       torrent::file_manager()->max_open_files());

  return first;
}