 
     rp = ap_proxy_make_fake_req(origin, r);
     /* In case anyone needs to know, this is a fake request that is really a
      * response.
      */
     rp->proxyreq = PROXYREQ_RESPONSE;
+    tmp_bb = apr_brigade_create(p, c->bucket_alloc);
     do {
+        apr_status_t rc;
+
         apr_brigade_cleanup(bb);
 
-        len = ap_getline(buffer, sizeof(buffer), rp, 0);
+        rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), rp, 0, &len);
         if (len == 0) {
             /* handle one potential stray CRLF */
-            len = ap_getline(buffer, sizeof(buffer), rp, 0);
+            rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), rp, 0, &len);
         }
         if (len <= 0) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                           "proxy: error reading status line from remote "
                           "server %s", backend->hostname);
             return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                                  "Error reading from remote server");
         }
         /* XXX: Is this a real headers length send from remote? */
