 {
     void *rec = NULL;
     svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
     apr_status_t rv = APR_SUCCESS;
     const char *errmsg;
 
+    /* If nothing is configured, we shouldn't be here */
+    if (svr->name == no_dbdriver) {
+        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, pool, "DBD: not configured");
+        return NULL;
+    }
+
     if (!svr->persist) {
         /* Return a once-only connection */
         rv = dbd_construct(&rec, svr, s->process->pool);
         return (rv == APR_SUCCESS) ? arec : NULL;
     }
 
