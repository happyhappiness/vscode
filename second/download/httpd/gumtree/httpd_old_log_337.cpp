ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
                                 "mod_rewrite: can't access text RewriteMap "
                                 "file %s", s->checkfile);