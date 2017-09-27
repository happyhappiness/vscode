     int complete = 0;
     char buffer[HUGE_STRING_LEN];
     char drain_buffer[HUGE_STRING_LEN];
     forward_info *forward = (forward_info *)backend->forward;
     int len = 0;
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                 "proxy: CONNECT: sending the CONNECT request for %s:%d "
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00948)
+                 "CONNECT: sending the CONNECT request for %s:%d "
                  "to the remote proxy %pI (%s)",
                  forward->target_host, forward->target_port,
                  backend->addr, backend->hostname);
     /* Create the CONNECT request */
     nbytes = apr_snprintf(buffer, sizeof(buffer),
                           "CONNECT %s:%d HTTP/1.0" CRLF,
