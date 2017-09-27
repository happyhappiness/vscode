         }
 
         perform_idle_server_maintenance();
     }
 }
 
-int ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
+static int worker_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
 {
     int remaining_children_to_start;
     apr_status_t rv;
 
     ap_log_pid(pconf, ap_pid_fname);
 
-    first_server_limit = server_limit;
-    first_thread_limit = thread_limit;
-    if (changed_limit_at_restart) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
-                     "WARNING: Attempt to change ServerLimit or ThreadLimit "
-                     "ignored during restart");
-        changed_limit_at_restart = 0;
-    }
-
     /* Initialize cross-process accept lock */
-    ap_lock_fname = apr_psprintf(_pconf, "%s.%" APR_PID_T_FMT,
-                                 ap_server_root_relative(_pconf, ap_lock_fname),
-                                 ap_my_pid);
-
-    rv = apr_proc_mutex_create(&accept_mutex, ap_lock_fname,
-                               ap_accept_lock_mech, _pconf);
+    rv = ap_proc_mutex_create(&accept_mutex, NULL, AP_ACCEPT_MUTEX_TYPE, NULL,
+                              s, _pconf, 0);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
-                     "Couldn't create accept lock");
         mpm_state = AP_MPMQ_STOPPING;
-        return 1;
-    }
-
-#if APR_USE_SYSVSEM_SERIALIZE
-    if (ap_accept_lock_mech == APR_LOCK_DEFAULT ||
-        ap_accept_lock_mech == APR_LOCK_SYSVSEM) {
-#else
-    if (ap_accept_lock_mech == APR_LOCK_SYSVSEM) {
-#endif
-        rv = unixd_set_proc_mutex_perms(accept_mutex);
-        if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
-                         "Couldn't set permissions on cross-process lock; "
-                         "check User and Group directives");
-            mpm_state = AP_MPMQ_STOPPING;
-            return 1;
-        }
+        return DONE;
     }
 
     if (!is_graceful) {
         if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
             mpm_state = AP_MPMQ_STOPPING;
-            return 1;
+            return DONE;
         }
         /* fix the generation number in the global score; we just got a new,
          * cleared scoreboard
          */
-        ap_scoreboard_image->global->running_generation = ap_my_generation;
+        ap_scoreboard_image->global->running_generation = my_generation;
     }
 
     set_signals();
     /* Don't thrash... */
-    if (max_spare_threads < min_spare_threads + ap_threads_per_child)
-        max_spare_threads = min_spare_threads + ap_threads_per_child;
+    if (max_spare_threads < min_spare_threads + threads_per_child)
+        max_spare_threads = min_spare_threads + threads_per_child;
 
     /* If we're doing a graceful_restart then we're going to see a lot
      * of children exiting immediately when we get into the main loop
      * below (because we just sent them AP_SIG_GRACEFUL).  This happens pretty
-     * rapidly... and for each one that exits we'll start a new one until
-     * we reach at least daemons_min_free.  But we may be permitted to
-     * start more than that, so we'll just keep track of how many we're
+     * rapidly... and for each one that exits we may start a new one, until
+     * there are at least min_spare_threads idle threads, counting across
+     * all children.  But we may be permitted to start more children than
+     * that, so we'll just keep track of how many we're
      * supposed to start up without the 1 second penalty between each fork.
      */
     remaining_children_to_start = ap_daemons_to_start;
     if (remaining_children_to_start > ap_daemons_limit) {
         remaining_children_to_start = ap_daemons_limit;
     }
