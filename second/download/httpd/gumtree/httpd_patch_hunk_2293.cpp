 static authz_status user_check_authorization(request_rec *r,
                                              const char *require_args)
 {
     const char *t, *w;
 
     if (!r->user) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-            "access to %s failed, reason: no authenticated user", r->uri);
-        return AUTHZ_DENIED;
+        return AUTHZ_DENIED_NO_USER;
     }
 
     t = require_args;
     while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
         if (!strcmp(r->user, w)) {
             return AUTHZ_GRANTED;
