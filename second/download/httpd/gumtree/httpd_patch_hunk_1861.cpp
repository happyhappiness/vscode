                 break;
 
             /* Every 30 seconds give an update */
             if ((time_remains % 30000) == 0) {
                 ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, 
                              ap_server_conf,
-                             "Child %lu: Waiting %d more seconds "
+                             "Child %d: Waiting %d more seconds "
                              "for %d worker threads to finish.", 
                              my_pid, time_remains / 1000, threads_created);
             }
             /* We'll poll from the top, 10 times per second */
             Sleep(100);
             watch_thread = 0;
