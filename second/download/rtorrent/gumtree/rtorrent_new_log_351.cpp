print_buffer(first, last, " [F %i/%i]",
                       torrent::file_manager()->open_files(),
                       torrent::file_manager()->max_open_files());