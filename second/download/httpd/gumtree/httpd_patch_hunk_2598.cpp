     rv = apr_reslist_create(&group->reslist,
                             cfg->nmin, cfg->nkeep, cfg->nmax,
                             apr_time_from_sec(cfg->exptime),
                             dbd_construct, dbd_destruct, group,
                             group->pool);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
-                     "DBD: failed to initialise");
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00633)
+                     "failed to initialise");
         return rv;
     }
 
     apr_pool_cleanup_register(group->pool, group, dbd_destroy,
                               apr_pool_cleanup_null);
 
