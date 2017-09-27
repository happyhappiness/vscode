                 }
             }
             else if (ap_unregister_extra_mpm_process(pid.pid, &old_gen) == 1) {
                 worker_note_child_killed(-1, /* already out of the scoreboard */
                                          pid.pid, old_gen);
                 if (processed_status == APEXIT_CHILDSICK
-                    && old_gen == retained->my_generation) {
+                    && old_gen == retained->mpm->my_generation) {
                     /* resource shortage, minimize the fork rate */
                     for (i = 0; i < num_buckets; i++) {
                         retained->idle_spawn_rate[i] = 1;
                     }
                 }
 #if APR_HAS_OTHER_CHILD
             }
             else if (apr_proc_other_child_alert(&pid, APR_OC_REASON_DEATH,
                                                 status) == 0) {
                 /* handled */
 #endif
             }
-            else if (retained->is_graceful) {
+            else if (retained->mpm->was_graceful) {
                 /* Great, we've probably just lost a slot in the
                  * scoreboard.  Somehow we don't know about this child.
                  */
                 ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                              ap_server_conf, APLOGNO(00291)
                              "long lost child came home! (pid %ld)",
