         apr_size_t len;
         apr_status_t rv;
         apr_bucket *e = APR_BRIGADE_FIRST(bb);
 
         rv = apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
         if (rv == APR_EOF || (rv == APR_SUCCESS && len == 0)) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01984)
                           "OCSP response: got EOF");
             break;
         }
         if (rv != APR_SUCCESS) {
-            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01985)
                           "error reading response from OCSP server");
             return NULL;
         }
         count += len;
         if (count > MAX_CONTENT) {
-            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01986)
                           "OCSP response size exceeds %u byte limit",
                           MAX_CONTENT);
             return NULL;
         }
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
-                      "OCSP response: got %" APR_SIZE_T_FMT 
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01987)
+                      "OCSP response: got %" APR_SIZE_T_FMT
                       " bytes, %" APR_SIZE_T_FMT " total", len, count);
 
         BIO_write(bio, data, (int)len);
         apr_bucket_delete(e);
     }
 
