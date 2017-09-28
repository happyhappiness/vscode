             double perc;
             time_t eta, elapsed;
             off_t remaining_bytes = server.loading_total_bytes-
                                     server.loading_loaded_bytes;
 
             perc = ((double)server.loading_loaded_bytes /
-                   server.loading_total_bytes) * 100;
+                   (server.loading_total_bytes+1)) * 100;
 
-            elapsed = server.unixtime-server.loading_start_time;
+            elapsed = time(NULL)-server.loading_start_time;
             if (elapsed == 0) {
                 eta = 1; /* A fake 1 second figure if we don't have
                             enough info */
             } else {
-                eta = (elapsed*remaining_bytes)/server.loading_loaded_bytes;
+                eta = (elapsed*remaining_bytes)/(server.loading_loaded_bytes+1);
             }
 
             info = sdscatprintf(info,
                 "loading_start_time:%jd\r\n"
                 "loading_total_bytes:%llu\r\n"
                 "loading_loaded_bytes:%llu\r\n"
