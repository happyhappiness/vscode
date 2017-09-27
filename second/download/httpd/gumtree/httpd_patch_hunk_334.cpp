         ap_scoreboard_image->global->running_generation = ap_my_generation;
 
     	ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
 		    "Graceful restart requested, doing restart");
 
         /* Wait for all of the threads to terminate before initiating the restart */
-        DBPRINT0 ("Restart pending. Waiting for threads to terminate...\n");
         while (worker_thread_count > 0) {
+            printf ("\rRestart pending. Waiting for %d thread(s) to terminate...",
+                    worker_thread_count);
             apr_thread_yield();
         }
-        DBPRINT0 ("restarting...\n");
+        printf ("\nRestarting...\n");
     }
 
     return 0;
 }
 
 static int netware_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
 {
     int debug;
     char *addrname = NULL;
 
+    mpm_state = AP_MPMQ_STARTING;
+
     debug = ap_exists_config_define("DEBUG");
 
     is_graceful = 0;
     ap_my_pid = getpid();
     addrname = getaddressspacename (NULL, NULL);
     if (addrname) {
