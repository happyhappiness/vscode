 char*
 print_hhmmss_local(char* first, char* last, time_t t) {
   std::tm *u = std::localtime(&t);
   
   if (u == NULL)
     //return "inv_time";
-    throw torrent::internal_error("print_hhmmss_local(...) failed.");
+    throw torrent::client_error("print_hhmmss_local(...) failed.");
 
   return print_buffer(first, last, "%2u:%02u:%02u", u->tm_hour, u->tm_min, u->tm_sec);
 }
 
 char*
 print_ddhhmm(char* first, char* last, time_t t) {
