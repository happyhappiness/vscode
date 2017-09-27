                                      getpid(), t, ldc->reason, ldap_err2string(result));
                    }
                }
            }
        }
        else if (strcmp(w, "ldap-attribute") == 0) {
            if (req->dn == NULL || strlen(req->dn) == 0) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                              "require ldap-attribute: user's DN has not been defined; failing authorisation",
                              getpid());
                return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
