         r->header_only = 1;
         apr_table_set(r->headers_out, "Proxy-agent: %s", ap_get_server_banner());
         ap_rflush(r);
 #endif
     }
 
-    ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
-                 "proxy: CONNECT: setting up poll()");
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "setting up poll()");
 
     /*
      * Step Four: Handle Data Transfer
      *
      * Handle two way transfer of data over the socket (this is a tunnel).
      */
