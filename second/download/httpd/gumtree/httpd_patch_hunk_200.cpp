     return APR_SUCCESS;
 }
 
 
 static int init_config_log(apr_pool_t *pc, apr_pool_t *p, apr_pool_t *pt, server_rec *s)
 {
-    /* First, do "physical" server, which gets default log fd and format
+    int res;
+
+    /* First init the buffered logs array, which is needed when opening the logs. */
+    if (buffered_logs) {
+        all_buffered_logs = apr_array_make(p, 5, sizeof(buffered_log *));
+    }
+
+    /* Next, do "physical" server, which gets default log fd and format
      * for the virtual servers, if they don't override...
      */
-    int res = open_multi_logs(s, p);
+    res = open_multi_logs(s, p);
 
     /* Then, virtual servers */
 
     for (s = s->next; (res == OK) && s; s = s->next) {
         res = open_multi_logs(s, p);
     }
 
     return res;
 }
 
 static void init_child(apr_pool_t *p, server_rec *s)
 {
-	/* Now register the last buffer flush with the cleanup engine */
-    if (buffered_logs)
-	    apr_pool_cleanup_register(p, s, flush_all_logs, flush_all_logs);
+    int mpm_threads;
+
+    ap_mpm_query(AP_MPMQ_MAX_THREADS, &mpm_threads);
+
+    /* Now register the last buffer flush with the cleanup engine */
+    if (buffered_logs) {
+        int i;
+        buffered_log **array = (buffered_log **)all_buffered_logs->elts;
+        
+        apr_pool_cleanup_register(p, s, flush_all_logs, flush_all_logs);
+
+        for (i = 0; i < all_buffered_logs->nelts; i++) {
+            buffered_log *this = array[i];
+            
+#if APR_HAS_THREADS
+            if (mpm_threads > 1) {
+                apr_status_t rv;
+
+                this->mutex.type = apr_anylock_threadmutex;
+                rv = apr_thread_mutex_create(&this->mutex.lock.tm,
+                                             APR_THREAD_MUTEX_DEFAULT,
+                                             p);
+                if (rv != APR_SUCCESS) {
+                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
+                                 "could not initialize buffered log mutex, "
+                                 "transfer log may become corrupted");
+                    this->mutex.type = apr_anylock_none;
+                }
+            }
+            else
+#endif
+            {
+                this->mutex.type = apr_anylock_none;
+            }
+        }
+    }
 }
 
 static void ap_register_log_handler(apr_pool_t *p, char *tag, 
                                     ap_log_handler_fn_t *handler, int def)
 {
     ap_log_handler *log_struct = apr_palloc(p, sizeof(*log_struct));
