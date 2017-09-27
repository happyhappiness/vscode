                                                      * connections in K-A or lingering
                                                      * close?
                                                      */
                                pchild, APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
     }
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(03103)
                      "apr_pollset_create with Thread Safety failed.");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02471)
                  "start_threads: Using %s", apr_pollset_method_name(event_pollset));
