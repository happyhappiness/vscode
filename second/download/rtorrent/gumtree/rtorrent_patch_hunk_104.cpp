 
   return print_buffer(first, last, "%02u/%02u/%04u", u->tm_mday, (u->tm_mon + 1), (1900 + u->tm_year));
 }
 
 char*
 print_download_title(char* first, char* last, core::Download* d) {
-  return print_buffer(first, last, "%s", d->get_download().name().c_str());
+  return print_buffer(first, last, " %s", d->get_download().name().c_str());
 }
 
 char*
 print_download_info(char* first, char* last, core::Download* d) {
   first = print_buffer(first, last, "Torrent: ");
 
