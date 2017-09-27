         } else {
             ResetEvent(qwait_event);
         }
         apr_thread_mutex_unlock(qlock);
   
         if (!context) {
-            /* We failed to grab a context off the queue, consider allocating a
-             * new one out of the child pool. There may be up to ap_threads_per_child
-             * contexts in the system at once.
+            /* We failed to grab a context off the queue, consider allocating
+             * a new one out of the child pool. There may be up to 
+             * (ap_threads_per_child + num_listeners) contexts in the system 
+             * at once.
              */
-            if (num_completion_contexts >= ap_threads_per_child) {
+            if (num_completion_contexts >= max_num_completion_contexts) {
                 /* All workers are busy, need to wait for one */
                 static int reported = 0;
                 if (!reported) {
                     ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                                  "Server ran out of threads to serve requests. Consider "
                                  "raising the ThreadsPerChild setting");
