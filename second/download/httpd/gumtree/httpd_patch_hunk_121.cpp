     if (ap_threads_max_free < ap_threads_min_free + 1)	/* Don't thrash... */
         ap_threads_max_free = ap_threads_min_free + 1;
     request_count = 0;
 
     startup_workers(ap_threads_to_start);
 
-     /* Allow the Apache screen to be closed normally on exit()*/
-    hold_screen_on_exit = 0;
+     /* Allow the Apache screen to be closed normally on exit() only if it
+        has not been explicitly forced to close on exit(). (ie. the -E flag
+        was specified at startup) */
+    if (hold_screen_on_exit > 0) {
+        hold_screen_on_exit = 0;
+    }
 
     ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
 		"%s configured -- resuming normal operations",
 		ap_get_server_version());
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
 		"Server built: %s", ap_get_server_built());
