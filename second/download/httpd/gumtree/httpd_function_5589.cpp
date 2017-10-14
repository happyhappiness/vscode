static int log_scripterror(request_rec *r, cgi_server_conf * conf, int ret,
                           apr_status_t rv, char *error)
{
    apr_file_t *f = NULL;
    apr_finfo_t finfo;
    char time_str[APR_CTIME_LEN];
    int log_flags = rv ? APLOG_ERR : APLOG_ERR;

    ap_log_rerror(APLOG_MARK, log_flags, rv, r,
                  "%s: %s", error, r->filename);

    /* XXX Very expensive mainline case! Open, then getfileinfo! */
    if (!conf->logname ||
        ((apr_stat(&finfo, conf->logname,
                   APR_FINFO_SIZE, r->pool) == APR_SUCCESS) &&
         (finfo.size > conf->logbytes)) ||
        (apr_file_open(&f, conf->logname,
                       APR_APPEND|APR_WRITE|APR_CREATE, APR_OS_DEFAULT,
                       r->pool) != APR_SUCCESS)) {
        return ret;
    }

    /* "%% [Wed Jun 19 10:53:21 1996] GET /cgi-bin/printenv HTTP/1.0" */
    apr_ctime(time_str, apr_time_now());
    apr_file_printf(f, "%%%% [%s] %s %s%s%s %s\n", time_str, r->method, r->uri,
                    r->args ? "?" : "", r->args ? r->args : "", r->protocol);
    /* "%% 500 /usr/local/apache/cgi-bin */
    apr_file_printf(f, "%%%% %d %s\n", ret, r->filename);

    apr_file_printf(f, "%%error\n%s\n", error);

    apr_file_close(f);
    return ret;
}