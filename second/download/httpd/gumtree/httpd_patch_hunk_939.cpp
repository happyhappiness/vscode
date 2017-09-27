         }
 
         ap_log_error(APLOG_MARK, log_level, rv, ap_server_conf,
                      "connect to listener on %pI", ap_listeners->bind_addr);
     }
 
+    /* Create the request string. We include a User-Agent so that
+     * adminstrators can track down the cause of the odd-looking
+     * requests in their logs.
+     */
+    srequest = apr_pstrcat(p, "GET / HTTP/1.0\r\nUser-Agent: ",
+                           ap_get_server_version(),
+                           " (internal dummy connection)\r\n\r\n", NULL);
+
+    /* Since some operating systems support buffering of data or entire
+     * requests in the kernel, we send a simple request, to make sure
+     * the server pops out of a blocking accept().
+     */
+    /* XXX: This is HTTP specific. We should look at the Protocol for each
+     * listener, and send the correct type of request to trigger any Accept
+     * Filters.
+     */
+    len = strlen(srequest);
+    apr_socket_send(sock, srequest, &len);
     apr_socket_close(sock);
     apr_pool_destroy(p);
 
     return rv;
 }
 
