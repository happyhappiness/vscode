         method_restricted = 1;
 
         t = reqs[x].requirement;
         w = ap_getword_white(r->pool, &t);
 
         if (strcmp(w, "ldap-user") == 0) {
+            required_ldap = 1;
             if (req->dn == NULL || strlen(req->dn) == 0) {
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                               "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                               "require user: user's DN has not been defined; failing authorisation",
                               getpid());
                 return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
