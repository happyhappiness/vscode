 
             if (cur->desc.s == sock) {
                 pollevent = cur->rtnevents;
                 if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
                     ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02446)
                                   "sock was readable");
-                    done |= proxy_wstunnel_transfer(r, backconn, c, bb,
-                                                    "sock", NULL) != APR_SUCCESS;
+                    done |= ap_proxy_transfer_between_connections(r, backconn,
+                                                                  c,
+                                                                  header_brigade,
+                                                                  bb, "sock",
+                                                                  NULL,
+                                                                  AP_IOBUFSIZE,
+                                                                  0)
+                                                                 != APR_SUCCESS;
                 }
                 else if (pollevent & APR_POLLERR) {
                     ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02447)
                             "error on backconn");
                     backconn->aborted = 1;
                     done = 1;
