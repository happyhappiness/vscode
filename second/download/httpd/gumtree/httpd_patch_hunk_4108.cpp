                 pollevent = cur->rtnevents;
                 if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
 #ifdef DEBUGGING
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01025)
                                   "sock was readable");
 #endif
-                    done |= proxy_connect_transfer(r, backconn, c, bb,
-                                                   "sock") != APR_SUCCESS;
+                    done |= ap_proxy_transfer_between_connections(r, backconn,
+                                                                  c, bb_back,
+                                                                  bb_front,
+                                                                  "sock", NULL,
+                                                                  CONN_BLKSZ, 1)
+                                                                 != APR_SUCCESS;
                 }
                 else if (pollevent & APR_POLLERR) {
                     ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(01026)
                                   "err on backconn");
                     backconn->aborted = 1;
                     done = 1;
