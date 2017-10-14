ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                         "mod_rewrite: Invalid RewriteLog "
                         "path %s", conf->rewritelogfile+1);