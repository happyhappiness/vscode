     while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
         if (!strcmp(r->user, w)) {
             return AUTHZ_GRANTED;
         }
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01663)
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01663)
                   "access to %s failed, reason: user '%s' does not meet "
                   "'require'ments for user to be allowed access",
                   r->uri, r->user);
 
     return AUTHZ_DENIED;
 }
