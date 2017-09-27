         ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(03102)
                      "creation of the timeout mutex failed.");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     /* Create the main pollset */
-    for (i = 0; i < sizeof(good_methods) / sizeof(void*); i++) {
+    for (i = 0; i < sizeof(good_methods) / sizeof(good_methods[0]); i++) {
         rv = apr_pollset_create_ex(&event_pollset,
                             threads_per_child*2, /* XXX don't we need more, to handle
                                                 * connections in K-A or lingering
                                                 * close?
                                                 */
                             pchild, APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY | APR_POLLSET_NODEFAULT,
