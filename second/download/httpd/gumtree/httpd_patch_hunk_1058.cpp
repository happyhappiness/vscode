         /* Return a once-only connection */
         rv = dbd_construct(&rec, svr, s->process->pool);
         return (rv == APR_SUCCESS) ? arec : NULL;
     }
 
     if (!svr->dbpool) {
-        if (dbd_setup(s->process->pool, s) != APR_SUCCESS) {
+        if (dbd_setup_lock(pool, s) != APR_SUCCESS) {
             return NULL;
         }
     }
-    if (apr_reslist_acquire(svr->dbpool, &rec) != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, pool,
+    rv = apr_reslist_acquire(svr->dbpool, &rec);
+    if (rv != APR_SUCCESS) {
+        ap_log_perror(APLOG_MARK, APLOG_ERR, rv, pool,
                       "Failed to acquire DBD connection from pool!");
         return NULL;
     }
     rv = apr_dbd_check_conn(arec->driver, pool, arec->handle);
     if ((rv != APR_SUCCESS) && (rv != APR_ENOTIMPL)) {
         errmsg = apr_dbd_error(arec->driver, arec->handle, rv);
         if (!errmsg) {
             errmsg = "(unknown)";
         }
-        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, pool,
+        ap_log_perror(APLOG_MARK, APLOG_ERR, rv, pool,
                       "DBD[%s] Error: %s", svr->name, errmsg );
         apr_reslist_invalidate(svr->dbpool, rec);
         return NULL;
     }
     return arec;
 }
 #else
-AP_DECLARE(ap_dbd_t*) ap_dbd_open(apr_pool_t *pool, server_rec *s)
+DBD_DECLARE_NONSTD(ap_dbd_t*) ap_dbd_open(apr_pool_t *pool, server_rec *s)
 {
     apr_status_t rv = APR_SUCCESS;
     const char *errmsg;
     void *rec = NULL;
     svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
 
