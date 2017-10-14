static void do_rewritelog(request_rec *r, int level, char *perdir,
                          const char *fmt, ...)
{
    char *logline, *text;
    const char *rhost, *rname;
    int redir;
    request_rec *req;
    va_list ap;

    rhost = ap_get_remote_host(r->connection, r->per_dir_config,
                               REMOTE_NOLOOKUP, NULL);
    rname = ap_get_remote_logname(r);

    for (redir=0, req=r; req->prev; req = req->prev) {
        ++redir;
    }

    va_start(ap, fmt);
    text = apr_pvsprintf(r->pool, fmt, ap);
    va_end(ap);

    logline = apr_psprintf(r->pool, "%s %s %s [%s/sid#%pp][rid#%pp/%s%s%s] "
                                    "%s%s%s%s" APR_EOL_STR,
                           rhost ? rhost : "UNKNOWN-HOST",
                           rname ? rname : "-",
                           r->user ? (*r->user ? r->user : "\"\"") : "-",
                           ap_get_server_name(r),
                           (void *)(r->server),
                           (void *)r,
                           r->main ? "subreq" : "initial",
                           redir ? "/redir#" : "",
                           redir ? apr_itoa(r->pool, redir) : "",
                           perdir ? "[perdir " : "",
                           perdir ? perdir : "",
                           perdir ? "] ": "",
                           text);

    AP_REWRITE_LOG((uintptr_t)r, level, r->main ? 0 : 1, (char *)ap_get_server_name(r), logline);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG + level, 0, r, logline);

    return;
}