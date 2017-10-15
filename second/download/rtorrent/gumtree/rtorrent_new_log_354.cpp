print_buffer(first, last, " [U %i/%i]",
                       torrent::resource_manager()->currently_upload_unchoked(),
                       torrent::resource_manager()->max_upload_unchoked());