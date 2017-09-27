         apr_thread_yield();
         apr_sleep(SCOREBOARD_MAINTENANCE_INTERVAL);
     }
     mpm_state = AP_MPMQ_STOPPING;
 
 
-    /* Shutdown the listen sockets so that we don't get stuck in a blocking call. 
+    /* Shutdown the listen sockets so that we don't get stuck in a blocking call.
     shutdown_listeners();*/
 
     if (shutdown_pending) { /* Got an unload from the console */
         ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
             "caught SIGTERM, shutting down");
 
         while (worker_thread_count > 0) {
-            printf ("\rShutdown pending. Waiting for %d thread(s) to terminate...", 
+            printf ("\rShutdown pending. Waiting for %d thread(s) to terminate...",
                     worker_thread_count);
             apr_thread_yield();
         }
 
         return 1;
     }
