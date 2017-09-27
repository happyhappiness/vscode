         worker->is_address_reusable = 0;
     }
     else {
         worker->is_address_reusable = 1;
     }
 
+    if (worker->cp == NULL)
+        init_conn_pool(p, worker);
+    if (worker->cp == NULL) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+            "can not create connection pool");
+        return APR_EGENERAL;
+    } 
+
 #if APR_HAS_THREADS
+    if (worker->mutex == NULL) {
+        rv = apr_thread_mutex_create(&(worker->mutex), APR_THREAD_MUTEX_DEFAULT, p);
+        if (rv != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                "can not create thread mutex");
+            return rv;
+        }
+    }
+
     ap_mpm_query(AP_MPMQ_MAX_THREADS, &mpm_threads);
     if (mpm_threads > 1) {
         /* Set hard max to no more then mpm_threads */
         if (worker->hmax == 0 || worker->hmax > mpm_threads) {
             worker->hmax = mpm_threads;
         }
