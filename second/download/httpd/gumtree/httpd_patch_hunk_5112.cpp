             }
         }
     }
 
     for (i = 0; i < threads_per_child; i++) {
         if (threads[i]) { /* if we ever created this thread */
+            if (mode != ST_GRACEFUL) {
 #ifdef HAVE_PTHREAD_KILL
-            apr_os_thread_t *worker_os_thread;
+                apr_os_thread_t *worker_os_thread;
 
-            apr_os_thread_get(&worker_os_thread, threads[i]);
-            pthread_kill(*worker_os_thread, WORKER_SIGNAL);
+                apr_os_thread_get(&worker_os_thread, threads[i]);
+                pthread_kill(*worker_os_thread, WORKER_SIGNAL);
 #endif
+            }
 
             rv = apr_thread_join(&thread_rv, threads[i]);
             if (rv != APR_SUCCESS) {
                 ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00278)
                              "apr_thread_join: unable to join worker "
                              "thread %d",
