print_buffer(first, last, " [D %i/%i]",
                       torrent::resource_manager()->currently_download_unchoked(),
                       torrent::resource_manager()->max_download_unchoked());