 
   first = print_buffer(first, last, " [D %i/%i]",
                        torrent::download_unchoked(),
                        torrent::max_download_unchoked());
 
   first = print_buffer(first, last, " [H %u/%u]",
-                       control->core()->get_poll_manager()->get_http_stack()->active(),
-                       control->core()->get_poll_manager()->get_http_stack()->max_active());                       
+                       control->core()->http_stack()->active(),
+                       control->core()->http_stack()->max_active());                       
 
   first = print_buffer(first, last, " [S %i/%i/%i]",
                        torrent::total_handshakes(),
                        torrent::connection_manager()->size(),
                        torrent::connection_manager()->max_size());
                        
