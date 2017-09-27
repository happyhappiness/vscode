ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "mod_rewrite: can't access text RewriteMap "
                                  "file %s", s->checkfile);