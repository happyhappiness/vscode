             if (APR_STATUS_IS_EINTR(rv)) {
                 continue;
             }
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02444) "error apr_poll()");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02445)
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02445)
                       "woke from poll(), i=%d", pollcnt);
 
         for (pi = 0; pi < pollcnt; pi++) {
             const apr_pollfd_t *cur = &signalled[pi];
 
             if (cur->desc.s == sock) {
                 pollevent = cur->rtnevents;
                 if (pollevent & APR_POLLIN) {
-                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02446)
+                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02446)
                                   "sock was readable");
                     rv = proxy_wstunnel_transfer(r, backconn, c, bb, "sock");
                     }
                 else if ((pollevent & APR_POLLERR)
                          || (pollevent & APR_POLLHUP)) {
                          rv = APR_EPIPE;
                          ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02447)
                                        "err/hup on backconn");
                 }
+                else { 
+                    rv = APR_EGENERAL;
+                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02605)
+                            "unknown event on backconn %d", pollevent);
+                }
                 if (rv != APR_SUCCESS)
                     client_error = 1;
             }
             else if (cur->desc.s == client_socket) {
                 pollevent = cur->rtnevents;
                 if (pollevent & APR_POLLIN) {
-                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02448)
+                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02448)
                                   "client was readable");
                     rv = proxy_wstunnel_transfer(r, c, backconn, bb, "client");
                 }
+                else if ((pollevent & APR_POLLERR)
+                        || (pollevent & APR_POLLHUP)) {
+                    rv = APR_EPIPE;
+                    c->aborted = 1;
+                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02607)
+                            "err/hup on client conn");
+                }
+                else { 
+                    rv = APR_EGENERAL;
+                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02606)
+                            "unknown event on client conn %d", pollevent);
+                }
             }
             else {
                 rv = APR_EBADF;
                 ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02449)
                               "unknown socket in pollset");
             }
