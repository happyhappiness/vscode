         /* XXX: we really need to make sure this new generation number isn't in
          * use by any of the children.
          */
         ++ap_my_generation;
         ap_scoreboard_image->global->running_generation = ap_my_generation;
 
-        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00227)
                 "Graceful restart requested, doing restart");
 
         /* Wait for all of the threads to terminate before initiating the restart */
         while (worker_thread_count > 0) {
             printf ("\rRestart pending. Waiting for %d thread(s) to terminate...",
                     worker_thread_count);
