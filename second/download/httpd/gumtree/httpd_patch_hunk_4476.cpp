                  */
                 if (child_slot < 0
                     || ap_get_scoreboard_process(child_slot)->generation
                        == retained->my_generation) {
                     shutdown_pending = 1;
                     child_fatal = 1;
+                    /*
+                     * total_daemons counting will be off now, but as we
+                     * are shutting down, that is not an issue anymore.
+                     */
                     return;
                 }
                 else {
                     ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf, APLOGNO(00487)
                                  "Ignoring fatal error in child of previous "
                                  "generation (pid %ld).",
