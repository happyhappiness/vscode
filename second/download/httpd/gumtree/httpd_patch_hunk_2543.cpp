     dbmkey.dptr  = (char *)id;
     dbmkey.dsize = idlen;
 
     /* and delete it from the DBM file */
     apr_pool_clear(ctx->pool);
 
-    if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE, 
+    if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
                            DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00810)
                      "Cannot open socache DBM file `%s' for writing "
                      "(delete)",
                      ctx->data_file);
         return rv;
     }
     apr_dbm_delete(dbm, dbmkey);
