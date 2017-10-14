static void do_rewritelog(request_rec *r, int level, char *perdir,
                          const char *fmt, ...)
{
    rewrite_server_conf *conf;
    char *logline, *text;
    const char *rhost, *rname;
    apr_size_t nbytes;
    int redir;
    apr_status_t rv;
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
                           rhost ? rhost : "UNKNOWN-HOST",
                           rname ? rname : "-",
                           r->user ? (*r->user ? r->user : "\"\"") : "-",
                           current_logtime(r),
                           ap_get_server_name(r),
                           (void *)(r->server),
                           (void *)r,
                           r->main ? "subreq" : "initial",
                           redir ? "/redir#" : "",
                           redir ? apr_itoa(r->pool, redir) : "",
                           level,
                           perdir ? "[perdir " : "",
                           perdir ? perdir : "",
                           perdir ? "] ": "",
                           text);

    rv = apr_global_mutex_lock(rewrite_log_lock);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_global_mutex_lock(rewrite_log_lock) failed");
        /* XXX: Maybe this should be fatal? */
    }

    nbytes = strlen(logline);
    apr_file_write(conf->rewritelogfp, logline, &nbytes);

    rv = apr_global_mutex_unlock(rewrite_log_lock);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_global_mutex_unlock(rewrite_log_lock) failed");
        /* XXX: Maybe this should be fatal? */
    }

    return;
}