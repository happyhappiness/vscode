 * |              rewriting logfile support
 * |                                                       |
 * +-------------------------------------------------------+
 */

#ifndef REWRITELOG_DISABLED
static char *current_logtime(request_rec *r)
{
    apr_time_exp_t t;
    char tstr[80];
    apr_size_t len;

    apr_time_exp_lt(&t, apr_time_now());

    apr_strftime(tstr, &len, sizeof(tstr), "[%d/%b/%Y:%H:%M:%S ", &t);
    apr_snprintf(tstr+len, sizeof(tstr)-len, "%c%.2d%.2d]",
                 t.tm_gmtoff < 0 ? '-' : '+',
                 t.tm_gmtoff / (60*60), t.tm_gmtoff % (60*60));

    return apr_pstrdup(r->pool, tstr);
}

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

static void do_rewritelog(request_rec *r, int level, char *perdir,
                          const char *fmt, ...)
{
    rewrite_server_conf *conf;
    char *logline, *text;
    const char *rhost, *rname;
    apr_size_t nbytes;
    int redir;
    request_rec *req;
    va_list ap;

    conf = ap_get_module_config(r->server->module_config, &rewrite_module);

    if (!conf->rewritelogfp || level > conf->rewriteloglevel) {
        return;
    }

    rhost = ap_get_remote_host(r->connection, r->per_dir_config,
                               REMOTE_NOLOOKUP, NULL);
    rname = ap_get_remote_logname(r);

    for (redir=0, req=r; req->prev; req = req->prev) {
        ++redir;
    }

    va_start(ap, fmt);
    text = apr_pvsprintf(r->pool, fmt, ap);
    va_end(ap);

    logline = apr_psprintf(r->pool, "%s %s %s %s [%s/sid#%pp][rid#%pp/%s%s%s] "
                                    "(%d) %s%s%s%s" APR_EOL_STR,
                           rhost ? ap_escape_logitem(r->pool, rhost) : "UNKNOWN-HOST",
                           rname ? ap_escape_logitem(r->pool, rname) : "-",
                           r->user ? (*r->user ? ap_escape_logitem(r->pool, r->user) : "\"\"") : "-",
                           current_logtime(r),
                           ap_escape_logitem(r->pool, ap_get_server_name(r)),
                           (void *)(r->server),
                           (void *)r,
                           r->main ? "subreq" : "initial",
                           redir ? "/redir#" : "",
                           redir ? apr_itoa(r->pool, redir) : "",
                           level,
                           perdir ? "[perdir " : "",
                           perdir ? perdir : "",
                           perdir ? "] ": "",
                           ap_escape_logitem(r->pool, text));

    nbytes = strlen(logline);
    apr_file_write(conf->rewritelogfp, logline, &nbytes);

    return;
}
#endif /* !REWRITELOG_DISABLED */


