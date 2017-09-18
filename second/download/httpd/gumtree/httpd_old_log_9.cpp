r(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                          "user %s not in right group: %s",
                          user, r->filename);