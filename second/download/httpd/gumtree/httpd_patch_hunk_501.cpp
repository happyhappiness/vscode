         ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                      "set timeout on socket to connect to listener");
         apr_socket_close(sock);
         return rv;
     }
 
-    rv = apr_connect(sock, pod->sa);
+    rv = apr_connect(sock, ap_listeners->bind_addr);
     if (rv != APR_SUCCESS) {
         int log_level = APLOG_WARNING;
 
         if (APR_STATUS_IS_TIMEUP(rv)) {
             /* probably some server processes bailed out already and there
              * is nobody around to call accept and clear out the kernel
              * connection queue; usually this is not worth logging
              */
             log_level = APLOG_DEBUG;
         }
 
         ap_log_error(APLOG_MARK, log_level, rv, ap_server_conf,
-                     "connect to listener");
+                     "connect to listener on %pI", ap_listeners->bind_addr);
     }
 
     apr_socket_close(sock);
     apr_pool_destroy(p);
 
     return rv;
