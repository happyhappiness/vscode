 
   return first;
 }
 
 char*
 print_download_time_left(char* first, char* last, core::Download* d) {
-  uint32_t rate = d->download()->down_rate()->rate();
+  uint32_t rate = d->info()->down_rate()->rate();
 
   if (rate < 512)
     return print_buffer(first, last, "--d --:--");
   
   time_t remaining = (d->download()->file_list()->size_bytes() - d->download()->bytes_done()) / (rate & ~(uint32_t)(512 - 1));
 
