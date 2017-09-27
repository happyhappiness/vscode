             }
 
             if (ap_some_auth_required(r)) {
                 if (((access_status = ap_run_check_user_id(r)) != 0)
                     || !ap_auth_type(r)) {
                     return decl_die(access_status, ap_auth_type(r)
-                                  ? "check user.  No user file?"
+                                  ? "check user.  Check your authn provider!"
                                   : "perform authentication. AuthType not set!",
                                   r);
                 }
 
                 if (((access_status = ap_run_auth_checker(r)) != 0)
                     || !ap_auth_type(r)) {
                     return decl_die(access_status, ap_auth_type(r)
-                                  ? "check access.  No groups file?"
+                                  ? "check access.  Check your 'Require' directive"
                                   : "perform authentication. AuthType not set!",
                                    r);
                 }
             }
             break;
 
