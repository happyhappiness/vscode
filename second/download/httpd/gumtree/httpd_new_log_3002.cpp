ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "auth_ldap authorize attribute: authorization denied for "
                  "user %s to %s",
                  r->user, r->uri);