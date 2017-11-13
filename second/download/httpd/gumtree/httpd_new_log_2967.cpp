ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "auth_ldap authenticate: user %s authentication failed; "
                      "URI %s [%s][%s] (not authoritative)",
                      user, r->uri, ldc->reason, ldap_err2string(result));