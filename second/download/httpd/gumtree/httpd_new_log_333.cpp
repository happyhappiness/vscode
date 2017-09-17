ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                     "Options FollowSymLinks or SymLinksIfOwnerMatch is off "
                     "which implies that RewriteRule directive is forbidden: "
                     "%s", r->filename);