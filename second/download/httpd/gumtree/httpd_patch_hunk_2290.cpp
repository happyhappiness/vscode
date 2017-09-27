 
         if (got_ip && apr_ipsubnet_test(ip, r->connection->remote_addr)) {
             return AUTHZ_GRANTED;
         }
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                   "access to %s failed, reason: ip address list does not meet "
                   "'require'ments for user '%s' to be allowed access",
                   r->uri, r->user);
 
     return AUTHZ_DENIED;
 }
