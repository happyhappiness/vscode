                 }
             }
         }
         else {
             if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                 != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
+                int level = APLOG_EMERG;
+
+                if (ap_scoreboard_image->parent[process_slot].generation != 
+                    ap_scoreboard_image->global->running_generation) {
+                    level = APLOG_DEBUG; /* common to get these at restart time */
+                }
+                ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
                              "apr_proc_mutex_unlock failed. Attempting to "
                              "shutdown process gracefully.");
                 signal_threads(ST_GRACEFUL);
             }
             break;
         }
