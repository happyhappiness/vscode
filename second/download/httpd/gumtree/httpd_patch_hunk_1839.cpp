      * we can have cleanups occur when the child exits.
      */
     apr_allocator_create(&allocator);
     apr_allocator_max_free_set(allocator, ap_max_mem_free);
     apr_pool_create_ex(&pchild, pconf, NULL, allocator);
     apr_allocator_owner_set(allocator, pchild);
+    apr_pool_tag(pchild, "pchild");
 
+#if APR_HAS_THREADS
+    osthd = apr_os_thread_current();
+    apr_os_thread_put(&thd, &osthd, pchild);
+#endif
+    
     apr_pool_create(&ptrans, pchild);
     apr_pool_tag(ptrans, "transaction");
 
     /* needs to be done before we switch UIDs so we have permissions */
     ap_reopen_scoreboard(pchild, NULL, 0);
-    status = apr_proc_mutex_child_init(&accept_mutex, ap_lock_fname, pchild);
+    lockfile = apr_proc_mutex_lockfile(accept_mutex);
+    status = apr_proc_mutex_child_init(&accept_mutex,
+                                       lockfile,
+                                       pchild);
     if (status != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                      "Couldn't initialize cross-process lock in child "
-                     "(%s) (%d)", ap_lock_fname, ap_accept_lock_mech);
+                     "(%s) (%s)",
+                     lockfile ? lockfile : "none",
+                     apr_proc_mutex_name(accept_mutex));
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
-    if (unixd_setup_child()) {
+    if (ap_run_drop_privileges(pchild, ap_server_conf)) {
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     ap_run_child_init(pchild, ap_server_conf);
 
     ap_create_sb_handle(&sbh, pchild, my_child_num, 0);
