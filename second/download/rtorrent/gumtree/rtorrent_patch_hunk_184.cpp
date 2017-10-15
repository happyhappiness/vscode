     first = print_buffer(first, last, " [Local ");
     first = print_address(first, last, torrent::connection_manager()->local_address());
     first = print_buffer(first, last, "]");
   }
   
   if (first > last)
-    throw torrent::client_error("print_status_info(...) wrote past end of the buffer.");
+    throw torrent::internal_error("print_status_info(...) wrote past end of the buffer.");
 
   if (!rak::socket_address::cast_from(torrent::connection_manager()->bind_address())->is_address_any()) {
     first = print_buffer(first, last, " [Bind ");
     first = print_address(first, last, torrent::connection_manager()->bind_address());
     first = print_buffer(first, last, "]");
   }
