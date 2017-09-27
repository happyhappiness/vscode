  * us all the error-handling in one place.
  */
 static apr_status_t dbd_construct(void **db, void *params, apr_pool_t *pool)
 {
     svr_cfg *svr = (svr_cfg*) params;
     ap_dbd_t *rec = apr_pcalloc(pool, sizeof(ap_dbd_t));
-    apr_status_t rv = apr_dbd_get_driver(pool, svr->name, &rec->driver);
+    apr_status_t rv;
+
+    /* this pool is mostly so dbd_close can destroy the prepared stmts */
+    rv = apr_pool_create(&rec->pool, pool);
+    if (rv != APR_SUCCESS) {
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
+                      "DBD: Failed to create memory pool");
+    }
 
-/* Error-checking get_driver isn't necessary now (because it's done at
- * config-time).  But in case that changes in future ...
+/* The driver is loaded at config time now, so this just checks a hash.
+ * If that changes, the driver DSO could be registered to unload against
+ * our pool, which is probably not what we want.  Error checking isn't
+ * necessary now, but in case that changes in the future ...
  */
+    rv = apr_dbd_get_driver(rec->pool, svr->name, &rec->driver);
     switch (rv) {
     case APR_ENOTIMPL:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                       "DBD: driver for %s not available", svr->name);
         return rv;
     case APR_EDSOOPEN:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                       "DBD: can't find driver for %s", svr->name);
         return rv;
     case APR_ESYMNOTFOUND:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                       "DBD: driver for %s is invalid or corrupted", svr->name);
         return rv;
     default:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                       "DBD: mod_dbd not compatible with apr in get_driver");
         return rv;
     case APR_SUCCESS:
         break;
     }
 
-    rv = apr_dbd_open(rec->driver, pool, svr->params, &rec->handle);
+    rv = apr_dbd_open(rec->driver, rec->pool, svr->params, &rec->handle);
     switch (rv) {
     case APR_EGENERAL:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
-                      "DBD: Can't connect to %s[%s]", svr->name, svr->params);
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
+                      "DBD: Can't connect to %s", svr->name);
         return rv;
     default:
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                       "DBD: mod_dbd not compatible with apr in open");
         return rv;
     case APR_SUCCESS:
         break;
     }
     *db = rec;
-    rv = dbd_prepared_init(pool, svr, rec);
+    rv = dbd_prepared_init(rec->pool, svr, rec);
+    if (rv != APR_SUCCESS) {
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
+                      "DBD: failed to initialise prepared SQL statements");
+    }
+    return rv;
+}
+static apr_status_t dbd_close(void *CONN)
+{
+    ap_dbd_t *conn = CONN;
+    apr_status_t rv = apr_dbd_close(conn->driver, conn->handle);
+    apr_pool_destroy(conn->pool);
     return rv;
 }
 #if APR_HAS_THREADS
 static apr_status_t dbd_destruct(void *sql, void *params, apr_pool_t *pool)
 {
-    ap_dbd_t *rec = sql;
-    return apr_dbd_close(rec->driver, rec->handle);
+    return dbd_close(sql);
 }
 
-static apr_status_t dbd_setup(apr_pool_t *pool, server_rec *s)
+static apr_status_t dbd_setup(apr_pool_t *pool, svr_cfg *svr)
 {
-    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
-    apr_status_t rv = apr_reslist_create(&svr->dbpool, svr->nmin, svr->nkeep,
-                                         svr->nmax, svr->exptime,
-                                         dbd_construct, dbd_destruct,
-                                         svr, pool);
+    apr_status_t rv;
+
+    /* create a pool just for the reslist from a process-lifetime pool;
+     * that pool (s->process->pool in the dbd_setup_lock case,
+     * whatever was passed to ap_run_child_init in the dbd_setup_init case)
+     * will be shared with other threads doing other non-mod_dbd things
+     * so we can't use it for the reslist directly
+     */
+    rv = apr_pool_create(&svr->pool, pool);
+    if (rv != APR_SUCCESS) {
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
+                      "DBD: Failed to create reslist memory pool");
+        return rv;
+    }
+
+    rv = apr_reslist_create(&svr->dbpool, svr->nmin, svr->nkeep, svr->nmax,
+                            apr_time_from_sec(svr->exptime),
+                            dbd_construct, dbd_destruct, svr, svr->pool);
     if (rv == APR_SUCCESS) {
-        apr_pool_cleanup_register(pool, svr->dbpool,
+        apr_pool_cleanup_register(svr->pool, svr->dbpool,
                                   (void*)apr_reslist_destroy,
                                   apr_pool_cleanup_null);
     }
     else {
-        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
-                      "DBD Pool: failed to initialise");
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, svr->pool,
+                      "DBD: failed to initialise");
+        apr_pool_destroy(svr->pool);
+        svr->pool = NULL;
     }
