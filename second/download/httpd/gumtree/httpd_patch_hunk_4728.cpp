 
     /* for the DBM we need the data file */
     if (ctx->data_file == NULL) {
         const char *path = apr_pstrcat(p, DEFAULT_DBM_PREFIX, namespace,
                                        NULL);
 
-        ctx->data_file = ap_server_root_relative(p, path);
+        ctx->data_file = ap_runtime_dir_relative(p, path);
 
         if (ctx->data_file == NULL) {
             ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00803)
                          "could not use default path '%s' for DBM socache",
                          path);
             return APR_EINVAL;
