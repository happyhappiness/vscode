print_buffer(first, last, " [D %i/%i]",
                       torrent::download_unchoked(),
                       torrent::max_download_unchoked());