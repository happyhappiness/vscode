            at a time so we need to fall on our sword... */
         ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                      "Couldn't create accept lock");
         return 1;
     }
 
-    /* worker_thread_count_mutex
-     * locks the worker_thread_count so we have ana ccurate count...
-     */
-    rv = apr_thread_mutex_create(&worker_thread_count_mutex, 0, pconf);
-    if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
-                     "Couldn't create worker thread count lock");
-        return 1;
-    }
-
     /*
-     * Startup/shutdown... 
+     * Startup/shutdown...
      */
-    
+
     if (!is_graceful) {
         /* setup the scoreboard shared memory */
         if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
             return 1;
         }
 
