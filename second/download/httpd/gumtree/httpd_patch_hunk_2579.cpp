     apr_time_t now;
     char *path = apr_pstrcat(p, ctx->storage_path, ".tmp.XXXXXX", NULL);
     /* TODO: Update stats file (!) */
     rv = apr_file_mktemp(&fp, path, APR_CREATE | APR_WRITE, p);
 
     if (rv) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                     "Heartmonitor: Unable to open tmp file: %s", path);
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02081)
+                     "Unable to open tmp file: %s", path);
         return rv;
     }
 
     now = apr_time_now();
     for (hi = apr_hash_first(p, ctx->servers);
          hi != NULL; hi = apr_hash_next(hi)) {
