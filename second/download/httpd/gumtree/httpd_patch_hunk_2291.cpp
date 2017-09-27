         while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
             if (in_domain(w, remotehost)) {
                 return AUTHZ_GRANTED;
             }
         }
 
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                       "access to %s failed, reason: host name list does not meet "
                       "'require'ments for user '%s' to be allowed access",
                       r->uri, r->user);
     }
 
     return AUTHZ_DENIED;
