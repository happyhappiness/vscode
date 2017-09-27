                 if ((access_status = ap_run_check_user_id(r)) != OK) {
                     return decl_die(access_status, "check user", r);
                 }
                 if (r->user == NULL) {
                     /* don't let buggy authn module crash us in authz */
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00027)
-                                  "Buggy authn provider failed to set user for %s",
+                                  "No authentication done but request not "
+                                  "allowed without authentication for %s. "
+                                  "Authentication not configured?",
                                   r->uri);
                     access_status = HTTP_INTERNAL_SERVER_ERROR;
                     return decl_die(access_status, "check user", r);
                 }
                 if ((access_status = ap_run_auth_checker(r)) != OK) {
                     return decl_die(access_status, "check authorization", r);
