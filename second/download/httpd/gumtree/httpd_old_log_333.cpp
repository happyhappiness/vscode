ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                     "Options FollowSymLinks or SymLinksIfOwnerMatch is off "
                     "which implies that RewriteRule directive is forbidden: "
                     "%s", r->filename);