+
     return rv;
 }
+static apr_status_t dbd_setup_init(apr_pool_t *pool, server_rec *s)
+{
+    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
+    apr_status_t rv;
+
+    if (!svr->persist) {
+        return APR_SUCCESS;
+    }
+
+    rv = dbd_setup(pool, svr);
+    if (rv == APR_SUCCESS) {
+        return rv;
+    }
+
+    /* we failed, so create a mutex so that subsequent competing callers
+     * to ap_dbd_open can serialize themselves while they retry
+     */
+    rv = apr_thread_mutex_create(&svr->mutex, APR_THREAD_MUTEX_DEFAULT, pool);
+    if (rv != APR_SUCCESS) {
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
+                      "DBD: Failed to create thread mutex");
+    }
+    return rv;
+}
+static apr_status_t dbd_setup_lock(apr_pool_t *pool, server_rec *s)
+{
+    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
+    apr_status_t rv, rv2 = APR_SUCCESS;
 
+    /* several threads could be here at the same time, all trying to
+     * initialize the reslist because dbd_setup_init failed to do so
+     */
+    if (!svr->mutex) {
+        /* we already logged an error when the mutex couldn't be created */
+        return APR_EGENERAL;
+    }
+
+    rv = apr_thread_mutex_lock(svr->mutex);
+    if (rv != APR_SUCCESS) {
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
+                      "DBD: Failed to acquire thread mutex");
+        return rv;
+    }
+
+    if (!svr->dbpool) {
+        rv2 = dbd_setup(s->process->pool, svr);
+    }
+
+    rv = apr_thread_mutex_unlock(svr->mutex);
+    if (rv != APR_SUCCESS) {
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, pool,
+                      "DBD: Failed to release thread mutex");
+        if (rv2 == APR_SUCCESS) {
+            rv2 = rv;
+        }
+    }
+    return rv2;
+}
 #endif
 
 
 /* Functions we export for modules to use:
         - open acquires a connection from the pool (opens one if necessary)
         - close releases it back in to the pool
 */
-AP_DECLARE(void) ap_dbd_close(server_rec *s, ap_dbd_t *sql)
+DBD_DECLARE_NONSTD(void) ap_dbd_close(server_rec *s, ap_dbd_t *sql)
 {
     svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
     if (!svr->persist) {
-        apr_dbd_close(sql->driver, sql->handle);
+        dbd_close((void*) sql);
     }
 #if APR_HAS_THREADS
     else {
         apr_reslist_release(svr->dbpool, sql);
     }
 #endif
 }
-static apr_status_t dbd_close(void *CONN)
-{
-    ap_dbd_t *conn = CONN;
-    return apr_dbd_close(conn->driver, conn->handle);
-}
 #define arec ((ap_dbd_t*)rec)
 #if APR_HAS_THREADS
-AP_DECLARE(ap_dbd_t*) ap_dbd_open(apr_pool_t *pool, server_rec *s)
+DBD_DECLARE_NONSTD(ap_dbd_t*) ap_dbd_open(apr_pool_t *pool, server_rec *s)
 {
     void *rec = NULL;
     svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
     apr_status_t rv = APR_SUCCESS;
     const char *errmsg;
 
