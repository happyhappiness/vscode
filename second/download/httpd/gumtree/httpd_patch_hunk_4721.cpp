 {
     apr_status_t rv;
     const char *dbd_hash = NULL;
     apr_dbd_prepared_t *statement;
     apr_dbd_results_t *res = NULL;
     apr_dbd_row_t *row = NULL;
+    int ret;
 
     authn_dbd_conf *conf = ap_get_module_config(r->per_dir_config,
                                                 &authn_dbd_module);
     ap_dbd_t *dbd = authn_dbd_acquire_fn(r);
     if (dbd == NULL) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01658)
