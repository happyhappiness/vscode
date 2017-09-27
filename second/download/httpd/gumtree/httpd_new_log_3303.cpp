ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01707)
                  "auth_ldap authorize user: authorization denied for "
                  "user %s to %s",
                  r->user, r->uri);