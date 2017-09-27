             /* handle one potential stray CRLF */
             rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), rp, 0, &len);
         }
         if (len <= 0) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                           "proxy: error reading status line from remote "
-                          "server %s", backend->hostname);
-            if (rc == APR_TIMEUP) {
+                          "server %s:%d", backend->hostname, backend->port);
+            if (APR_STATUS_IS_TIMEUP(rc)) {
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                               "proxy: read timeout");
             }
             /*
              * If we are a reverse proxy request shutdown the connection
              * WITHOUT ANY response to trigger a retry by the client
