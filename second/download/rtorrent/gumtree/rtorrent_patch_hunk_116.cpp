     first = print_buffer(first, last, "/%3i KB]", torrent::down_throttle() / 1024);
   
   first = print_buffer(first, last, " [Rate %5.1f/%5.1f KB]",
 		       (double)torrent::up_rate()->rate() / 1024.0,
 		       (double)torrent::down_rate()->rate() / 1024.0);
 
-  first = print_buffer(first, last, " [Listen %s:%u]",
-		       torrent::local_address().c_str(),
-		       (unsigned int)torrent::listen_port());
+  first = print_buffer(first, last, " [Port: %i]", (unsigned int)torrent::connection_manager()->listen_port());
+
+  if (!rak::socket_address::cast_from(torrent::connection_manager()->local_address())->is_address_any()) {
+    first = print_buffer(first, last, " [Local ");
+    first = print_address(first, last, torrent::connection_manager()->local_address());
+    first = print_buffer(first, last, "]");
+  }
   
   if (first > last)
     throw torrent::internal_error("print_status_info(...) wrote past end of the buffer.");
 
-  std::string bindAddress = torrent::bind_address();
-
-  if (!bindAddress.empty())
-    first = print_buffer(first, last, " [Bind %s]", bindAddress.c_str());
+  if (!rak::socket_address::cast_from(torrent::connection_manager()->bind_address())->is_address_any()) {
+    first = print_buffer(first, last, " [Bind ");
+    first = print_address(first, last, torrent::connection_manager()->bind_address());
+    first = print_buffer(first, last, "]");
+  }
 
   return first;
 }
 
 char*
 print_status_extra(char* first, char* last, __UNUSED Control* c) {
