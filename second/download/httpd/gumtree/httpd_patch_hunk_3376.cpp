 #if APR_HAS_OTHER_CHILD
             }
             else if (apr_proc_other_child_alert(&pid, APR_OC_REASON_DEATH, status) == APR_SUCCESS) {
                 /* handled */
 #endif
             }
-            else if (is_graceful) {
+            else if (retained->is_graceful) {
                 /* Great, we've probably just lost a slot in the
                  * scoreboard.  Somehow we don't know about this
                  * child.
                  */
                 ap_log_error(APLOG_MARK, APLOG_WARNING,
-                            0, ap_server_conf,
+                            0, ap_server_conf, APLOGNO(00167)
                             "long lost child came home! (pid %ld)", (long)pid.pid);
             }
             /* Don't perform idle maintenance when a child dies,
              * only do it when there's a timeout.  Remember only a
              * finite number of children can die, and it's pretty
              * pathological for a lot to die suddenly.
