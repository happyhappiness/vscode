r(APLOG_MARK, APLOG_ERR, 0, r,
                  "access to %s failed, reason: ip address list does not meet "
                  "'require'ments for user '%s' to be allowed access",
                  r->uri, r->user);