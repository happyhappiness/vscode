                     "Cannot parse vary entry for key: %s", key);
             apr_pool_destroy(sobj->pool);
             sobj->pool = NULL;
             return DECLINED;
         }
 
-        nkey = regen_key(r->pool, r->headers_in, varray, key);
+        nkey = regen_key(r->pool, r->headers_in, varray, key, &len);
 
         /* attempt to retrieve the cached entry */
         if (socache_mutex) {
             apr_status_t status = apr_global_mutex_lock(socache_mutex);
             if (status != APR_SUCCESS) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02355)
