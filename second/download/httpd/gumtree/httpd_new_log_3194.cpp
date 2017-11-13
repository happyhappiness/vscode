ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01694)
                      "auth_ldap authenticate: user %s authentication failed; "
                      "URI %s [%s][%s] (not authoritative)",
                      user, r->uri, ldc->reason, ldap_err2string(result));