         ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                      "creation of the timeout mutex failed.");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     /* Create the main pollset */
-    rv = apr_pollset_create(&event_pollset,
-                            threads_per_child, /* XXX don't we need more, to handle
+    for (i = 0; i < sizeof(good_methods) / sizeof(void*); i++) {
+        rv = apr_pollset_create_ex(&event_pollset,
+                            threads_per_child*2, /* XXX don't we need more, to handle
                                                 * connections in K-A or lingering
                                                 * close?
                                                 */
-                            pchild, APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
+                            pchild, APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY | APR_POLLSET_NODEFAULT,
+                            good_methods[i]);
+        if (rv == APR_SUCCESS) {
+            break;
+        }
+    }
+    if (rv != APR_SUCCESS) {
+        rv = apr_pollset_create(&event_pollset,
+                               threads_per_child*2, /* XXX don't we need more, to handle
+                                                     * connections in K-A or lingering
+                                                     * close?
+                                                     */
+                               pchild, APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
+    }
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                      "apr_pollset_create with Thread Safety failed.");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02471)
+                 "start_threads: Using %s", apr_pollset_method_name(event_pollset));
     worker_sockets = apr_pcalloc(pchild, threads_per_child
                                  * sizeof(apr_socket_t *));
 
     loops = prev_threads_created = 0;
     while (1) {
         /* threads_per_child does not include the listener thread */
