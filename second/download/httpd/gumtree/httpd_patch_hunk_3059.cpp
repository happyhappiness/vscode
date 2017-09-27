                     }
                     else if (rv != APR_SUCCESS) {
                         /* In this case, we are in real trouble because
                          * our backend bailed on us. Pass along a 502 error
                          * error bucket
                          */
-                        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
-                                      "proxy: error reading response");
+                        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01110)
+                                      "error reading response");
                         ap_proxy_backend_broke(r, bb);
                         ap_pass_brigade(r->output_filters, bb);
                         backend_broke = 1;
                         backend->close = 1;
                         break;
                     }
