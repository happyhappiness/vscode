                                      getpid(), t, ldc->reason, ldap_err2string(result));
                    }
                }
            }
        }
        else if (strcmp(w, "ldap-attribute") == 0) {
            while (t[0]) {
                w = ap_getword(r->pool, &t, '=');
                value = ap_getword_conf(r->pool, &t);

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
                              "[%d] auth_ldap authorise: checking attribute"
