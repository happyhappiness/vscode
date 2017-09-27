          * listener_may_exit flag is clear and the time it enters a
          * blocking syscall, the signal didn't do any good...  work around
          * that by sleeping briefly and sending it again
          */
 
         iter = 0;
-        while (iter < 10 &&
-#ifdef HAVE_PTHREAD_KILL
-               pthread_kill(*listener_os_thread, 0)
-#else
-               kill(ap_my_pid, 0)
-#endif
-               == 0) {
-            /* listener not dead yet */
+        while (iter < 10 && !dying) {
+            /* listener has not stopped accepting yet */
             apr_sleep(apr_time_make(0, 500000));
             wakeup_listener();
             ++iter;
         }
         if (iter >= 10) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
-                         "the listener thread didn't exit");
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00475)
+                         "the listener thread didn't stop accepting");
         }
         else {
             rv = apr_thread_join(&thread_rv, listener);
             if (rv != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
+                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00476)
                              "apr_thread_join: unable to join listener thread");
             }
         }
     }
 
     for (i = 0; i < threads_per_child; i++) {
         if (threads[i]) {       /* if we ever created this thread */
             rv = apr_thread_join(&thread_rv, threads[i]);
             if (rv != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
+                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00477)
                              "apr_thread_join: unable to join worker "
                              "thread %d", i);
             }
         }
     }
 }
