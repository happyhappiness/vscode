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
    else if (*conf->rewritelogfile != '\0') {
        fname = ap_server_root_relative(p, conf->rewritelogfile);
        if (!fname) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s, 
                         "mod_rewrite: Invalid RewriteLog "
                         "path %s", conf->rewritelogfile);
            exit(1);
        }
        if ((rc = apr_file_open(&conf->rewritelogfp, fname, 
                                rewritelog_flags, rewritelog_mode, p))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s, 
                         "mod_rewrite: could not open RewriteLog "
                         "file %s", fname);
            exit(1);
        }
        apr_file_inherit_set(conf->rewritelogfp);
    }
    return;
}

static void rewritelog(request_rec *r, int level, const char *text, ...)
{
