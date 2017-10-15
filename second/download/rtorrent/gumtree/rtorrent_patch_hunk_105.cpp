     first = print_buffer(first, last, " [Bind %s]", bindAddress.c_str());
 
   return first;
 }
 
 char*
-print_status_extra(char* first, char* last, Control* c) {
+print_status_extra(char* first, char* last, __UNUSED Control* c) {
   first = print_buffer(first, last, " [U %i/%i]",
 		       torrent::currently_unchoked(),
 		       torrent::max_unchoked());
 
   first = print_buffer(first, last, " [S %i/%i/%i]",
 		       torrent::total_handshakes(),
