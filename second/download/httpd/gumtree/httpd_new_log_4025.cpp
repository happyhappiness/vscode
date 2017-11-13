ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00670)
                     "Options FollowSymLinks and SymLinksIfOwnerMatch are both off, "
                     "so the RewriteRule directive is also forbidden "
                     "due to its similar ability to circumvent directory restrictions : "
                     "%s", r->filename);