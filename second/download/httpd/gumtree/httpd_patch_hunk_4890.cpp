         if (bytes_spooled + bytes > MAX_MEM_SPOOL) {
             /*
              * LimitRequestBody does not affect Proxy requests (Should it?).
              * Let it take effect if we decide to store the body in a
              * temporary file on disk.
              */
-            if (bytes_spooled + bytes > limit) {
+            if (limit && (bytes_spooled + bytes > limit)) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01088)
                               "Request body is larger than the configured "
                               "limit of %" APR_OFF_T_FMT, limit);
                 return HTTP_REQUEST_ENTITY_TOO_LARGE;
             }
             /* can't spool any more in memory; write latest brigade to disk */
