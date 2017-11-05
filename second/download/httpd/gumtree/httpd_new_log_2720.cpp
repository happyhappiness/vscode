ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01695)
                      "auth_ldap authenticate: "
                      "user %s authentication failed; URI %s [%s][%s]",
                      user, r->uri, ldc->reason, ldap_err2string(result));