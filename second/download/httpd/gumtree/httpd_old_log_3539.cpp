ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "mod_rewrite: can't access DBM RewriteMap "
                              "file %s", s->checkfile2);