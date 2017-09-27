                 /* E[NM]FILE, ENOMEM, etc */
                 resource_shortage = 1;
                 signal_threads(ST_GRACEFUL);
             }
             if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                 != APR_SUCCESS) {
-                int level = APLOG_EMERG;
 
                 if (listener_may_exit) {
                     break;
                 }
-                if (ap_scoreboard_image->parent[process_slot].generation !=
-                    ap_scoreboard_image->global->running_generation) {
-                    level = APLOG_DEBUG; /* common to get these at restart time */
-                }
-                ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
-                             "apr_proc_mutex_unlock failed. Attempting to "
-                             "shutdown process gracefully.");
-                signal_threads(ST_GRACEFUL);
+                accept_mutex_error("unlock", rv, process_slot);
             }
             if (csd != NULL) {
                 rv = ap_queue_push(worker_queue, csd, ptrans);
                 if (rv) {
                     /* trash the connection; we couldn't queue the connected
                      * socket to a worker
