 #if APR_HAS_OTHER_CHILD
             else if (apr_proc_other_child_alert(&pid, APR_OC_REASON_DEATH,
                                                 status) == 0) {
                 /* handled */
             }
 #endif
-            else if (retained->is_graceful) {
+            else if (retained->mpm->was_graceful) {
                 /* Great, we've probably just lost a slot in the
                  * scoreboard.  Somehow we don't know about this child.
                  */
                 ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                              ap_server_conf, APLOGNO(00488)
                              "long lost child came home! (pid %ld)",
