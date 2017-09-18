    if (conf->rewritelogfp != NULL) {
        return; /* virtual log shared w/ main server */
    }

    if (*conf->rewritelogfile == '|') {
        if ((pl = ap_open_piped_log(p, conf->rewritelogfile+1)) == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, 
                         "mod_rewrite: could not open reliable pipe "
                         "to RewriteLog filter %s", conf->rewritelogfile+1);
            exit(1);
        }
        conf->rewritelogfp = ap_piped_log_write_fd(pl);
    }
