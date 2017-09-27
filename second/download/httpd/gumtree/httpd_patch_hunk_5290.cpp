         }
         if (len <= 0) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(01102)
                           "error reading status line from remote "
                           "server %s:%d", backend->hostname, backend->port);
             if (APR_STATUS_IS_TIMEUP(rc)) {
-                apr_table_set(r->notes, "proxy_timedout", "1");
+                apr_table_setn(r->notes, "proxy_timedout", "1");
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01103) "read timeout");
                 if (do_100_continue) {
                     return ap_proxyerror(r, HTTP_SERVICE_UNAVAILABLE, "Timeout on 100-Continue");
                 }
             }
             /*
