ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s, 
                         "mod_rewrite: could not open reliable pipe "
                         "to RewriteLog filter %s", conf->rewritelogfile+1);