   first = print_buffer(first, last, " [U %i/%i]",
                        torrent::currently_unchoked(),
                        torrent::max_unchoked());
 
   first = print_buffer(first, last, " [S %i/%i/%i]",
                        torrent::total_handshakes(),
-                       torrent::open_sockets(),
-                       torrent::max_open_sockets());
+                       torrent::connection_manager()->size(),
+                       torrent::connection_manager()->max_size());
                        
   first = print_buffer(first, last, " [F %i/%i]",
                        torrent::open_files(),
                        torrent::max_open_files());
 
   return first;
