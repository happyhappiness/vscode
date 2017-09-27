         /* shouldn't be possible */
         rv = HTTP_INTERNAL_SERVER_ERROR ;
         break;
     }
 
     if (rv != OK) {
-        /* apr_errno value has been logged in lower level method */
+        /* apr_status_t value has been logged in lower level method */
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                      "proxy: pass request body failed to %pI (%s)"
                      " from %s (%s)",
                      p_conn->addr,
                      p_conn->hostname ? p_conn->hostname: "",
                      c->remote_ip,
