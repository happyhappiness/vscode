 
     if (mctx->stapling_force_url)
         ocspuri = mctx->stapling_force_url;
     else
         ocspuri = cinf->uri;
 
+    if (!ocspuri) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02621)
+                     "stapling_renew_response: no uri for responder");
+        rv = FALSE;
+        goto done;
+    }
+
     /* Create a temporary pool to constrain memory use */
     apr_pool_create(&vpool, conn->pool);
 
     ok = apr_uri_parse(vpool, ocspuri, &uri);
     if (ok != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01939)
