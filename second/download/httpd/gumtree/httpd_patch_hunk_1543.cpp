 {
     dbd_group_t *group = params;
     dbd_cfg_t *cfg = group->cfg;
     apr_pool_t *rec_pool, *prepared_pool;
     ap_dbd_t *rec;
     apr_status_t rv;
+    const char *err = "";
 
     rv = apr_pool_create(&rec_pool, pool);
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, rv, cfg->server,
                      "DBD: Failed to create memory pool");
         return rv;
