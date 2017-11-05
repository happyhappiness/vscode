static int open_rewritelog(server_rec *s, apr_pool_t *p)
{
    rewrite_server_conf *conf;
    const char *fname;

    conf = ap_get_module_config(s->module_config, &rewrite_module);

    /* - no logfile configured
     * - logfilename empty
     * - virtual log shared w/ main server
     */
    if (!conf->rewritelogfile || !*conf->rewritelogfile || conf->rewritelogfp) {
        return 1;
    }

    if (*conf->rewritelogfile == '|') {
        piped_log *pl;

        fname = ap_server_root_relative(p, conf->rewritelogfile+1);
        if (!fname) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                         "mod_rewrite: Invalid RewriteLog "
                         "path %s", conf->rewritelogfile+1);
            return 0;
        }

        if ((pl = ap_open_piped_log(p, fname)) == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "mod_rewrite: could not open reliable pipe "
                         "to RewriteLog filter %s", fname);
            return 0;
        }
        conf->rewritelogfp = ap_piped_log_write_fd(pl);
    }
    else {
        apr_status_t rc;

        fname = ap_server_root_relative(p, conf->rewritelogfile);
        if (!fname) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                         "mod_rewrite: Invalid RewriteLog "
                         "path %s", conf->rewritelogfile);
            return 0;
        }

        if ((rc = apr_file_open(&conf->rewritelogfp, fname,
                                REWRITELOG_FLAGS, REWRITELOG_MODE, p))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                         "mod_rewrite: could not open RewriteLog "
                         "file %s", fname);
            return 0;
        }
    }

    return 1;
}