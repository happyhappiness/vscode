                                       ldc->reason, ldap_err2string(result));
                     }
                 }
             }
         }
         else if (strcmp(w, "ldap-filter") == 0) {
-            required_ldap = 1;
             if (req->dn == NULL || strlen(req->dn) == 0) {
                 ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                               "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                               "require ldap-filter: user's DN has not been defined; failing authorisation",
                               getpid());
                 return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
